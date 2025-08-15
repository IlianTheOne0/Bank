namespace ApplicationServer.Commands.Auth;

using ApplicationServer.Commands.Base;

public class CommandsAuth : CommandsBase
{
    public string Username { get; set; }
    public string Password { get; set; }
    public DateTime TimeStamp { get; set; }
}