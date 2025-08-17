namespace InfrastructureServer.Models.User.Model;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("Users")]
public class ModelsUser : BaseModel
{
    [PrimaryKey("Id")] public Guid Id { get; set; }
    [Column("FullName")] public string FullName { get; set; }
    [Column("Email")] public string Email { get; set; }
    [Column("Username")] public string Username { get; set; }
    [Column("Password")] public string Password { get; set; }
    [Column("PhoneNumber")] public string PhoneNumber { get; set; }
    [Column("Sex")] public bool Sex { get; set; }
    [Column("DateOfBirth")] public DateTime DateOfBirth { get; set; }
    [Column("CreatedAt")] public DateTime CreatedAt { get; set; }
    [Column("UpdatedAt")] public DateTime UpdatedAt { get; set; }
}