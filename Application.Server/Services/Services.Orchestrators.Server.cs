namespace ApplicationServer.Services.Orchestrators.Server;

using ApplicationServer.Commands.Auth;

using InfrastructureServer.Interfaces.Messaging.KafkaProducer;

using Microsoft.Extensions.Logging;

public class ServicesOrchestratorsServer
{
    private readonly InterfacesKafkaProducer _producer;
    private readonly ILogger<ServicesOrchestratorsServer> _logger;

    public ServicesOrchestratorsServer(InterfacesKafkaProducer Producer, ILogger<ServicesOrchestratorsServer> Logger)
    {
        _producer = Producer;
        _logger = Logger;
    }

    public async Task HandleAuthCommand(CommandsAuth Command)
    {
        try
        {
            _logger.LogInformation("Forwarding auth command for {Username}", Command.Username);
            await _producer.ProduceAsync
            (
                "database-commands",
                new
                {
                    CommandType = "Auth",
                    Command = Command
                }
            );
        }
        catch (Exception E) { _logger.LogError(E, "Error forwarding auth command"); }
    }
}