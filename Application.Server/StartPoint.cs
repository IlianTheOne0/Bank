namespace ApplicationServer.StartPoint;

using ApplicationServer.Extensions.ServicesCollecction;
using ApplicationClient.Services.ConfigLoader;
using ApplicationServer.Services.KafkaConsumer;

using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

internal class ApplicationServerStartPoint
{
    public static async Task Main(string[] Args)
    {
        Console.Title = "Application.Server";
        Console.WriteLine("Application.Server:");

        var config = await ServicesConfigLoader.LoadConfigAsync();
        if (config is null) { return; }

        var host = Host.CreateDefaultBuilder(Args)
            .ConfigureServices
            (
            services =>
                {
                    services.AddApplicationServer
                    (
                        config.Kafka.BootstrapServers,
                        config
                    );
                }
            )
            .Build();

        var kafkaConsumer = host.Services.GetRequiredService<KafkaConsumerService>();
        kafkaConsumer.Start();

        await host.RunAsync();
    }
}