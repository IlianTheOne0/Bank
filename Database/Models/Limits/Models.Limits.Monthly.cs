namespace Database.Models.Limits.Monthly.Model;

using Supabase.Postgrest.Attributes;

[Table("MonthlyLimits")]
public class MonthlyLimits
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("MonthlyLimit")] public dynamic MonthlyLimit { get; set; }
    [Column("TodaysExpenses")] public dynamic TodaysExpenses { get; set; }
    [Column("CardId")] public int CardId { get; set; }
}