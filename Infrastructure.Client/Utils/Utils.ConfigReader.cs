namespace InfrastructureClient.Utils.ConfigReader;

using InfrastructureClient.Interfaces.Utils.ConfigReader;

using Newtonsoft.Json;
using Microsoft.Extensions.Logging;
using System.Text;

public class UtilsConfigReader : InterfacesUtilsConfigReader
{
    private readonly string _path;
    private readonly ILogger<UtilsConfigReader> _logger;

    public UtilsConfigReader(string Path, ILogger<UtilsConfigReader> Logger)
    {
        _path = Path ?? throw new ArgumentNullException(nameof(Path));
        _logger = Logger ?? throw new ArgumentNullException(nameof(Logger));

        _logger.LogDebug("ConfigReader initialized with path: {Path}", _path);
    }

    public async Task<TModel?> ReadJsonAsync<TModel>()
    {
        _logger.LogDebug("Attempting to read and deserialize JSON from {Path}", _path);

        if (!File.Exists(_path))
        {
            _logger.LogError("Config file not found at path: {Path}", _path);
            throw new FileNotFoundException("Config file not found", _path);
        }

        try
        {
            using var sr = new StreamReader(_path, Encoding.UTF8);
            var text = await sr.ReadToEndAsync();

            if (string.IsNullOrWhiteSpace(text))
            {
                _logger.LogWarning("Config file at {Path} is empty or contains only whitespace", _path);
                return default;
            }

            _logger.LogDebug("Successfully read config file, deserializing...");
            var result = JsonConvert.DeserializeObject<TModel>(text);

            _logger.LogDebug("Config file deserialized successfully");
            return result;
        }
        catch (Exception E) { _logger.LogError(E, "Error reading or deserializing config file at {Path}", _path); throw; }
    }
}