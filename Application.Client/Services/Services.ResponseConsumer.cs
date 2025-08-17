namespace ApplicationClient.Services.ResponseConsumer;


using ApplicationClient.Responses.Auth;
using ApplicationClient.Responses.Cards;
using ApplicationClient.Responses.Database;
using ApplicationClient.Responses.Envelope;

using Confluent.Kafka;
using Microsoft.Extensions.Logging;
using System.Collections.Concurrent;
using System.Text.Json;

public class ResponseConsumerService : IDisposable
{
    private readonly IConsumer<string, string> _consumer;
    private readonly CancellationTokenSource _cts = new();
    private readonly ILogger<ResponseConsumerService> _logger;
    
    private readonly ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesDatabase>> _pendingTransactionResponses;
    private readonly ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesAuth>> _pendingAuthResponses;
    private readonly ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesCards>> _pendingCardsResponses;

    public ResponseConsumerService
    (
        string bootstrapServers, IEnumerable<string> Topics,
        ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesDatabase>> TransactionResponses,
        ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesAuth>> AuthResponses,
        ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesCards>> CardsResponses,
        ILogger<ResponseConsumerService> Logger
    )
    {
        _pendingTransactionResponses = TransactionResponses;
        _pendingAuthResponses = AuthResponses;
        _pendingCardsResponses = CardsResponses;
        _logger = Logger;

        var config = new ConsumerConfig
        {
            BootstrapServers = bootstrapServers,
            GroupId = "console-response-consumer",
            AutoOffsetReset = AutoOffsetReset.Earliest,
            EnableAutoCommit = true,
            AutoCommitIntervalMs = 5000
        };

        _consumer = new ConsumerBuilder<string, string>(config)
            .SetErrorHandler((_, e) => _logger.LogError("Consumer error: {Reason}", e.Reason))
            .Build();

        _consumer.Subscribe(Topics);
    }

    public void Start() => Task.Run(ConsumeResponses);

    private void ConsumeResponses()
    {
        _logger.LogInformation("Starting unified response consumer");

        try
        {
            while (!_cts.IsCancellationRequested)
            {
                try { var cr = _consumer.Consume(_cts.Token); ProcessMessage(cr); }
                catch (ConsumeException E) { _logger.LogError(E, "Consume error: {Reason}", E.Error.Reason); }
            }
        }
        catch (OperationCanceledException) { _logger.LogInformation("Response consumption cancelled"); }
        catch (Exception E) { _logger.LogCritical(E, "Fatal error in response consumer"); }
    }

    private void ProcessMessage(ConsumeResult<string, string> Cr)
    {
        try
        {
            _logger.LogDebug("Received message from {Topic}", Cr.Topic);
            if (Cr.Topic.EndsWith("auth-responses"))
            {
                var response = JsonSerializer.Deserialize<ResponsesAuth>(Cr.Message.Value);
                if (response != null && _pendingAuthResponses.TryRemove(response.CorrelationId, out var tcs))
                {
                    tcs.SetResult(response);
                    _logger.LogInformation("Processed auth response for {CorrelationId}", response.CorrelationId);
                }
            }
            else if (Cr.Topic.EndsWith("cards-responses"))
            {
                var response = JsonSerializer.Deserialize<ResponsesCards>(Cr.Message.Value);
                if (response != null && _pendingCardsResponses.TryRemove(response.CorrelationId, out var tcs))
                {
                    tcs.SetResult(response);
                    _logger.LogInformation("Processed cards response for {CorrelationId}", response.CorrelationId);
                }
            }
            else { _logger.LogWarning("Received message from unknown topic: {Topic}", Cr.Topic); }
        }
        catch (JsonException E) { _logger.LogError(E, "JSON deserialization error for message: {Value}", Cr.Message.Value); }
        catch (Exception E) { _logger.LogError(E, "Error processing message from {Topic}", Cr.Topic); }
    }

    public void Dispose()
    {
        _cts.Cancel();
        _consumer.Close();
        _consumer.Dispose();
        _logger.LogInformation("Unified response consumer stopped");
    }
}