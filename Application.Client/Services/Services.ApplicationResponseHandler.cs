namespace ApplicationClient.Services.ApplicationResponseHandler;

using ApplicationClient.Responses.Database;
using ApplicationClient.Responses.Envelope;

using Microsoft.Extensions.Logging;
using Confluent.Kafka;
using System.Collections.Concurrent;
using System.Text.Json;

public class ServicesApplicationResponseHandler : IDisposable
{
    private readonly IConsumer<string, string> _consumer;
    private readonly CancellationTokenSource _cts = new();
    private readonly ConcurrentDictionary<Guid, TaskCompletionSource<ResponsesDatabase>> _pendingResponses = new();
    private readonly Task _consumingTask;
    private readonly ILogger<ServicesApplicationResponseHandler> _logger;

    public ServicesApplicationResponseHandler(string BootstrapServers, IEnumerable<string> ResponseTopics, ILogger<ServicesApplicationResponseHandler> Logger)
    {
        _logger = Logger;

        var config = new ConsumerConfig
        {
            BootstrapServers = BootstrapServers,
            GroupId = "application-response-handler",
            AutoOffsetReset = AutoOffsetReset.Earliest
        };

        _consumer = new ConsumerBuilder<string, string>(config).Build();
        _consumer.Subscribe(ResponseTopics);

        _consumingTask = Task.Run(ConsumeResponses);
    }

    private void ConsumeResponses()
    {
        try
        {
            while (!_cts.IsCancellationRequested)
            {
                var cr = _consumer.Consume(_cts.Token);
                try
                {
                    var response = JsonSerializer.Deserialize<ResponsesEnvelope>(cr.Message.Value);
                    if (response != null && _pendingResponses.TryRemove(response.CorrelationId, out var tcs)) { tcs.SetResult(response.Response); }
                }
                catch (JsonException E) { _logger.LogError(E, "Failed to deserialize response"); }
            }
        }
        catch (Exception E) { _logger.LogError(E, "Error in response consumer"); }
    }

    public Task<ResponsesDatabase> RegisterPendingResponse(Guid CorrelationId)
    {
        var tcs = new TaskCompletionSource<ResponsesDatabase>();
        _pendingResponses[CorrelationId] = tcs;
        return tcs.Task;
    }

    public void Dispose()
    {
        _cts.Cancel();
        _consumer.Close();
        _consumer.Dispose();
        _consumingTask.Wait();
    }
}