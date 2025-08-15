namespace InfrastructureClient.Messaging.KafkaProducer;

using InfrastructureClient.Interfaces.KafkaProducer;

using Confluent.Kafka;
using Newtonsoft.Json;
using Microsoft.Extensions.Logging;

public class MessagingKafkaProducer : InterfacesKafkaProducer
{
    private readonly IProducer<string, string> _producer;
    private readonly ILogger<MessagingKafkaProducer> _logger;

    public MessagingKafkaProducer(string BootstrapServers, ILogger<MessagingKafkaProducer> Logger)
    {
        _logger = Logger ?? throw new ArgumentNullException(nameof(Logger));

        var cfg = new ProducerConfig
        {
            BootstrapServers = BootstrapServers,
            Acks = Acks.All,
            ApiVersionRequestTimeoutMs = 5000,
            SocketTimeoutMs = 5000,
            RequestTimeoutMs = 3000
        };

        _logger.LogDebug("Initializing Kafka producer with config: {@Config}", cfg);

        _producer = new ProducerBuilder<string, string>(cfg)
            .SetErrorHandler((_, e) => _logger.LogError("Kafka producer error: {Reason}, Code: {Code}", e.Reason, e.Code))
            .SetLogHandler((_, m) => _logger.LogDebug("Kafka log: {Message}, Facility: {Facility}", m.Message, m.Facility))
            .Build();

        _logger.LogInformation("Kafka producer initialized successfully");
    }

    public async Task ProduceAsync<TMethod>(string Topic, TMethod Message, CancellationToken CancellationToken = default)
    {
        _logger.LogDebug("Producing message to topic {Topic}", Topic);

        try
        {
            var payload = JsonConvert.SerializeObject(Message);
            var kafkaMessage = new Message<string, string>
            {
                Key = Guid.NewGuid().ToString(),
                Value = payload
            };

            _logger.LogTrace("Producing message with key {Key} and payload: {Payload}", kafkaMessage.Key, payload);

            var result = await _producer.ProduceAsync(Topic, kafkaMessage, CancellationToken);

            _logger.LogDebug("Message delivered to {Topic} [Partition: {Partition}, Offset: {Offset}]", result.Topic, result.Partition, result.Offset);
        }
        catch (Exception E) { _logger.LogError(E, "Error producing message to topic {Topic}", Topic); throw; }
    }

    public void Dispose()
    {
        try
        {
            _logger.LogDebug("Flushing producer messages...");
            _producer.Flush(TimeSpan.FromSeconds(5));
            _logger.LogInformation("Kafka producer disposed successfully");
        }
        catch (Exception E) { _logger.LogError(E, "Error during producer disposal"); }
        finally { (_producer as IDisposable)?.Dispose(); }
    }
}