namespace InfrastructureServer.Models.Card.Statuses;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("CardStatuses")]
public class ModelsCardStatuses : BaseModel
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Status")] public string Status { get; set; } = string.Empty;
}