namespace Database.Loop;

using Database.CommandsHandler.Transactions;

using ApplicationServer.Commands.Auth;
using ApplicationServer.Responses.Envelope;

using InfrastructureServer.Interfaces.Messaging.KafkaProducer;
using InfrastructureServer.Models.Config;

using Newtonsoft.Json;
using Microsoft.Extensions.DependencyInjection;

internal partial class DatabaseLoop
{
    private static async Task HandleMessage(AppConfig Config, string Topic, string Json, ServiceProvider Provider, CancellationToken Cts)
    {
        try
        {
            if (Topic == "database-commands")
            {
                dynamic envelope = JsonConvert.DeserializeObject(Json)!;
                string commandType = envelope.CommandType;
                string commandJson = JsonConvert.SerializeObject(envelope.Command);

                switch (commandType)
                {
                    case "Auth": { await HandleAuthCommand(Config, commandJson, Provider, Cts); } break;
                    default: { throw new Exception("Unknown command type!"); }
                }
            }
        }
        catch (Exception E) { Console.WriteLine($"Error handling message: {E.Message}"); }
    }

    private static async Task HandleAuthCommand(AppConfig Config, string Json, ServiceProvider Provider, CancellationToken Cts)
    {
        var cmd = JsonConvert.DeserializeObject<CommandsAuth>(Json);
        using var scope = Provider.CreateScope();
        var serviceProvider = scope.ServiceProvider;
        var authHandler = serviceProvider.GetRequiredService<CommandsHandlerAuth>();
        var response = await authHandler.Handle(cmd);

        var producer = serviceProvider.GetRequiredService<InterfacesKafkaProducer>();

        await producer.ProduceAsync
        (
            Config.Kafka.Topics["DatabaseResponses"],
            new ResponsesEnvelope
            {
                Response = response,
                ResponseTopic = Config.Kafka.Topics["AuthResponse"],
                CorrelationId = cmd!.CorrelationId
            }
        );
    }
}