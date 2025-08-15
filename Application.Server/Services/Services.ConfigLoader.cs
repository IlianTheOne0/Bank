namespace ApplicationClient.Services.ConfigLoader;

using InfrastructureServer.Models.Config;
using InfrastructureServer.Utils.ConfigReader;

using Microsoft.Extensions.Logging;

public static class ServicesConfigLoader
{
    public static async Task<AppConfig?> LoadConfigAsync()
    {
        try
        {
            var baseDir = AppContext.BaseDirectory;
            var configPath = Path.Combine(baseDir, "..", "..", "..", "..", "Infrastructure.Server", ".env", "app_config.json");
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
            AppConfig? config = await jsonReader.ReadJsonAsync<AppConfig>();

            if (config is null) { throw new InvalidOperationException($"Failed to read AppConfig from {configPath}."); }

            return config;
        }
        catch (Exception E) { Console.WriteLine($"Error loading config: {E.Message}"); return null; }
    }
}