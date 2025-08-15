namespace Domain.Entities.Transactions.Model;

using Domain.Entities.Transactions.Types;

public class EntitiesTransaction
{
    public int Id { get; set; }
    public decimal Amount { get; set; }
    public DateTime TimeStamp { get; set; }
    public string Description { get; set; } = string.Empty;
    public Guid SenderUserId { get; set; }
    public Guid ReceiverUserId { get; set; }
    public int SenderCardId { get; set; }
    public int ReceiverCardId { get; set; }
    public EntitiesTransactionTypes Type { get; set; }
}