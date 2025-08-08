namespace Database.Models.Card.Types;

using Supabase.Postgrest.Attributes;

[Table("CardTypes")]
public class CardTypes
{
    [PrimaryKey("Id")] int Id { get; set; }
    [Column("Type")] string Type { get; set; }

    public CardTypes() { }
    public CardTypes(int Id, string Type) { this.Id = Id; this.Type = Type; }

    public override string ToString() => Type;
}