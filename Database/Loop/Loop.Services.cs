namespace Database.Loop;

using Database.CommandsHandler.Transactions;
using Database.Interfaces.Repositories.Supabase.Auth;
using Database.Interfaces.Repositories.Supabase.Commands;
using Database.Interfaces.Repositories.Supabase.Init;
using Database.Repositories.Supabase;

using InfrastructureServer.Interfaces.Messaging.KafkaProducer;
using InfrastructureServer.Messaging.KafkaProducer;
using InfrastructureServer.Models.Config;

using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

internal partial class DatabaseLoop
{
    private static async Task LoadServices(ServiceCollection Services, AppConfig Config)
    {
        try
        {
            using var loggerFactory = LoggerFactory.Create
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

            Services.AddLogging(configure => configure.AddConsole());

            Services.AddSingleton<InterfacesKafkaProducer>
            (
                new KafkaProducer
                (
                    Config.Kafka.BootstrapServers,
                    loggerFactory.CreateLogger<KafkaProducer>()
                )
            );

            Services.AddSingleton
            (
                provider =>
                {
                    var repo = new RepositoriesSupabase();
                    var logger = provider.GetService<ILogger<RepositoriesSupabase>>() ?? loggerFactory.CreateLogger<RepositoriesSupabase>();
                    repo.InitDatabase(Config.Supabase, logger);
                    return repo;
                }
            )
            .AddSingleton<InterfacesRepositoriesSupabaseAuth>
            (
                provider => provider.GetRequiredService<RepositoriesSupabase>()
            )
                .AddSingleton<InterfacesRepositoriesSupabaseCommands>
                (
                    provider => provider.GetRequiredService<RepositoriesSupabase>()
                )
                .AddSingleton<InterfacesRepositoriesSupabaseInit>
                (
                    provider => provider.GetRequiredService<RepositoriesSupabase>()
                );

            Services.AddScoped<CommandsHandlerAuth>
            (
                provider => new CommandsHandlerAuth
                (
                    provider.GetRequiredService<InterfacesRepositoriesSupabaseCommands>(),
                    provider.GetService<ILogger<CommandsHandlerAuth>>() ?? loggerFactory.CreateLogger<CommandsHandlerAuth>()
                )
            );
        }
        catch (Exception E) { Console.WriteLine($"Fatal error: {E.Message}\n{E.StackTrace}"); }
    }
}