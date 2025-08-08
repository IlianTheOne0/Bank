namespace Database.Models.Transactions.Model;

using Domain.Entities.Transactions.Types;
using Supabase.Postgrest.Attributes;

[Table("Transactions")]
public class Transaction
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Amount")] public decimal Amount { get; set; }
    [Column("TimeStamp")] public DateTime TimeStamp { get; set; }
    [Column("Description")] public string Description { get; set; } = string.Empty;
    [Column("SenderUserId")] public Guid SenderUserId { get; set; }
    [Column("ReceiverUserId")] public Guid ReceiverUserId { get; set; }
    [Column("SenderCardId")] public int? SenderCardId { get; set; }
    [Column("ReceiverCardId")] public int? ReceiverCardId { get; set; }
    [Column("Type")] public TransactionTypes Type { get; set; }
}