namespace InfrastructureServer.Models.Card.Types;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("CardTypes")]
public class ModelsCardTypes : BaseModel
{
    [PrimaryKey("Id")] int Id { get; set; }
    [Column("Type")] string Type { get; set; }
}