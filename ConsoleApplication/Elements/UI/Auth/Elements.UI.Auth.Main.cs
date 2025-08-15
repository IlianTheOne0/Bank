namespace ConsoleApplication.Elements.UI.Auth;

using ConsoleApplication.Elements.Menu;
using ConsoleApplication.Elements.UI.Auth.Login;

using Domain.Entities.User.Model;

internal class ElementsUiAuthMain
{
    public static async Task<EntitiesUser?> ShowAuthMenu(IServiceProvider Services)
    {
        EntitiesUser? user = null;

        while (user == null)
        {
            var authMenu = new ElementsMenu("Authentication")
            {
                BorderColor = ConsoleColor.DarkYellow,
                TitleColor = ConsoleColor.Yellow,
                OptionColor = ConsoleColor.White,
                HighlightColor = ConsoleColor.Black,
                HighlightBackground = ConsoleColor.Yellow
            };

            authMenu.Options.Add(new ElementsMenuOption("Login", () => { }));
            authMenu.Options.Add(new ElementsMenuOption("Register", () => { }));
            authMenu.Options.Add(new ElementsMenuOption("Exit", () => Environment.Exit(0)));

            Console.Clear();
            int choice = await MenuRenderer.Render(authMenu);

            switch (choice)
            {
                case 0:
                {
                    user = await ElementsUiAuthLogin.ShowLoginMenu(Services);
                    if (user == null) { continue; }
                } break;
                case 1: { } break;
            }
        }

        return user;
    }
}