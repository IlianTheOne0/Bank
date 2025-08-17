namespace Database.CommandsHandler.Transactions;

using Application.Server.Commands;
using ApplicationServer.Responses.Database;
using Database.Interfaces.CommandsHandler;
using Database.Interfaces.Repositories.Supabase.Commands;
using Infrastructure.Server.Interfaces.Utils.Hasher;
using InfrastructureServer.Models.Card.Currencies;
using InfrastructureServer.Models.Card.Model;
using InfrastructureServer.Models.Card.Statuses;
using InfrastructureServer.Models.Card.Types;
using InfrastructureServer.Utils.Hasher;
using Microsoft.Extensions.Logging;
using System;
using System.Diagnostics;
using System.Security.Cryptography;
using static Supabase.Postgrest.Constants;

public class CommandsHandlerCards : InterfacesCommandsHandler
{
    private readonly InterfacesRepositoriesSupabaseCommands _repositorySupabase;
    private readonly InterfacesUtilsHasher _hasher;
    private readonly ILogger<CommandsHandlerCards> _logger;
    public CommandsHandlerCards(InterfacesRepositoriesSupabaseCommands RepositorySupabase, InterfacesUtilsHasher Hasher, ILogger<CommandsHandlerCards> Logger = null!)
    {
        _repositorySupabase = RepositorySupabase ?? throw new ArgumentNullException(nameof(RepositorySupabase), "Supabase commands repository cannot be null. Please provide a valid repository instance.");
        _hasher = Hasher;
        _logger = Logger;
    }

    public async Task<ResponsesDatabase> Handle<TModel>(TModel Command)
    {
        var stopwatch = Stopwatch.StartNew();
        string modelType = typeof(TModel).Name;
        ResponsesDatabase response;

        try
        {
            _logger?.LogDebug($"Starting auth handling for {modelType}");

            if (Command == null) { throw new ArgumentNullException($"Cannot process null {modelType} command. Please provide a valid command instance.", nameof(Command)); }

            if (Command is CommandsCards cards)
            {
                if (cards.NewCard != null) { response = await HandleNewCard(cards); }
                else { response = await HandleCards(cards); }
            }
            else { throw new NotSupportedException($"Command type {modelType} is not supported by this handler. This handler only processes ModelsTransaction commands."); }

            _logger?.LogInformation($"Successfully processed {modelType} command in {stopwatch.ElapsedMilliseconds}ms");

            return response;
        }
        catch (Exception E)
        {
            _logger?.LogError($"Failed to process {modelType} command after {stopwatch.ElapsedMilliseconds}ms. Error: {E.Message}", E);
            throw;
        }
    }

    private async Task<ResponsesDatabase> HandleCards(CommandsCards Cards)
    {
        var cardsTableResult = await _repositorySupabase.FilterAsync<ModelsCard>("UserId", Operator.Equals, Cards.UserId.ToString());
        var statusesTableResult = await _repositorySupabase.GetAllAsync<ModelsCardStatuses>();
        var typesTableResult = await _repositorySupabase.GetAllAsync<ModelsCardTypes>();
        var currenciesTableResult = await _repositorySupabase.GetAllAsync<ModelsCardCurrencies>();

        object payload = new
        {
            Cards = cardsTableResult,
            Statuses = statusesTableResult,
            Types = typesTableResult,
            Currencies = currenciesTableResult
        };

        if (cardsTableResult == null) { return ResponsesDatabase.Fail("Argument null Error", $"The user with id {Cards.UserId} did not open any cards.", payload); }
        if (cardsTableResult.Count == 0) { return ResponsesDatabase.Fail("Argument null Error", $"The user with id {Cards.UserId} did not open any cards.", payload); }

        _logger?.LogDebug($"Processed cards for user (Id: {Cards.UserId.ToString() ?? "N/A"})");
        return ResponsesDatabase.Ok(payload);
    }

    private async Task<ResponsesDatabase> HandleNewCard(CommandsCards Card)
    {
        var cardStatuses = _repositorySupabase.GetAllAsync<ModelsCardStatuses>();

        ModelsCard newCard = new ModelsCard
        {
            Balance = 0,
            CardNumber = string.Join(" ", Enumerable.Range(0, 4).Select(_ => string.Concat(Enumerable.Range(0, 4).Select(__ => new Random().Next(0, 10).ToString())))),
            CVV = (ushort)RandomNumberGenerator.GetInt32(100, 1000),
            IssueDate = DateTime.Now,
            ExpirationDate = DateTime.Now.AddYears(5),
            CurrencyId = Card.NewCard.Currency.Id,
            UserId = Card.UserId,
            TypeId = Card.NewCard.Type.Id,
            StatusId = cardStatuses.Result.FirstOrDefault(provider => provider.Status.Contains("Active"))!.Id,
            PinHash = _hasher.Hash(Card.NewCard.Pin)
        };

        await _repositorySupabase.InsertAsync<ModelsCard>(newCard);
        return ResponsesDatabase.Ok(newCard);
    }
}