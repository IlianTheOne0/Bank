using ConsoleApplication.Controllers;
using Infrastructure.Interfaces.Kafka.Producer;
using Infrastructure.Interfaces.Services.JsonReader;
using Infrastructure.Kafka.Client.Producer;
using Infrastructure.Services.JsonReader;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using System.IO;

namespace ConsoleApplication;

internal class Program
{
    private static IHost? _host;

    private static async void ConfigureServices(HostBuilderContext context, IServiceCollection services)
    {
        var config = context.Configuration;

        services.AddSingleton<InterfacesKafkaProducer>(provider =>
        {
            var jsonReader = provider.GetRequiredService<InterfacesServicesJsonReader>();
            var bootstrapServers = jsonReader.GetConfiguration()["Kafka:BootstrapServers"]!;
            return new KafkaProducer(bootstrapServers);
        });

        services.AddSingleton<InterfacesKafkaProducer>(provider =>
        {
            var jsonReader = provider.GetRequiredService<InterfacesServicesJsonReader>();
            var bootstrapServers = jsonReader.GetConfiguration()["Kafka:BootstrapServers"]!;
            return new KafkaProducer(bootstrapServers);
        });

        services.AddSingleton<UserInteractionController>(provider =>
        {
            var producer = provider.GetRequiredService<InterfacesKafkaProducer>();
            var jsonReader = provider.GetRequiredService<InterfacesServicesJsonReader>();
            var topic = jsonReader.GetConfiguration()["Kafka:Topic"]!;
            return new UserInteractionController(producer, topic);
        });
    }

    public static async Task Main(string[] args)
    {
        _host = Host.CreateDefaultBuilder(args)
            .ConfigureHostConfiguration(configHost =>
            {
                configHost.SetBasePath(Directory.GetCurrentDirectory());
                configHost.AddJsonFile("Infrastructure/.env/app_config.json", optional: false);
            })
            .ConfigureServices(ConfigureServices)
            .Build();

        try
        {
            var controller = _host.Services.GetRequiredService<UserInteractionController>();
            await controller.RunAsync();
        }
        catch (Exception ex) { Console.WriteLine($"Application failed: {ex.Message}"); throw; }
        finally
        {
            if (_host is IAsyncDisposable asyncDisposable) { await asyncDisposable.DisposeAsync(); }
            else { _host?.Dispose(); }
        }
    }
}