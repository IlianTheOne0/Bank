namespace Database.Models.User.Model;

using Supabase.Postgrest.Attributes;

[Table("Users")]
public class User
{
    [PrimaryKey("Id")] public Guid Id { get; set; }
    [Column("FullName")] public string FullName { get; set; }
    [Column("Email")] public string Email { get; set; }
    [Column("PhoneNumber")] public string PhoneNumber { get; set; }
    [Column("Sex")] public bool Sex { get; set; }
    [Column("Age")] public ushort Age { get; set; }
    [Column("DateOfBirth")] public DateTime DateOfBirth { get; set; }
    [Column("CreatedAt")] public DateTime CreatedAt { get; set; }
    [Column("UpdatedAt")] public DateTime UpdatedAt { get; set; }
}