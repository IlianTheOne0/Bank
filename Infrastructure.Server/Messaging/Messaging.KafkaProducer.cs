namespace InfrastructureServer.Messaging.KafkaProducer;

using InfrastructureServer.Interfaces.Messaging.KafkaProducer;

using Confluent.Kafka;
using Newtonsoft.Json;
using Microsoft.Extensions.Logging;

public class KafkaProducer : InterfacesKafkaProducer, IDisposable
{
    private readonly IProducer<string, string> _producer;
    private readonly ILogger<KafkaProducer> _logger;

    public KafkaProducer(string bootstrapServers, ILogger<KafkaProducer> Logger)
    {
        _logger = Logger ?? throw new ArgumentNullException(nameof(Logger));

        var config = new ProducerConfig { BootstrapServers = bootstrapServers };

        _logger.LogInformation("Initializing Kafka producer with bootstrap servers: {BootstrapServers}", bootstrapServers);

        _producer = new ProducerBuilder<string, string>(config)
            .SetErrorHandler((_, e) => _logger.LogError("Kafka producer error: {Reason} (Code: {Code})", e.Reason, e.Code))
            .SetLogHandler((_, m) => _logger.LogDebug("Kafka log: {Message} (Facility: {Facility})", m.Message, m.Facility))
            .Build();

        _logger.LogInformation("Kafka producer initialized successfully");
    }

    public async Task ProduceAsync<TModel>(string Topic, TModel Message)
    {
        if (string.IsNullOrWhiteSpace(Topic))
        {
            _logger.LogError("Topic cannot be null or empty");
            throw new ArgumentException("Topic cannot be null or empty", nameof(Topic));
        }

        _logger.LogDebug("Producing message to topic: {Topic}", Topic);

        try
        {
            var json = JsonConvert.SerializeObject(Message);
            _logger.LogTrace("Serialized message: {Json}", json);

            var kafkaMessage = new Message<string, string>
            {
                Key = Guid.NewGuid().ToString(),
                Value = json
            };

            var deliveryResult = await _producer.ProduceAsync(Topic, kafkaMessage);

            _logger.LogDebug("Message delivered to {Topic} [Partition: {Partition}, Offset: {Offset}]", deliveryResult.Topic, deliveryResult.Partition, deliveryResult.Offset);
        }
        catch (Exception E) { _logger.LogError(E, "Failed to produce message to topic: {Topic}", Topic); throw; }
    }

    public void Dispose()
    {
        try
        {
            _logger.LogDebug("Flushing pending Kafka messages...");
            _producer.Flush(TimeSpan.FromSeconds(5));
            _producer.Dispose();
            _logger.LogInformation("Kafka producer disposed successfully");
        }
        catch (Exception E) { _logger.LogError(E, "Error occurred while disposing Kafka producer"); throw; }
    }
}