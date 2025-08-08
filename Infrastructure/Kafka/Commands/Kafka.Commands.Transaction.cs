namespace Infrastructure.Kafka.Commands.Transaction;

using Infrastructure.Interfaces.Kafka.Commands.Processor;

public class TransactionCommandProcessor : InterfacesKafkaCommandsProcessor
{
    public bool CanProcess(CommandTypes type) => type == CommandTypes.ProcessTransaction;

    public async Task ProcessAsync(string data)
    {
        var transaction = JsonSerializer.Deserialize<Transaction>(data);
    }
}