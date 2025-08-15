namespace ApplicationClient.Extensions.ServiceCollection;

using ApplicationClient.Services.Orchestrators.Auth;
using ApplicationClient.Services.ApplicationResponseHandler;

using Domain.Entities.Services.Kafka;

using InfrastructureClient.Interfaces.KafkaProducer;
using InfrastructureClient.Messaging.KafkaProducer;

using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

public static class ExtensionsServiceCollection
{
    public static IServiceCollection AddApplicationServices(this IServiceCollection Services, EntitiesServicesKafka Config, string BootstrapServers)
    {
        LoadKafkaProducer(Services, Config, BootstrapServers);
        LoadResponseHandler(Services, Config, BootstrapServers);
        LoadOrchestrators(Services, Config);

        return Services;
    }

    private static void LoadKafkaProducer(IServiceCollection Services, EntitiesServicesKafka Config, string BootstrapServers)
    {
        Services.AddSingleton<InterfacesKafkaProducer>
        (
            provider => new MessagingKafkaProducer
            (
                BootstrapServers,
                provider.GetService<ILogger<MessagingKafkaProducer>>()!
            )
        );
    }

    private static void LoadResponseHandler(IServiceCollection Services, EntitiesServicesKafka Config, string BootstrapServers)
    {
        Services.AddSingleton<ServicesApplicationResponseHandler>
        (
            provider => new ServicesApplicationResponseHandler
            (
                BootstrapServers,
                Config.Topics["AuthResponse"],
                provider.GetService<ILogger<ServicesApplicationResponseHandler>>()!
            )
        );
    }

    private static void LoadOrchestrators(IServiceCollection Services, EntitiesServicesKafka Config)
    {
        Services.AddScoped<ServicesOrchestratorAuth>
        (
            provider => new ServicesOrchestratorAuth
            (
                provider.GetRequiredService<InterfacesKafkaProducer>(),
                provider.GetRequiredService<ServicesApplicationResponseHandler>(),
                Config.Topics["AuthTopic"],
                provider.GetService<ILogger<ServicesOrchestratorAuth>>()!
            )
        );
    }
}