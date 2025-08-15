namespace Domain.Entities.Services.Kafka;

public record EntitiesServicesKafka
{
    public bool DebugMode { get; set; } = false;
    public required string BootstrapServers { get; set; }
    public required string GroupId { get; set; }
    public required string PipeName { get; set; }
    public required Dictionary<string, string> Topics { get; set; }
}