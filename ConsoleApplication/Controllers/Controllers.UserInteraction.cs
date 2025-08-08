namespace ConsoleApplication.Controllers;

using Domain.Entities.Transactions.Model;
using Infrastructure.Interfaces.Kafka.Producer;


public class UserInteractionController
{
    private readonly InterfacesKafkaProducer _producer;
    private readonly string _topic;

    public UserInteractionController(InterfacesKafkaProducer producer, string topic)
    {
        _producer = producer;
        _topic = topic;
    }

    public async Task RunAsync()
    {
        Console.WriteLine("1. Process Transaction");
        Console.WriteLine("2. Block Card");
        Console.Write("Choose: ");
        var choice = Console.ReadLine();

        switch (choice)
        {
            case "1": await ProcessTransaction(); break;
            case "2": await BlockCard(); break;
            default: Console.WriteLine("Invalid"); break;
        }
    }

    private async Task ProcessTransaction()
    {
        var tx = new Transaction
        {
            Amount = 123.45m,
            Description = "Test Deposit",
            TimeStamp = DateTime.UtcNow,
            SenderUserId = Guid.NewGuid(),
            ReceiverUserId = Guid.NewGuid(),
            Type = new() { Id = 1, Type = "Deposit" }
        };

        var command = new Command
        {
            Type = CommandTypes.ProcessTransaction,
            Data = System.Text.Json.JsonSerializer.Serialize(tx)
        };

        await _producer.ProduceAsync(_topic, command);
        Console.WriteLine("Sent transaction command.");
    }

    private async Task BlockCard()
    {
        Console.Write("Enter card ID to block: ");
        var cardId = int.Parse(Console.ReadLine()!);

        var command = new Command
        {
            Type = CommandTypes.BlockCard,
            Data = System.Text.Json.JsonSerializer.Serialize(cardId)
        };

        await _producer.ProduceAsync(_topic, command);
        Console.WriteLine("Sent block card command.");
    }
}
