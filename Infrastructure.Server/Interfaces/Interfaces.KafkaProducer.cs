namespace InfrastructureServer.Interfaces.Messaging.KafkaProducer;

public interface InterfacesKafkaProducer
{
    Task ProduceAsync<TModel>(string Topic, TModel Message);
}