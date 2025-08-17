using InfrastructureServer.Models.Card.Currencies;
using InfrastructureServer.Models.Card.Statuses;
using InfrastructureServer.Models.Card.Types;

namespace Application.Server.Commands;

using ApplicationServer.Commands.Base;

public class CommandsCards : CommandsBase
{
    public Guid UserId { get; set; }
    public CommandsNewCard? NewCard { get; set; } = null;
}

public class CommandsNewCard
{
    public string Pin { get; set; }
    public ModelsCardCurrencies Currency { get; set; }
    public ModelsCardStatuses Status { get; set; }
    public ModelsCardTypes Type { get; set; }
}