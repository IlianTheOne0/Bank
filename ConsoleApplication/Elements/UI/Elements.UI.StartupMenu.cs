namespace ConsoleApplication.Elements.UI.StartupMenu;

using ConsoleApplication.Elements.UI.Auth;
using ConsoleApplication.Elements.UI.MainMenu;

using Domain.Entities.User.Model;

internal class ElementsUIStartupMenu
{
    public static async Task<int> RunAsync(IServiceProvider Services)
    {
        try
        {
            Console.Clear();
            while (true)
            {
                EntitiesUser? user = await ElementsUIAuthMain.ShowAuthMenu(Services);
                if (user is null) { return 1; }
                ElementsUIMainMenu.SetUser(user);
                await ElementsUIMainMenu.ShowMainMenu(Services);
            }
        }
        catch (Exception) { return 1; }
    }
}