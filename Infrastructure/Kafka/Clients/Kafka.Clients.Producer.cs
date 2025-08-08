namespace Infrastructure.Kafka.Client.Producer;

using Confluent.Kafka;
using Infrastructure.Interfaces.Kafka.Producer;
using System.Text.Json;
using System.Threading.Tasks;

public class KafkaProducer : InterfacesKafkaProducer, IAsyncDisposable
{
    private readonly IProducer<Null, string> _producer;

    public KafkaProducer(string bootstrapServers)
    {
        if (string.IsNullOrWhiteSpace(bootstrapServers)) { throw new ArgumentException("Bootstrap servers cannot be null or empty", nameof(bootstrapServers)); }

        var config = new ProducerConfig
        {
            BootstrapServers = bootstrapServers,
            MessageTimeoutMs = 5000,
            RequestTimeoutMs = 3000
        };

        _producer = new ProducerBuilder<Null, string>(config).Build();
    }

    public async Task ProduceAsync(string topic, object command)
    {
        if (string.IsNullOrWhiteSpace(topic)) { throw new ArgumentException("Topic cannot be null or empty", nameof(topic)); }

        try
        {
            var json = JsonSerializer.Serialize(command);
            var message = new Message<Null, string> { Value = json };

            var deliveryResult = await _producer.ProduceAsync(topic, message);

            Console.WriteLine($"Delivered message to {deliveryResult.TopicPartitionOffset}");
        }
        catch (ProduceException<Null, string> e) { Console.WriteLine($"Delivery failed: {e.Error.Reason}"); throw; }
    }

    public async ValueTask DisposeAsync()
    {
        _producer.Flush(TimeSpan.FromSeconds(5));
        _producer.Dispose();
        await Task.CompletedTask;
    }
}