namespace ConsoleApplication.Elements.UI.StatusMenus.Error;

using ConsoleApplication.Elements.Menu;

internal static class StatusMenusError
{
    private static ElementsMenu CreateErrorMenu(string ErrorMessage, string ContinueText)
    {
        var menu = new ElementsMenu("Error")
        {
            BorderColor = ConsoleColor.DarkRed,
            TitleColor = ConsoleColor.Red,
            OptionColor = ConsoleColor.Gray,
            HighlightBackground = ConsoleColor.Red,
            HighlightColor = ConsoleColor.White
        };

        var messageLines = SplitMessage(ErrorMessage, 50);
        foreach (var line in messageLines) { menu.Options.Add(new ElementsMenuOption(line)); }

        menu.Options.Add(new ElementsMenuOption(ContinueText));
        return menu;
    }

    private static List<string> SplitMessage(string Message, int MaxLineLength)
    {
        var lines = new List<string>();
        var words = Message.Split(' ');
        var currentLine = "";

        foreach (var word in words)
        {
            if (currentLine.Length + word.Length + 1 > MaxLineLength) { lines.Add(currentLine.Trim()); currentLine = ""; }
            currentLine += word + " ";
        }

        if (!string.IsNullOrWhiteSpace(currentLine)) { lines.Add(currentLine.Trim()); }

        return lines;
    }

    public static async Task<bool> Execute(string ErrorMessage, string ContinueText = "Continue")
    {
        var menu = CreateErrorMenu(ErrorMessage, ContinueText);
        return await MenuRenderer.Render(menu) == menu.Options.Count - 1;
    }
}