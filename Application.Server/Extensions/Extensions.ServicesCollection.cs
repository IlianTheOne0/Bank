namespace ApplicationServer.Extensions.ServicesCollecction;

using ApplicationServer.Services.KafkaConsumer;
using ApplicationServer.Services.Orchestrators.Server;

using InfrastructureServer.Interfaces.Messaging.KafkaProducer;
using InfrastructureServer.Messaging.KafkaProducer;
using InfrastructureServer.Models.Config;

using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;


public static class ServiceCollectionExtensions
{
    public static IServiceCollection AddApplicationServer(this IServiceCollection Services, string BootstrapServers, AppConfig Config)
    {
        Services.AddSingleton<InterfacesKafkaProducer>
         (
            provider => new KafkaProducer
            (
                BootstrapServers,
                provider.GetService<ILogger<KafkaProducer>>()!
            )
        );

        Services.AddScoped<ServicesOrchestratorsServer>();

        Services.AddSingleton<KafkaConsumerService>
        (
            provider => new KafkaConsumerService
            (
                BootstrapServers,
                new[]
                {
                    Config.Kafka.Topics["AuthTopic"],
                    Config.Kafka.Topics["DatabaseResponses"]
                },
                provider,
                provider.GetService<ILogger<KafkaConsumerService>>()!
            )
        );

        return Services;
    }
}