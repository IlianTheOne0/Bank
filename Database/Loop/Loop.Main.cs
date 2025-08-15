namespace Database.Loop;

using ApplicationClient.Services.ConfigLoader;

using InfrastructureServer.Models.Config;

using Confluent.Kafka;
using Microsoft.Extensions.DependencyInjection;
using System;

internal partial class DatabaseLoop
{
    public static async Task Main(string[] Args)
    {
        try
        {
            Console.Title = "Database";
            Console.WriteLine("Database:");

            AppConfig config = await ServicesConfigLoader.LoadConfigAsync() ?? throw new FileLoadException("Database worker stopped.");

            ServiceCollection services = new ServiceCollection();
            await LoadServices(services, config);

            Console.WriteLine($"Kafka bootstrap: {config.Kafka?.BootstrapServers ?? "<missing>"}");
            Console.WriteLine($"Topics: {string.Join(", ", config.Kafka?.Topics.Values!)}");
            Console.WriteLine($"Supabase present: {(config.Supabase != null ? "yes" : "no")}");

            using ServiceProvider serviceProvider = services.BuildServiceProvider();
            
            await SupabaseLogin(serviceProvider, config);
            
            (CancellationTokenSource cts, IConsumer<string, byte[]> consumer) = await LoadKafka(config);
            await ProcessTheMessages(config, cts, consumer, serviceProvider);
            
            await SupabaseLogout(serviceProvider);

            Console.WriteLine("Database worker stopped.");
        }
        catch (Exception E) { Console.WriteLine($"Fatal error: {E.Message}\n{E.StackTrace}"); }
    }
}