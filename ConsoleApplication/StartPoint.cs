namespace ConsoleApplication.StartPoint;

using ConsoleApplication.Elements.UI.StartupMenu;

using ApplicationClient.Extensions.ServiceCollection;
using ApplicationClient.Responses.Auth;
using ApplicationClient.Responses.Database;

using ApplicationClient.Services.ConfigLoader;
using ApplicationClient.Services.ResponseConsumer;

using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System.Collections.Concurrent;
using ApplicationClient.Responses.Cards;

internal static partial class ConsoleApplicationLoop
{
    public static async Task<int> Main(string[] Args)
    {
        var config = await ServicesConfigLoader.LoadConfigAsync();
        if (config is null) { Console.WriteLine("Failed to load configuration. Exiting."); return 1; }

        var services = new ServiceCollection();
        if (config.DebugMode)
        {
            Console.Title = "Bank App - Debug Console";

            services.AddLogging
            (
                builder =>
                {
                    builder.AddSimpleConsole
                    (
                        options =>
                        {
                            options.SingleLine = true;
                            options.TimestampFormat = "HH:mm:ss ";
                        }
                    );
                }
            );
        }
        else
        {
            Console.Title = "Bank App";
            services.AddLogging(builder => builder.SetMinimumLevel(LogLevel.Warning));
        }

        services.AddApplicationServices(config, config.BootstrapServers);

        services.AddSingleton<ResponseConsumerService>();

        var pendingTransactionResponses = new ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesDatabase>>();
        var pendingAuthResponses = new ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesAuth>>();
        var pendingCardsResponses = new ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesCards>>();

        services.AddSingleton(pendingTransactionResponses);
        services.AddSingleton(pendingAuthResponses);
        services.AddSingleton(pendingCardsResponses);

        services.AddSingleton<ResponseConsumerService>
        (
            provider => new ResponseConsumerService
            (
                config.BootstrapServers,
                new[] { config.Topics["AuthResponse"], config.Topics["CardsResponse"] },
                provider.GetRequiredService<ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesDatabase>>>(),
                provider.GetRequiredService<ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesAuth>>>(),
                provider.GetRequiredService<ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesCards>>>(),
                provider.GetService<ILogger<ResponseConsumerService>>()!
            )
        );

        var provider = services.BuildServiceProvider();

        provider.GetRequiredService<ResponseConsumerService>().Start();

        return await ElementsUIStartupMenu.RunAsync(provider);
    }
}