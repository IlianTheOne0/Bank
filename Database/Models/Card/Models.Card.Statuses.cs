namespace Database.Models.Card.Statuses;

using Supabase.Postgrest.Attributes;

[Table("CardStatuses")]
public class CardStatuses
{
    [PrimaryKey("Id")] public int Id { get; set; }

    [Column("Status")] public string Status { get; set; } = string.Empty;

    public CardStatuses() { }
    public CardStatuses(int Id, string Status) { this.Id = Id; this.Status = Status; }

    public override string ToString() => Status;
}