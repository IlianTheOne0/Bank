namespace Domain.Entities.Card.Model;

using Domain.Entities.Card.Statuses;
using Domain.Entities.Card.Types;

public class EntitiesCard
{
    public int Id { get; set; }
    public decimal Balance { get; set; }
    public string CardNumber { get; set; }
    public ushort CVV { get; set; }
    public DateTime IssueDate { get; set; }
    public DateTime ExpirationDate { get; set; }
    public string Currency { get; set; }
    public Guid UserId { get; set; }
    public EntitiesCardTypes Type { get; set; }
    public EntitiesCardStatuses Status { get; set; }
    public string PinHash { get; set; }
}