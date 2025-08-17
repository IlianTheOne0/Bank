namespace ConsoleApplication.Elements.UI.Functions.Cards.View;

using ApplicationClient.Responses.Cards;
using ConsoleApplication.Elements.Menu;
using ConsoleApplication.Elements.UI.StatusMenus.Processing;
using Domain.Entities.Card.Currencies;
using Domain.Entities.Card.Model;
using Domain.Entities.Card.Statuses;
using Domain.Entities.Card.Types;

internal class ElementsUIFunctionsViewCards
{
    public static async Task ShowViewCardsMenu(EntitiesCard Card)
    {
        var viewCardMenu = new ElementsMenu(Card.CardNumber)
        {
            BorderColor = ConsoleColor.DarkCyan,
            TitleColor = ConsoleColor.Cyan,
            OptionColor = ConsoleColor.White,
            HighlightColor = ConsoleColor.Black,
            HighlightBackground = ConsoleColor.Cyan
        };

        viewCardMenu.Options.Add(new ElementsMenuOption("Back", () => { }));

        while (true)
        {
            int choice = await MenuRenderer.Render(viewCardMenu);
            if (choice == viewCardMenu.Options.Count - 1) { break; }
        }
    }
}