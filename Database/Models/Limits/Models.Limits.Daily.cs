namespace Database.Models.Limits.Daily.Model;

using Supabase.Postgrest.Attributes;

[Table("DailyLimits")]
public class MonthlyLimits
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("MonthlyLimit")] public dynamic MonthlyLimit { get; set; }
    [Column("TodaysExpenses")] public dynamic TodaysExpenses { get; set; }
    [Column("CardId")] public int CardId { get; set; }
}