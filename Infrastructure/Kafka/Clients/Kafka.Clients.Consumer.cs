namespace Infrastructure.Kafka.Client.Consumer;

using Confluent.Kafka;
using Infrastructure.Interfaces.Kafka.Commands.Processor;
using System.Text.Json;
using static Microsoft.EntityFrameworkCore.DbLoggerCategory.Database;

public class KafkaConsumerService : IDisposable
{
    private readonly IConsumer<string, string> _consumer;
    private readonly IEnumerable<InterfacesKafkaCommandsProcessor> _processors;

    public KafkaConsumerService(string BootstrapServers, string GroupId, string Topic, IEnumerable<InterfacesKafkaCommandsProcessor> processors)
    {
        var config = new ConsumerConfig
        {
            BootstrapServers = BootstrapServers,
            GroupId = GroupId,
            AutoOffsetReset = AutoOffsetReset.Earliest,
            EnableAutoCommit = false,
            EnableAutoOffsetStore = false
        };

        _consumer = new ConsumerBuilder<string, string>(config).Build();
        _consumer.Subscribe(Topic);
        _processors = processors;
    }

    public async Task ProcessCommand(Command command)
    {
        var processor = _processors.FirstOrDefault(p => p.CanProcess(command.Type));
        if (processor != null) { await processor.ProcessAsync(command.Data); }
    }

    public async Task StartConsumingAsync(CancellationToken CancellationToken)
    {
        while (!CancellationToken.IsCancellationRequested)
        {
            try
            {
                var result = _consumer.Consume(CancellationToken);
                var command = JsonSerializer.Deserialize<Command>(result.Message.Value);

                if (command != null)
                {
                    Console.WriteLine($"Received command: {command.Type}");
                    await _commandProcessor.ProcessCommand(command.Type, command.Data);
                }

                _consumer.StoreOffset(result);
                _consumer.Commit(result);
            }
            catch (ConsumeException E) { Console.WriteLine($"Consume error: {E.Error.Reason}"); }
            catch (Exception E) { Console.WriteLine($"Processing error: {E.Message}"); }
        }
    }

    public void Dispose() { _consumer.Close(); _consumer.Dispose(); }
}