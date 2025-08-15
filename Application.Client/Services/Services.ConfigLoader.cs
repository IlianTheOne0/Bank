namespace ApplicationClient.Services.ConfigLoader;

using Domain.Entities.Services.Kafka;

using InfrastructureClient.Utils.ConfigReader;

using Microsoft.Extensions.Logging;

public static class ServicesConfigLoader
{
    public static async Task<EntitiesServicesKafka?> LoadConfigAsync()
    {
        try
        {
            var baseDir = AppContext.BaseDirectory;
            var configPath = Path.Combine(baseDir, "..", "..", "..", "..", "Infrastructure.Client", ".env", "app_config.json");
            configPath = Path.GetFullPath(configPath);

            if (!File.Exists(configPath)) { Console.WriteLine($"Config file not found at: {configPath}"); return null; }

            using var loggerFactory = LoggerFactory.Create
            (
                builder =>
                {
                    builder.AddSimpleConsole
                    (
                        options =>
                        {
                            options.SingleLine = true;
                            options.TimestampFormat = "HH:mm:ss ";
                        }
                    );
                }
            );

            var configReaderLogger = loggerFactory.CreateLogger<UtilsConfigReader>();
            UtilsConfigReader jsonReader = new UtilsConfigReader(configPath, configReaderLogger);
            EntitiesServicesKafka? config = await jsonReader.ReadJsonAsync<EntitiesServicesKafka>();

            if (config is null) { throw new InvalidOperationException($"Failed to read AppConfig from {configPath}."); }

            return config;
        }
        catch (Exception E) { Console.WriteLine($"Error loading config: {E.Message}"); return null; }
    }
}