namespace Domain.Entities.Transactions.Types;

public class TransactionTypes
{
    public int Id { get; set; }
    public string Type { get; set; }

    public TransactionTypes() { }
    public TransactionTypes(int Id, string Type) { this.Id = Id; this.Type = Type; }

    public override string ToString() => Type;
}