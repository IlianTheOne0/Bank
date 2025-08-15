namespace Domain.Entities.Transactions.Types;

public class EntitiesTransactionTypes
{
    public int Id { get; set; }
    public string Type { get; set; }

    public override string ToString() => Type;
}