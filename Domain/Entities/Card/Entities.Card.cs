namespace Domain.Entities.Card;

using Domain.Entities.Card.Statuses;

public class Card
{
    public int Id { get; set; }
    public decimal Balance { get; set; }
    public string CardNumber { get; set; }
    public ushort CVV { get; set; }
    public DateTime IssueDate { get; set; }
    public DateTime ExpirationDate { get; set; }
    public Guid UserId { get; set; }
    public string Type { get; set; }
    public CardStatuses Status { get; set; }
}