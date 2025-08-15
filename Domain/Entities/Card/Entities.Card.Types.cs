namespace Domain.Entities.Card.Types;

public class EntitiesCardTypes
{
    int Id { get; set; }
    string Type { get; set; }

    public override string ToString() => Type;
}