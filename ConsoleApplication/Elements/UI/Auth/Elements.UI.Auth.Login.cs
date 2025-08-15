namespace ConsoleApplication.Elements.UI.Auth.Login;

using ConsoleApplication.Elements.Menu;
using ConsoleApplication.Elements.UI.StatusMenus.Error;
using ConsoleApplication.Elements.UI.StatusMenus.Processing;

using ApplicationClient.Commands.Auth;
using ApplicationClient.Responses.Auth;
using ApplicationClient.Services.Orchestrators.Auth;

using Domain.Entities.User.Model;

using Microsoft.Extensions.DependencyInjection;


internal class ElementsUiAuthLogin
{
    public static async Task<EntitiesUser?> ShowLoginMenu(IServiceProvider Services)
    {
        EntitiesUser user = null!;

        var loginMenu = new ElementsMenu("Login")
        {
            BorderColor = ConsoleColor.DarkYellow,
            TitleColor = ConsoleColor.Yellow,
            OptionColor = ConsoleColor.White,
            HighlightColor = ConsoleColor.Black,
            HighlightBackground = ConsoleColor.Yellow,
            InputColor = ConsoleColor.Black
        };

        loginMenu.Options.Add(new ElementsMenuInputOption("Username"));
        loginMenu.Options.Add(new ElementsMenuInputOption("Password", IsPassword: true));
        loginMenu.Options.Add(new ElementsMenuOption("Login",
            async () =>
            {
                await StatusMenusProcessing.Execute
                (
                    async () =>
                    {
                        var username = ((ElementsMenuInputOption)loginMenu.Options[0]).Input;
                        var password = ((ElementsMenuInputOption)loginMenu.Options[1]).Input;

                        var result = await ProcessLogin(Services, username, password);
                        if (result.Success)
                        {
                            user = new EntitiesUser { Id = result.UserId, FullName = username };
                        }
                        else { await StatusMenusError.Execute($"Login failed: {result.Error}"); }
                    }
                );
            }
        ));
        loginMenu.Options.Add(new ElementsMenuOption("Back", () => { }));

        int choice = await MenuRenderer.Render(loginMenu);

        if (choice == 3) { return null; }

        return user;
    }

    private static async Task<ResponsesAuth> ProcessLogin(IServiceProvider Services, string Username, string Password)
    {
        try
        {
            if (Services == null) { throw new ArgumentNullException(nameof(Services)); }

            var cmd = new CommandsAuth { CorrelationId = Guid.NewGuid(), Username = Username, Password = Password, };

            using var scope = Services.CreateScope();
            var authOrchestrator = scope.ServiceProvider.GetRequiredService<ServicesOrchestratorAuth>();

            if (authOrchestrator == null) { throw new InvalidOperationException("Auth orchestrator service is not available"); }

            return await authOrchestrator.Execute<CommandsAuth, ResponsesAuth>(cmd);
        }
        catch (Exception E)
        {
            Console.WriteLine($"Error during login process: {E.Message}");
            return new ResponsesAuth { Success = false, Error = E.Message, Message = "Login process failed" };
        }
    }
}