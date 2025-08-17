namespace InfrastructureServer.Models.Card.Currencies;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("Currencies")]
public class ModelsCardCurrencies : BaseModel
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Currency")] public string Currency { get; set; } = string.Empty;
}