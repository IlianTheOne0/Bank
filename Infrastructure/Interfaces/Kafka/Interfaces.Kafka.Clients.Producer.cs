namespace Infrastructure.Interfaces.Kafka.Clients.Producer;

public interface InterfacesKafkaClientsProducer
{
    Task ProduceAsync(string topic, object command);
}