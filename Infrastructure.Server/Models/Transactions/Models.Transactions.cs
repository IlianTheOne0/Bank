namespace InfrastructureServer.Models.Transactions.Model;

using InfrastructureServer.Models.Transactions.Types;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("Transactions")]
public class ModelsTransaction : BaseModel
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("CorrelationId")] public Guid CorrelationId { get; set; }
    [Column("Amount")] public decimal Amount { get; set; }
    [Column("TimeStamp")] public DateTime TimeStamp { get; set; }
    [Column("Description")] public string Description { get; set; } = string.Empty;
    [Column("SenderUserId")] public Guid SenderUserId { get; set; }
    [Column("ReceiverUserId")] public Guid ReceiverUserId { get; set; }
    [Column("SenderCardId")] public int SenderCardId { get; set; }
    [Column("ReceiverCardId")] public int ReceiverCardId { get; set; }
    [Column("Type")] public ModelsTransactionTypes Type { get; set; } = new ModelsTransactionTypes();
}