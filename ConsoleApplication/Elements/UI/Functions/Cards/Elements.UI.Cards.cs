namespace ConsoleApplication.Elements.UI.Functions.Cards;

using ApplicationClient.Commands.Cards;
using ApplicationClient.Responses.Auth;
using ApplicationClient.Responses.Cards;
using ApplicationClient.Services.Orchestrators.Auth;
using ApplicationClient.Services.Orchestrators.Cards;
using ConsoleApplication.Elements.Menu;
using ConsoleApplication.Elements.UI.Functions.Cards.New;
using ConsoleApplication.Elements.UI.Functions.Cards.View;
using ConsoleApplication.Elements.UI.StartupMenu;
using ConsoleApplication.Elements.UI.StatusMenus.Error;
using ConsoleApplication.Elements.UI.StatusMenus.Processing;
using Domain.Entities.Card.Currencies;
using Domain.Entities.Card.Model;
using Domain.Entities.Card.Statuses;
using Domain.Entities.Card.Types;
using Domain.Entities.User.Model;
using Microsoft.EntityFrameworkCore.Diagnostics;
using Microsoft.Extensions.DependencyInjection;

internal class ElementsUIFunctionsCards
{
    public static async Task ShowCardsMenu(IServiceProvider Services, Guid UserId)
    {
        while (true)
        {
                var cardsMenu = new ElementsMenu($"Cards")
            {
                BorderColor = ConsoleColor.DarkCyan,
                TitleColor = ConsoleColor.Cyan,
                OptionColor = ConsoleColor.White,
                HighlightColor = ConsoleColor.Black,
                HighlightBackground = ConsoleColor.Cyan
            };

            ResponsesCards request = null;
            List<EntitiesCard> cards = new List<EntitiesCard>();
            List<EntitiesCardTypes> cardTypes = new List<EntitiesCardTypes>();
            List<EntitiesCardStatuses> cardStatuses = new List<EntitiesCardStatuses>();
            List<EntitiesCardCurrencies> cardCurrencies = new List<EntitiesCardCurrencies>();

            await StatusMenusProcessing.Execute(async () => { request = await GetCards(Services, UserId); }, "Loading cards...");
            
            cards = request.Cards;
            cardTypes = request.Types;
            cardStatuses = request.Statuses;
            cardCurrencies = request.Currencies;

            foreach (EntitiesCard card in cards) { cardsMenu.Options.Add(new ElementsMenuOption(card.CardNumber, () => { })); }
            cardsMenu.Options.Add(new ElementsMenuOption("Add New", async () => { await ElementsUIFunctionsCreateNewCard.CreateNewCardMenu(Services, cardTypes, cardCurrencies, UserId);  }));
            cardsMenu.Options.Add(new ElementsMenuOption("Back", () => { }));
        
            int choice = await MenuRenderer.Render(cardsMenu);

            if (choice == cardsMenu.Options.Count - 1) { break; }
            else if (choice == cardsMenu.Options.Count - 2) { continue; }
            else { await ElementsUIFunctionsViewCards.ShowViewCardsMenu(cards[choice]); }
        }
    }

    private static async Task<ResponsesCards> GetCards(IServiceProvider Services, Guid UserId)
    {
        try
        {
            if (Services == null) { throw new ArgumentNullException(nameof(Services)); }

            var cmd = new CommandsCards { CorrelationId = Guid.NewGuid(), UserId = UserId };
            
            using var scope = Services.CreateScope();
            var cardsOrchestrator = scope.ServiceProvider.GetRequiredService<ServicesOrchestratorCards>();

            if (cardsOrchestrator == null) { throw new InvalidOperationException("Cards orchestrator service is not available"); }

            ResponsesCards result = await cardsOrchestrator.Execute<CommandsCards, ResponsesCards>(cmd);
            if (result.Success) { return result; }
            await StatusMenusError.Execute(result.Message);
            return result;
        }
        catch (Exception E) { await StatusMenusError.Execute("Error during checks", E.Message); return null!; }
    }
}