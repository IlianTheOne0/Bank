namespace ConsoleApplication.Elements.UI.Auth.Signin;

using ApplicationClient.Commands.Auth;
using ApplicationClient.Responses.Auth;
using ApplicationClient.Services.Orchestrators.Auth;
using ConsoleApplication.Elements.Menu;
using ConsoleApplication.Elements.UI.StatusMenus.Error;
using ConsoleApplication.Elements.UI.StatusMenus.Processing;
using ConsoleApplication.Elements.UI.StatusMenus.Success;
using Domain.Entities.User.Model;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

internal static class ElementsUIAuthSignin
{
    public static async Task<EntitiesUser?> ShowSigninMenu(IServiceProvider Services)
    {
        EntitiesUser? createdUser = null;

        var signinMenu = new ElementsMenu("Signin")
        {
            BorderColor = ConsoleColor.DarkYellow,
            TitleColor = ConsoleColor.Yellow,
            OptionColor = ConsoleColor.White,
            HighlightColor = ConsoleColor.Black,
            HighlightBackground = ConsoleColor.Yellow,
            InputColor = ConsoleColor.Black,
        };

        var fullNameInput = new ElementsMenuInputOption("Full Name", MaxLength: 60);
        var phoneInput = new ElementsMenuInputOption("Phone Number", MaxLength: 20);
        var emailInput = new ElementsMenuInputOption("Email", MaxLength: 80);
        var usernameInput = new ElementsMenuInputOption("Username", MaxLength: 30);
        var dateOfBirthInput = new ElementsMenuInputOption("Date Of Birth", MaxLength: 10);
        var sexInput = new ElementsMenuInputOption("Sex", MaxLength: 6);
        var passwordInput = new ElementsMenuInputOption("Password", MaxLength: 32, IsPassword: true);
        var passwordRepeatInput = new ElementsMenuInputOption("Password (Repeat)", MaxLength: 32, IsPassword: true);

        signinMenu.Options.Add(fullNameInput);
        signinMenu.Options.Add(phoneInput);
        signinMenu.Options.Add(emailInput);
        signinMenu.Options.Add(usernameInput);
        signinMenu.Options.Add(dateOfBirthInput);
        signinMenu.Options.Add(sexInput);
        signinMenu.Options.Add(passwordInput);
        signinMenu.Options.Add(passwordRepeatInput);

        signinMenu.Options.Add(new ElementsMenuOption
        (
            "Submit",
            async () =>
            {
                string fullName = (fullNameInput.Input ?? string.Empty).Trim();
                string phone = (phoneInput.Input ?? string.Empty).Trim();
                string email = (emailInput.Input ?? string.Empty).Trim();
                string username = (usernameInput.Input ?? string.Empty).Trim();
                string dateOfBirthStr = (dateOfBirthInput.Input ?? string.Empty).Trim();
                string sexStr = (sexInput.Input ?? string.Empty).Trim();
                string password = passwordInput.Input ?? string.Empty;
                string passwordRepeat = passwordRepeatInput.Input ?? string.Empty;

                var errors = new List<string>();

                if (string.IsNullOrEmpty(fullName)) { errors.Add("Full name is required"); }
                if (string.IsNullOrEmpty(phone) || !System.Text.RegularExpressions.Regex.IsMatch(phone, @"^\+?\d{7,15}$")) { errors.Add("Phone number invalid (7-15 digits, optional leading +)"); }
                if (string.IsNullOrEmpty(email) || !System.Text.RegularExpressions.Regex.IsMatch(email, @"^[^@\s]+@[^@\s]+\.[^@\s]+$")) { errors.Add("Email invalid"); }
                if (string.IsNullOrEmpty(username) || username.Length < 3) { errors.Add("Username required (min 3 chars)"); }
                if (!DateTime.TryParse(dateOfBirthStr, out DateTime dateOfBirth)) { errors.Add("Date of birth invalid (use a recognizable date format)"); }

                bool? isMale = null;
                if (!string.IsNullOrEmpty(sexStr))
                {
                    var sex = sexStr.Trim().ToLowerInvariant();
                    if (sex == "m" || sex == "male" || sex == "true") { isMale = true; }
                    else if (sex == "f" || sex == "female" || sex == "false") { isMale = false; }
                    else { errors.Add("Sex must be 'm' or 'f' (or male/female)"); }
                }
                else { errors.Add("Sex is required"); }

                if (string.IsNullOrEmpty(password) || password.Length < 6) { errors.Add("Password required (min 6 chars)"); }
                if (password != passwordRepeat) { errors.Add("Passwords do not match"); }

                if (errors.Count > 0) { await StatusMenusError.Execute(string.Join("  |  ", errors)); return; }

                await StatusMenusProcessing.Execute(async () => { await Task.Delay(TimeSpan.FromMilliseconds(50)); });

                var cmd = new CommandsAuth
                {
                    CorrelationId = Guid.NewGuid(),
                    NewUser = new CommandsAuthSignIn
                    {
                        Id = Guid.NewGuid(),
                        FullName = fullName,
                        Email = email,
                        PhoneNumber = phone,
                        Username = username,
                        Sex = isMale!.Value,
                        DateOfBirth = dateOfBirth,
                        CreatedAt = DateTime.Now,
                        UpdatedAt = DateTime.Now,
                        Password = password
                    }
                };

                await StatusMenusProcessing.Execute
                (
                    async () =>
                    {
                        var result = await ProcessSignin(Services, cmd);

                        if (result.Success)
                        {
                            createdUser = result.User;
                            await StatusMenusSuccess.Execute("User created successfully");
                        }
                        else { await StatusMenusError.Execute($"Signin failed: {result.Message}"); }
                    }
                );
            }
        ));

        signinMenu.Options.Add(new ElementsMenuOption("Cancel", () => Task.CompletedTask));

        while (createdUser == null)
        {
            int choice = await MenuRenderer.Render(signinMenu);

            if (choice == signinMenu.Options.Count - 1) { return null; }
        }
        return createdUser;
    }

    private static async Task<ResponsesAuth> ProcessSignin(IServiceProvider Services, CommandsAuth Command)
    {
        try
        {
            if (Services == null) { throw new ArgumentNullException(nameof(Services)); }

            using var scope = Services.CreateScope();
            var authOrchestrator = scope.ServiceProvider.GetRequiredService<ServicesOrchestratorAuth>();

            if (authOrchestrator == null) { throw new InvalidOperationException("Auth orchestrator service is not available"); }

            return await authOrchestrator.Execute<CommandsAuth, ResponsesAuth>(Command);
        }
        catch (Exception E)
        {
            Console.WriteLine($"Error during signin process: {E.Message}");
            return new ResponsesAuth { Success = false, Error = E.Message, Message = "Signin process failed" };
        }
    }
}