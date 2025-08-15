namespace Domain.Entities.Card.Types;

public class EntitiesCardTypes
{
    public int Id { get; set; }
    public string Type { get; set; }

    public override string ToString() => Type;
}