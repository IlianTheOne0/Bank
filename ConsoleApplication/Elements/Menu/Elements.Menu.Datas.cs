namespace ConsoleApplication.Elements.Menu;

using System;
using System.Collections.Generic;

internal class ElementsMenuOption
{
    public string Text { get; }
    public Action? Action { get; }
    public Func<Task>? AsyncAction { get; }

    public ElementsMenuOption(string Text, Action? Action = null) { this.Text = Text; this.Action = Action; }

    public ElementsMenuOption(string Text, Func<Task> AsyncAction) { this.Text = Text; this.AsyncAction = AsyncAction; }
}

internal class ElementsMenuInputOption : ElementsMenuOption
{
    public string Input { get; set; }
    public int MaxLength { get; }
    public bool IsPassword { get; }

    public ElementsMenuInputOption(string Text, int MaxLength = 20, bool IsPassword = false, Action? Action = null)
        : base(Text, Action)
    {
        Input = "";
        this.MaxLength = MaxLength;
        this.IsPassword = IsPassword;
    }
}

internal class ElementsMenuActionOption : ElementsMenuOption
{
    public Func<bool>? ActionReturningBool { get; }
    public Func<Task<bool>>? AsyncActionReturningBool { get; }

    public ElementsMenuActionOption(string text, Func<bool> actionReturningBool) : base(text) => ActionReturningBool = actionReturningBool;
    public ElementsMenuActionOption(string text, Func<Task<bool>> asyncActionReturningBool) : base(text) => AsyncActionReturningBool = asyncActionReturningBool;
}

internal class ElementsMenu
{
    public string Title { get; }
    
    public List<ElementsMenuOption> Options { get; } = new List<ElementsMenuOption>();
    
    public ConsoleColor BorderColor { get; set; } = ConsoleColor.White;
    public ConsoleColor TitleColor { get; set; } = ConsoleColor.Cyan;
    public ConsoleColor OptionColor { get; set; } = ConsoleColor.Gray;
    public ConsoleColor HighlightColor { get; set; } = ConsoleColor.Black;
    public ConsoleColor HighlightBackground { get; set; } = ConsoleColor.White;
    public ConsoleColor InputColor { get; set; } = ConsoleColor.Black;

    public ElementsMenu(string Title) => this.Title = Title;
}