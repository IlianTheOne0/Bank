namespace ConsoleApplication.Elements.UI.MainMenu;

using ConsoleApplication.Elements.Menu;
using ConsoleApplication.Elements.UI.Functions.Cards;
using ConsoleApplication.Elements.UI.StatusMenus.Processing;
using Domain.Entities.User.Model;

internal class ElementsUIMainMenu
{
    private static EntitiesUser? _user;

    public static void SetUser(EntitiesUser? User) => _user = User;
    
    public static async Task ShowMainMenu(IServiceProvider Services)
    {
        
        
        var mainMenu = new ElementsMenu($"Welcome, {_user!.FullName}")
        {
            BorderColor = ConsoleColor.DarkCyan,
            TitleColor = ConsoleColor.Cyan,
            OptionColor = ConsoleColor.White,
            HighlightColor = ConsoleColor.Black,
            HighlightBackground = ConsoleColor.Cyan
        };

        mainMenu.Options.Add(new ElementsMenuOption("View Cards", async () => { await ElementsUIFunctionsCards.ShowCardsMenu(Services, _user!.Id); }));
        mainMenu.Options.Add(new ElementsMenuOption("Logout", () => { _user = null; }));
        mainMenu.Options.Add(new ElementsMenuOption("Exit", () => Environment.Exit(0)));

        while (_user != null) { await MenuRenderer.Render(mainMenu); }
    }
}