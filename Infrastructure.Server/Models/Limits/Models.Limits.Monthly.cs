namespace InfrastructureServer.Models.Limits.Monthly.Model;

using Supabase.Postgrest.Attributes;
using Supabase.Postgrest.Models;

[Table("MonthlyLimits")]
public class ModelsMonthlyLimits : BaseModel
{
    [PrimaryKey("Id")] public int Id { get; set; }
    [Column("MonthlyLimit")] public dynamic MonthlyLimit { get; set; }
    [Column("TodaysExpenses")] public dynamic TodaysExpenses { get; set; }
    [Column("CardId")] public int CardId { get; set; }
}