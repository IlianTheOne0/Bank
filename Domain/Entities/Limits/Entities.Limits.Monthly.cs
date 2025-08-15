namespace Domain.Entities.Limits.Monthly.Model;

public class EntitiesMonthlyLimits
{
    public int Id { get; set; }
    public dynamic MonthlyLimit { get; set; }
    public dynamic TodaysExpenses { get; set; }
    public int CardId { get; set; }
}