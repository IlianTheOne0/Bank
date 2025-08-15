namespace ConsoleApplication.Elements.Menu;

using System;

internal static class MenuRenderer
{
    private static bool _debugMode;
    private static ConsoleColor _originalBackground;
    private static ConsoleColor _originalForeground;

    public static void SetDebugMode(bool DebugMode)
    {
        _debugMode = DebugMode;
        if (!_debugMode)
        {
            _originalBackground = Console.BackgroundColor;
            _originalForeground = Console.ForegroundColor;
        }
    }

    public static async Task<int> Render(ElementsMenu Menu)
    {
        try
        {
            if (!_debugMode) { Console.Clear(); Console.SetCursorPosition(0, 0); }

            if (Menu.Options.Count == 0) { return -1; }

            int maxWidth = CalculateMenuWidth(Menu);
            int height = Menu.Options.Count + 6;
            int left = (Console.WindowWidth - maxWidth) / 2;
            int top = (Console.WindowHeight - height) / 2;

            bool selectionChanged = true;
            int selectedIndex = 0;
            bool isEditingInput = false;

            if (Menu.Title == "Processing" && Menu.Options.Count == 1) { DrawProcessingMenu(Menu, maxWidth, height, left, top); return 0; }

            while (true)
            {
                if (selectionChanged)
                {
                    DrawMenuFrame(Menu, maxWidth, height, left, top);
                    DrawOptions(Menu, maxWidth, left, top, selectedIndex, isEditingInput);
                    selectionChanged = false;
                }

                var key = Console.ReadKey(true);

                if (HandleInput(key, Menu, ref selectedIndex, ref isEditingInput, ref selectionChanged, out int result)) { return result; }
            }
        }
        catch (Exception E)
        {
            if (_debugMode) { Console.WriteLine($"Menu rendering error: {E.Message}"); }
            return -1;
        }
    }

    private static int CalculateMenuWidth(ElementsMenu Menu)
    {
        int maxWidth = Math.Max(Menu.Title.Length + 4, 40);
        foreach (var option in Menu.Options)
        {
            int optionWidth = option.Text.Length + 4;
            if (option is ElementsMenuInputOption inputOption) { optionWidth += inputOption.MaxLength + 2; }
            maxWidth = Math.Max(maxWidth, optionWidth);
        }
        return maxWidth;
    }

    private static void DrawProcessingMenu(ElementsMenu Menu, int Width, int Height, int Left, int Top)
    {
        DrawMenuFrame(Menu, Width, Height, Left, Top);
        DrawOptions(Menu, Width, Left, Top, 0, false);
    }

    private static void DrawMenuFrame(ElementsMenu Menu, int Width, int Height, int Left, int Top)
    {
        Console.ForegroundColor = Menu.BorderColor;

        // Top border
        Console.SetCursorPosition(Left, Top);
        Console.Write("┌" + new string('─', Width - 2) + "┐");

        // Title area
        Console.SetCursorPosition(Left, Top + 1);
        Console.Write("│");
        Console.ForegroundColor = Menu.TitleColor;
        Console.Write(CenterText(Menu.Title, Width - 2));
        Console.ForegroundColor = Menu.BorderColor;
        Console.Write("│");

        // Title separator
        Console.SetCursorPosition(Left, Top + 2);
        Console.Write("├" + new string('─', Width - 2) + "┤");

        // Bottom border
        Console.SetCursorPosition(Left, Top + Height - 3);
        Console.Write("└" + new string('─', Width - 2) + "┘");
    }

    private static void DrawOptions(ElementsMenu Menu, int Width, int Left, int Top, int SelectedIndex, bool IsEditingInput)
    {
        for (int i = 0; i < Menu.Options.Count; i++)
        {
            Console.SetCursorPosition(Left, Top + 3 + i);

            bool isSelected = i == SelectedIndex;
            bool isInputOption = Menu.Options[i] is ElementsMenuInputOption;

            SetOptionColors(Menu, i, isSelected, IsEditingInput);

            Console.ForegroundColor = Menu.BorderColor;
            Console.Write("│");

            SetOptionColors(Menu, i, isSelected, IsEditingInput);

            string displayText = GetDisplayText(Menu, i, isSelected, IsEditingInput);
            Console.Write(CenterText(displayText, Width - 2));

            Console.ForegroundColor = Menu.BorderColor;
            Console.Write("│");
        }

        Console.ResetColor();
        if (!_debugMode)
        {
            Console.BackgroundColor = _originalBackground;
            Console.ForegroundColor = _originalForeground;
        }
    }

    private static bool HandleInput(ConsoleKeyInfo Key, ElementsMenu Menu, ref int SelectedIndex, ref bool IsEditingInput, ref bool SelectionChanged, out int Result)
    {
        Result = -1;

        if (IsEditingInput) { return HandleInputEditing(Key, Menu, SelectedIndex, ref IsEditingInput, ref SelectionChanged); }

        switch (Key.Key)
        {
            case ConsoleKey.UpArrow:
            {
                SelectedIndex = (SelectedIndex - 1 + Menu.Options.Count) % Menu.Options.Count;
                SelectionChanged = true;
            } break;
            case ConsoleKey.DownArrow:
            {
                SelectedIndex = (SelectedIndex + 1) % Menu.Options.Count;
                SelectionChanged = true;
            } break;
            case ConsoleKey.Enter: { return HandleEnterKey(Menu, SelectedIndex, ref IsEditingInput, ref SelectionChanged, out Result); }
            case ConsoleKey.Escape: { Result = -1; return true; }
        }

        return false;
    }

    private static bool HandleInputEditing(ConsoleKeyInfo Key, ElementsMenu Menu, int SelectedIndex, ref bool IsEditingInput, ref bool SelectionChanged)
    {
        var inputOption = Menu.Options[SelectedIndex] as ElementsMenuInputOption;
        if (inputOption == null) { return false; }

        if (Key.Key == ConsoleKey.Enter || Key.Key == ConsoleKey.Escape) { IsEditingInput = false; SelectionChanged = true; }
        else if (Key.Key == ConsoleKey.Backspace && inputOption.Input.Length > 0) { inputOption.Input = inputOption.Input[..^1]; SelectionChanged = true; }
        else if (!char.IsControl(Key.KeyChar))
        {
            if (inputOption.Input.Length < inputOption.MaxLength) { inputOption.Input += Key.KeyChar; SelectionChanged = true; }
        }
        return false;
    }

    private static bool HandleEnterKey(ElementsMenu Menu, int SelectedIndex, ref bool IsEditingInput, ref bool SelectionChanged, out int Result)
    {
        Result = -1;

        if (Menu.Options[SelectedIndex] is ElementsMenuInputOption) { IsEditingInput = true; SelectionChanged = true; return false; }

        var option = Menu.Options[SelectedIndex];
        if (option.AsyncAction != null) { option.AsyncAction().Wait(); Result = SelectedIndex; return true; }

        option.Action?.Invoke();
        Result = SelectedIndex;
        return true;
    }

    private static void SetOptionColors(ElementsMenu Menu, int Index, bool IsSelected, bool IsEditingInput)
    {
        if (IsSelected)
        {
            Console.BackgroundColor = Menu.HighlightBackground;
            Console.ForegroundColor = IsEditingInput ? Menu.InputColor : Menu.HighlightColor;
        }
        else
        {
            Console.BackgroundColor = _debugMode ? Console.BackgroundColor : _originalBackground;
            Console.ForegroundColor = Menu.OptionColor;
        }
    }

    private static string GetDisplayText(ElementsMenu Menu, int Index, bool IsSelected, bool IsEditingInput)
    {
        if (Menu.Options[Index] is not ElementsMenuInputOption inputOption) { return Menu.Options[Index].Text; }

        string inputDisplay = inputOption.IsPassword ? new string('*', inputOption.Input.Length) : inputOption.Input;

        if (IsSelected && IsEditingInput) { inputDisplay += "_"; }

        return $"{Menu.Options[Index].Text}: {inputDisplay}";
    }

    private static string CenterText(string Text, int Width)
    {
        if (Text.Length >= Width) { return Text; }

        int padding = Width - Text.Length;
        int leftPadding = padding / 2;
        return new string(' ', leftPadding) + Text + new string(' ', padding - leftPadding);
    }
}