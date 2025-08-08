namespace Domain.Entities.Card.Statuses;

public class CardStatuses
{
    public int Id { get; set; }

    public string Status { get; set; } = string.Empty;

    public CardStatuses() { }
    public CardStatuses(int Id, string Status) { this.Id = Id; this.Status = Status; }

    public override string ToString() => Status;
}