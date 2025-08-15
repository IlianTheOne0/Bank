namespace ConsoleApplication.Elements.UI.StatusMenus.Processing;

using ConsoleApplication.Elements.Menu;

internal static class StatusMenusProcessing
{
    private static ElementsMenu CreateProcessingMenu(string Message)
    {
        var menu = new ElementsMenu("Processing")
        {
            BorderColor = ConsoleColor.DarkCyan,
            TitleColor = ConsoleColor.Cyan,
            OptionColor = ConsoleColor.Gray
        };

        menu.Options.Add(new ElementsMenuOption(Message));
        return menu;
    }

    public static async Task Execute(Func<Task> Operation, string ProcessingMessage = "Data is processing, please wait...")
    {
        var menu = CreateProcessingMenu(ProcessingMessage);
        var renderTask = MenuRenderer.Render(menu);
        var operationTask = Operation();
        await Task.WhenAll(renderTask, operationTask);
    }
}