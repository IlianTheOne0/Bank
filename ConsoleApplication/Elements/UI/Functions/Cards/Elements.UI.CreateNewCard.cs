namespace ConsoleApplication.Elements.UI.Functions.Cards.New;

using ApplicationClient.Commands.Cards;
using ApplicationClient.Responses.Auth;
using ApplicationClient.Responses.Cards;
using ApplicationClient.Services.Orchestrators.Auth;
using ApplicationClient.Services.Orchestrators.Cards;
using ConsoleApplication.Elements.Menu;
using ConsoleApplication.Elements.UI.StartupMenu;
using ConsoleApplication.Elements.UI.StatusMenus.Error;
using ConsoleApplication.Elements.UI.StatusMenus.Processing;
using ConsoleApplication.Elements.UI.StatusMenus.Success;
using Domain.Entities.Card.Currencies;
using Domain.Entities.Card.Model;
using Domain.Entities.Card.Types;
using Domain.Entities.User.Model;
using Microsoft.Extensions.DependencyInjection;

internal class ElementsUIFunctionsCreateNewCard
{
    public static async Task CreateNewCardMenu(IServiceProvider Services, List<EntitiesCardTypes> CardTypes, List<EntitiesCardCurrencies> CardCurrencies, Guid UserId)
    {
        string selectedCurrency = "";
        string selectedCardType = "";
        
        while (true)
        {
            var newCardMenu = new ElementsMenu($"New Card")
            {
                BorderColor = ConsoleColor.DarkCyan,
                TitleColor = ConsoleColor.Cyan,
                OptionColor = ConsoleColor.White,
                HighlightColor = ConsoleColor.Black,
                HighlightBackground = ConsoleColor.Cyan
            };

            newCardMenu.Options.Add
            (
                new ElementsMenuOption
                (
                    $"Currency: {(string.IsNullOrEmpty(selectedCurrency) ? "<not set>" : selectedCurrency)}",
                    async () =>
                    {
                        var pick = new ElementsMenu("Select currency");
                        foreach (var currency in CardCurrencies) { pick.Options.Add(new ElementsMenuOption(currency.Currency.ToUpper(), () => { selectedCurrency = currency.Currency.ToUpper(); return Task.CompletedTask; })); }
                        pick.Options.Add(new ElementsMenuOption("Back", () => Task.CompletedTask));
                        int choice = await MenuRenderer.Render(pick);
                        return;
                    }
                )
            );

            newCardMenu.Options.Add
            (
                new ElementsMenuOption
                (
                    $"Card Type: {(string.IsNullOrEmpty(selectedCardType) ? "<not set>" : selectedCardType)}", async () =>
                    {
                        var pick = new ElementsMenu("Select card type");
                        foreach (var type in CardTypes) { pick.Options.Add(new ElementsMenuOption(type.Type, () => { selectedCardType = type.Type; return Task.CompletedTask; })); }
                        pick.Options.Add(new ElementsMenuOption("Back", () => Task.CompletedTask));
                        int choice = await MenuRenderer.Render(pick);
                        return;
                    }
                )
            );

            var pinInput = new ElementsMenuInputOption("PIN", MaxLength: 4, IsPassword: true);
            newCardMenu.Options.Add(pinInput);

            newCardMenu.Options.Add
            (
                new ElementsMenuOption
                (
                    "Create",
                    async () =>
                    {
                        if (string.IsNullOrEmpty(selectedCurrency) || string.IsNullOrEmpty(selectedCardType)) { await StatusMenusError.Execute("Please select both currency and card type before creating a card"); return; }
                        if (string.IsNullOrEmpty(pinInput.Input) || pinInput.Input.Length != 4) { await StatusMenusError.Execute("PIN must be exactly 4 digits"); return; }

                        if (Services == null) { throw new ArgumentNullException(nameof(Services)); }

                        var cmd = new CommandsCards
                        {
                            CorrelationId = Guid.NewGuid(),
                            UserId = UserId,
                            NewCard = new CommandsNewCard
                            {
                                Currency = CardCurrencies.First(provider => provider.Currency.Equals(selectedCurrency, StringComparison.OrdinalIgnoreCase)),
                                Type = CardTypes.First(provider => provider.Type.Equals(selectedCardType, StringComparison.OrdinalIgnoreCase)),
                                Pin = pinInput.Input
                            }
                        };

                        await StatusMenusProcessing.Execute(async () => { await Task.Delay(TimeSpan.FromMilliseconds(50)); });
                        var result = await ProcessNewCard(Services, cmd);
                        await StatusMenusSuccess.Execute("Card registered successfully");
                        return;
                    }
                )
            );

            newCardMenu.Options.Add(new ElementsMenuOption("Back", () => Task.CompletedTask));
        

            int choice = await MenuRenderer.Render(newCardMenu);
            if (choice == newCardMenu.Options.Count - 1 || choice == newCardMenu.Options.Count - 2) { break; }
        }
    }

    private static async Task<ResponsesCards> ProcessNewCard(IServiceProvider Services, CommandsCards Command)
    {
        try
        {
            if (Services == null) { throw new ArgumentNullException(nameof(Services)); }

            using var scope = Services.CreateScope();
            var cardsOrchestrator = scope.ServiceProvider.GetRequiredService<ServicesOrchestratorCards>();

            if (cardsOrchestrator == null) { throw new InvalidOperationException("Card orchestrator service is not available"); }

            return await cardsOrchestrator.Execute<CommandsCards, ResponsesCards>(Command);
        }
        catch (Exception E)
        {
            Console.WriteLine($"Error during signin process: {E.Message}");
            return new ResponsesCards { Success = false, Error = E.Message, Message = "Signin process failed" };
        }
    }
}