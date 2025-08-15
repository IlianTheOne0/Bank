namespace ConsoleApplication.Elements.UI.StatusMenus.Success;

using ConsoleApplication.Elements.Menu;

internal static class StatusMenusSuccess
{
    private static ElementsMenu CreateSuccessMenu(string Message, string ContinueText)
    {
        var menu = new ElementsMenu("Success")
        {
            BorderColor = ConsoleColor.DarkGreen,
            TitleColor = ConsoleColor.Green,
            OptionColor = ConsoleColor.Gray,
            HighlightBackground = ConsoleColor.Green,
            HighlightColor = ConsoleColor.White
        };

        menu.Options.Add(new ElementsMenuOption(Message));
        menu.Options.Add(new ElementsMenuOption(ContinueText));
        return menu;
    }

    public static async Task<bool> Execute(string Message = "Operation completed successfully!", string ContinueText = "Continue")
    {
        var menu = CreateSuccessMenu(Message, ContinueText);
        return await MenuRenderer.Render(menu) == 1;
    }
}