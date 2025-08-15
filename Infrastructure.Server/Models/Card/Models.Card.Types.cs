namespace InfrastructureServer.Models.Card.Types;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("CardTypes")]
public class ModelsCardTypes : BaseModel
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Type")] public string Type { get; set; }
}