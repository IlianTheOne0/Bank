namespace ApplicationClient.Commands.Cards;

using ApplicationClient.Commands.Base;
using Domain.Entities.Card.Currencies;
using Domain.Entities.Card.Statuses;
using Domain.Entities.Card.Types;

public class CommandsCards : CommandsBase
{
    public Guid UserId { get; set; }
    public CommandsNewCard? NewCard { get; set; } = null;
}

public class CommandsNewCard
{
    public string Pin { get; set; }
    public EntitiesCardCurrencies Currency { get; set; }
    public EntitiesCardStatuses Status { get; set; }
    public EntitiesCardTypes Type { get; set; }
}