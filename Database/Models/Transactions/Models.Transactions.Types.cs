namespace Database.Models.Transactions.Types;

using Supabase.Postgrest.Attributes;

[Table("TransactionTypes")]
public class TransactionTypes
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Type")] public string Type { get; set; }

    public TransactionTypes() { }
    public TransactionTypes(int Id, string Type) { this.Id = Id; this.Type = Type; }

    public override string ToString() => Type;
}