namespace InfrastructureServer.Models.Transactions.Types;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("TransactionTypes")]
public class ModelsTransactionTypes : BaseModel
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Type")] public string Type { get; set; } = string.Empty;

    public ModelsTransactionTypes() { }
}