namespace ApplicationServer.Commands.Auth;

using ApplicationServer.Commands.Base;
using InfrastructureServer.Models.User.Model;

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

    public ModelsUser ToModel() => new ModelsUser
    {
        Id = Id,
        FullName = FullName,
        Email = Email,
        PhoneNumber = PhoneNumber,
        Username = Username,
        Sex = Sex,
        DateOfBirth = DateOfBirth,
        CreatedAt = CreatedAt,
        UpdatedAt = UpdatedAt,
        PasswordHash = ""
    };
}