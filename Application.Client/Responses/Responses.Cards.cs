namespace ApplicationClient.Responses.Cards;

using ApplicationClient.Responses.Base;
using Domain.Entities.Card.Currencies;
using Domain.Entities.Card.Model;
using Domain.Entities.Card.Statuses;
using Domain.Entities.Card.Types;

public class ResponsesCards : ResponsesBase
{
    public string Token { get; set; }
    public List<EntitiesCard> Cards { get; set; }
    public List<EntitiesCardStatuses> Statuses { get; set; }
    public List<EntitiesCardTypes> Types { get; set; }
    public List<EntitiesCardCurrencies> Currencies { get; set; }
}