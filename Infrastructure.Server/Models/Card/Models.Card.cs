namespace InfrastructureServer.Models.Card.Model;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("Cards")]
public class ModelsCard : BaseModel
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("Balance")] public decimal Balance { get; set; }
    [Column("CardNumber")] public string CardNumber { get; set; }
    [Column("CVV")] public ushort CVV { get; set; }
    [Column("IssueDate")] public DateTime IssueDate { get; set; }
    [Column("ExpirationDate")] public DateTime ExpirationDate { get; set; }
    [Column("UserId")] public Guid UserId { get; set; }
    [Column("CurrencyId")] public int CurrencyId { get; set; }
    [Column("TypeId")] public int TypeId { get; set; }
    [Column("StatusId")] public int StatusId { get; set; }
    [Column("PinHash")] public string PinHash { get; set; }
}