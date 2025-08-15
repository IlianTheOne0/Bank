namespace InfrastructureServer.Models.Config;

public class AppConfig
{
    public KafkaConfig Kafka { get; set; }
    public SupabaseConfig Supabase { get; set; }
}

public class KafkaConfig
{
    public string BootstrapServers { get; set; }
    public string GroupId { get; set; }
    public string PipeName { get; set; }
    public Dictionary<string, string> Topics { get; set; }
}

public class SupabaseConfig
{
    public string Url { get; set; }
    public string Key { get; set; }
    public string DefaultSchema { get; set; }
    public string EmailDomain { get; set; }
    public string Email { get; set; }
    public string Password { get; set; }
}