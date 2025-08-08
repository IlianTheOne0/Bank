namespace Database.Models.Card.Model;

using Database.Models.Card.Types;
using Database.Models.Card.Statuses;
using Supabase.Postgrest.Attributes;

[Table("Cards")]
public class Card
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Balance")] public decimal Balance { get; set; }
    [Column("CardNumber")] public string CardNumber { get; set; }
    [Column("CVV")] public ushort CVV { get; set; }
    [Column("IssueDate")] public DateTime IssueDate { get; set; }
    [Column("ExpirationDate")] public DateTime ExpirationDate { get; set; }
    [Column("UserId")] public Guid UserId { get; set; }
    [Column("Type")] public CardTypes Type { get; set; }
    [Column("Status")] public CardStatuses Status { get; set; }
}