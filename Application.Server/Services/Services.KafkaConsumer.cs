namespace ApplicationServer.Services.KafkaConsumer;

using ApplicationServer.Commands.Auth;
using ApplicationServer.Services.Orchestrators.Server;

using InfrastructureServer.Interfaces.Messaging.KafkaProducer;

using Confluent.Kafka;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System.Threading;
using System.Threading.Tasks;
using ApplicationServer.Responses.Envelope;
using Newtonsoft.Json;
using Application.Server.Commands;

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

    private async Task ConsumeMessages()
    {
        try
        {
            while (!_cts.IsCancellationRequested)
            {
                var cr = _consumer.Consume(_cts.Token);
                await ProcessMessage(cr).ConfigureAwait(false);
            }
        }
        catch (OperationCanceledException) { _logger.LogInformation("Consumption cancelled"); }
        catch (Exception E) { _logger.LogCritical(E, "Fatal error in consumer"); }
    }

    private async Task ProcessMessage(ConsumeResult<string, string> Cr)
    {
        try
        {
            _logger.LogInformation("Received message from {Topic}", Cr.Topic);

            using var scope = _serviceProvider.CreateScope();
            var orchestrator = scope.ServiceProvider.GetRequiredService<ServicesOrchestratorsServer>();

            if (Cr.Topic.EndsWith("database-responses"))
            {
                var responseEnvelope = JsonConvert.DeserializeObject<ResponsesEnvelope>(Cr.Message.Value);
                if (responseEnvelope != null)
                {
                    var producer = scope.ServiceProvider.GetRequiredService<InterfacesKafkaProducer>();
                    await producer.ProduceAsync(responseEnvelope.ResponseTopic, responseEnvelope);
                }
            }
            else if (Cr.Topic.EndsWith("auth-commands"))
            {
                var command = JsonConvert.DeserializeObject<CommandsAuth>(Cr.Message.Value);
                orchestrator?.HandleAuthCommand(command!);
            }
            else if (Cr.Topic.EndsWith("cards-commands"))
            {
                var command = JsonConvert.DeserializeObject<CommandsCards>(Cr.Message.Value);
                orchestrator?.HandleCardsCommand(command!);
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