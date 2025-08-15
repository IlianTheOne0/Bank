namespace InfrastructureClient.Interfaces.KafkaProducer;

public interface InterfacesKafkaProducer : IDisposable
{
    Task ProduceAsync<TMethod>(string Topic, TMethod Message, CancellationToken CancellationToken = default);
}