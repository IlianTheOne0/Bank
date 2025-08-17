namespace ApplicationClient.Commands.Auth;

using ApplicationClient.Commands.Base;

public class CommandsAuth : CommandsBase
{
    public string Username { get; set; }
    public string Password { get; set; }
    public CommandsAuthSignIn? NewUser { get; set; }
}

public class CommandsAuthSignIn
{
    public Guid Id { get; set; }
    public string FullName { get; set; }
    public string Email { get; set; }
    public string PhoneNumber { get; set; }
    public string Username { get; set; }
    public bool Sex { get; set; }
    public DateTime DateOfBirth { get; set; }
    public DateTime CreatedAt { get; set; }
    public DateTime UpdatedAt { get; set; }
    public string Password { get; set; }
}