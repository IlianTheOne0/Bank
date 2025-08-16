namespace ApplicationClient.Services.Orchestrators.Auth;

using ApplicationClient.Commands.Auth;
using ApplicationClient.Interfaces.Services.Orchestrator;
using ApplicationClient.Responses.Auth;
using ApplicationClient.Services.ApplicationResponseHandler;

using Domain.Entities.User.Model;

using InfrastructureClient.Interfaces.KafkaProducer;

using Microsoft.Extensions.Logging;
using System.Diagnostics;
using System.Text.Json;

public class ServicesOrchestratorAuth : InterfacesServicesOrchestrators
{
    private readonly InterfacesKafkaProducer _producer;
    private readonly ServicesApplicationResponseHandler _responseHandler;
    private readonly string _commandTopic;
    private readonly ILogger<ServicesOrchestratorAuth> _logger;

    public ServicesOrchestratorAuth(InterfacesKafkaProducer Producer, ServicesApplicationResponseHandler ResponseHandler, string CommandTopic, ILogger<ServicesOrchestratorAuth> Logger = null)
    {
        _producer = Producer;
        _responseHandler = ResponseHandler;
        _commandTopic = CommandTopic;
        _logger = Logger;
    }

    public async Task<TResponse> Execute<TCommand, TResponse>(TCommand Command)
    {
        if (Command is not CommandsAuth authCommand) { throw new ArgumentException("The command data type is incorrect!"); }

        var stopwatch = Stopwatch.StartNew();
        var correlationId = authCommand.CorrelationId;

        try
        {
            _logger?.LogInformation("Authenticating user: {Username}", authCommand.Username);

            var responseTask = _responseHandler.RegisterPendingResponse(correlationId);

            await _producer.ProduceAsync(_commandTopic, authCommand);

            var timeoutTask = Task.Delay(TimeSpan.FromSeconds(10));
            var completedTask = await Task.WhenAny(responseTask, timeoutTask);

            if (completedTask == responseTask)
            {
                var databaseResponse = await responseTask;
                _logger?.LogInformation("Authentication completed in {ElapsedMs}ms", stopwatch.ElapsedMilliseconds);

                EntitiesUser? user = null;

                try
                {
                    if (databaseResponse.Data != null)
                    {
                        if (databaseResponse.Data is EntitiesUser userObj) { user = userObj; }
                        else if (databaseResponse.Data is string jsonString)
                        {
                            if (!string.IsNullOrWhiteSpace(jsonString)) { user = JsonSerializer.Deserialize<EntitiesUser>(jsonString); }
                        }
                        else if (databaseResponse.Data is JsonElement jsonElement)
                        {
                            var json = jsonElement.GetRawText();
                            if (!string.IsNullOrWhiteSpace(json)) { user = JsonSerializer.Deserialize<EntitiesUser>(json); }
                        }
                    }
                }
                catch (Exception E) { _logger?.LogError(E, "Failed to deserialize user data from authentication response"); }

                var authResponse = new ResponsesAuth
                {
                    Success = databaseResponse.Success,
                    Message = databaseResponse.Message,
                    Error = databaseResponse.Error,
                    User = user!,
                    CorrelationId = correlationId
                };

                if (authResponse is TResponse typedResponse) { return typedResponse; }
                throw new InvalidCastException($"Cannot convert response to type {typeof(TResponse).Name}");
            }

            var timeoutResponse = new ResponsesAuth { Success = false, Error = "Timeout", Message = "Authentication timed out", CorrelationId = correlationId };

            if (timeoutResponse is TResponse typedTimeoutResponse) { return typedTimeoutResponse; }
            throw new InvalidCastException($"Cannot convert response to type {typeof(TResponse).Name}");
        }
        catch (Exception E)
        {
            _logger?.LogError(E, "Error authenticating user");
            var errorResponse = new ResponsesAuth { Success = false, Error = E.Message, Message = "Authentication failed", CorrelationId = correlationId };

            if (errorResponse is TResponse typedErrorResponse) { return typedErrorResponse; }
            throw new InvalidCastException($"Cannot convert response to type {typeof(TResponse).Name}");
        }
    }
}