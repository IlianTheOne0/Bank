namespace ApplicationServer.Services.KafkaConsumer;

using ApplicationServer.Commands.Auth;
using ApplicationServer.Responses.Envelope;
using ApplicationServer.Services.Orchestrators.Server;

using InfrastructureServer.Interfaces.Messaging.KafkaProducer;

using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Confluent.Kafka;
using System.Text.Json;

public class KafkaConsumerService : IDisposable
{
    private readonly IConsumer<string, string> _consumer;
    private readonly CancellationTokenSource _cts = new();
    private readonly IServiceProvider _serviceProvider;
    private readonly InterfacesKafkaProducer _producer;
    private readonly ILogger<KafkaConsumerService> _logger;

    public KafkaConsumerService(string BootstrapServers, IEnumerable<string> Topics, IServiceProvider Services, ILogger<KafkaConsumerService> Logger)
    {
        _serviceProvider = Services;
        _logger = Logger;

        var config = new ConsumerConfig
        {
            BootstrapServers = BootstrapServers,
            GroupId = "application-server",
            AutoOffsetReset = AutoOffsetReset.Earliest,
            EnableAutoCommit = true,
            AutoCommitIntervalMs = 5000
        };

        _consumer = new ConsumerBuilder<string, string>(config)
            .SetErrorHandler((_, e) => _logger.LogError("Consumer error: {Reason}", e.Reason))
            .Build();

        _producer = Services.GetRequiredService<InterfacesKafkaProducer>();

        _consumer.Subscribe(Topics);
    }

    public void Start() => Task.Run(ConsumeMessages);

    private void ConsumeMessages()
    {
        try
        {
            while (!_cts.IsCancellationRequested) { var cr = _consumer.Consume(_cts.Token); ProcessMessage(cr); }
        }
        catch (OperationCanceledException) { _logger.LogInformation("Consumption cancelled"); }
        catch (Exception E) { _logger.LogCritical(E, "Fatal error in consumer"); }
    }

    private void ProcessMessage(ConsumeResult<string, string> Cr)
    {
        try
        {
            _logger.LogInformation("Received message from {Topic}", Cr.Topic);

            using var scope = _serviceProvider.CreateScope();
            var orchestrator = scope.ServiceProvider.GetRequiredService<ServicesOrchestratorsServer>();
            
            if (Cr.Topic == "database-responses")
            {
                var response = JsonSerializer.Deserialize<ResponsesEnvelope>(Cr.Message.Value);
                _producer.ProduceAsync
                (
                    response!.ResponseTopic!,
                    response
                );
            }
            if (Cr.Topic.EndsWith("auth-commands"))
            {
                var command = JsonSerializer.Deserialize<CommandsAuth>(Cr.Message.Value);
                orchestrator?.HandleAuthCommand(command!);
            }
        }
        catch (Exception E) { _logger.LogError(E, "Error processing message"); }
    }

    public void Dispose()
    {
        _cts.Cancel();
        _consumer.Close();
        _consumer.Dispose();
    }
}