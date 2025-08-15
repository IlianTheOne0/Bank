namespace InfrastructureServer.Models.Card.Model;

using InfrastructureServer.Models.Card.Statuses;
using InfrastructureServer.Models.Card.Types;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("Cards")]
public class ModelsCard : BaseModel
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Balance")] public decimal Balance { get; set; }
    [Column("CardNumber")] public string CardNumber { get; set; }
    [Column("CVV")] public ushort CVV { get; set; }
    [Column("IssueDate")] public DateTime IssueDate { get; set; }
    [Column("ExpirationDate")] public DateTime ExpirationDate { get; set; }
    [Column("Currency")] public string Currency { get; set; }
    [Column("UserId")] public Guid UserId { get; set; }
    [Column("Type")] public ModelsCardTypes Type { get; set; }
    [Column("Status")] public ModelsCardStatuses Status { get; set; }
}