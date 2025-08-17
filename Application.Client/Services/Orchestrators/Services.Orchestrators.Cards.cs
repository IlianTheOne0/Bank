namespace ApplicationClient.Services.Orchestrators.Cards;

using ApplicationClient.Commands.Cards;
using ApplicationClient.Interfaces.Services.Orchestrator;
using ApplicationClient.Responses.Cards;
using ApplicationClient.Responses.Database;
using ApplicationClient.Services.ApplicationResponseHandler;
using Domain.Entities.Card.Currencies;
using Domain.Entities.Card.Model;
using Domain.Entities.Card.Statuses;
using Domain.Entities.Card.Types;
using InfrastructureClient.Interfaces.KafkaProducer;

using Microsoft.Extensions.Logging;
using System.Diagnostics;

public class ServicesOrchestratorCards : InterfacesServicesOrchestrators
{
    private readonly InterfacesKafkaProducer _producer;
    private readonly ServicesApplicationResponseHandler _responseHandler;
    private readonly string _commandTopic;
    private readonly ILogger<ServicesOrchestratorCards> _logger;

    public ServicesOrchestratorCards(InterfacesKafkaProducer Producer, ServicesApplicationResponseHandler ResponseHandler, string CommandTopic, ILogger<ServicesOrchestratorCards> Logger = null)
    {
        _producer = Producer;
        _responseHandler = ResponseHandler;
        _commandTopic = CommandTopic;
        _logger = Logger;
    }

    public async Task<TResponse> Execute<TCommand, TResponse>(TCommand Command)
    {
        if (Command is not CommandsCards cardCommand) { throw new ArgumentException("The command data type is incorrect!"); }

        var stopwatch = Stopwatch.StartNew();
        var correlationId = cardCommand.CorrelationId;

        try
        {
            _logger?.LogInformation("Processing cards for users with id: {UserId}", cardCommand.UserId);

            using var cts = new CancellationTokenSource(TimeSpan.FromSeconds(10));
            var responseTask = _responseHandler.RegisterPendingResponse(correlationId);

            await _producer.ProduceAsync(_commandTopic, cardCommand);

            ResponsesDatabase databaseResponse;
            try { databaseResponse = await responseTask.WaitAsync(cts.Token); }
            catch (OperationCanceledException)
            {
                var timeoutResponse = new ResponsesCards
                {
                    Success = false,
                    Error = "Timeout",
                    Message = "Processing timed out",
                    CorrelationId = correlationId
                };

                if (timeoutResponse is TResponse typedTimeoutResponse) return typedTimeoutResponse;
                throw new InvalidCastException($"Cannot convert response to type {typeof(TResponse).Name}");
            }

            _logger?.LogInformation("Processing completed in {ElapsedMs}ms", stopwatch.ElapsedMilliseconds);

            List<EntitiesCard>? cards = null;
            List<EntitiesCardStatuses>? cardStatuses = null;
            List<EntitiesCardTypes>? cardTypes = null;
            List<EntitiesCardCurrencies>? cardCurrencies = null;

            try
            {
                string json = null!;

                if (databaseResponse.Data != null)
                {
                    if (databaseResponse.Data is System.Text.Json.JsonElement text) { json = text.GetRawText(); }
                    else { json = databaseResponse.Data.ToString() ?? string.Empty; }
                }

                if (!string.IsNullOrWhiteSpace(json))
                {
                    try
                    {
                        var response = System.Text.Json.JsonSerializer.Deserialize<ResponsesCards>(json);
                        if (response != null)
                        {
                            cards = response.Cards ?? new List<EntitiesCard>();
                            cardStatuses = response.Statuses ?? new List<EntitiesCardStatuses>();
                            cardTypes = response.Types ?? new List<EntitiesCardTypes>();
                            cardCurrencies = response.Currencies ?? new List<EntitiesCardCurrencies>();
                        }
                    }
                    catch (Exception E) { _logger?.LogError(E, "Failed to deserialize cards payload as ResponsesCards - fallback to empty lists"); }
                }
            }
            catch (Exception E) { _logger?.LogError(E, "Failed to deserialize user data from card response"); }

            var cardResponse = new ResponsesCards
            {
                Success = databaseResponse.Success,
                Message = databaseResponse.Message,
                Error = databaseResponse.Error,
                Cards = cards ?? new List<EntitiesCard>(),
                Statuses = cardStatuses ?? new List<EntitiesCardStatuses>(),
                Types = cardTypes ?? new List<EntitiesCardTypes>(),
                Currencies = cardCurrencies ?? new List<EntitiesCardCurrencies>(),
                CorrelationId = correlationId
            };

            if (cardResponse is TResponse typedResponse) return typedResponse;
            throw new InvalidCastException($"Cannot convert response to type {typeof(TResponse).Name}");
        }
        catch (Exception E)
        {
            _logger?.LogError(E, "Error processing cards");
            var errorResponse = new ResponsesCards
            {
                Success = false,
                Error = E.Message,
                Message = "Processing failed",
                CorrelationId = correlationId
            };

            if (errorResponse is TResponse typedErrorResponse) return typedErrorResponse;
            throw new InvalidCastException($"Cannot convert response to type {typeof(TResponse).Name}");
        }
    }
}