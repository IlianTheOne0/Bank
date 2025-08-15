namespace InfrastructureServer.Utils.ConfigReader;

using InfrastructureServer.Interfaces.Utils.ConfigReader;

using Newtonsoft.Json;
using Microsoft.Extensions.Logging;
using System.Text;

public class UtilsConfigReader : InterfacesUtilsConfigReader
{
    private readonly string _path;
    private readonly ILogger<UtilsConfigReader> _logger;

    public UtilsConfigReader(string path, ILogger<UtilsConfigReader> Logger)
    {
        _path = path ?? throw new ArgumentNullException(nameof(path));
        _logger = Logger ?? throw new ArgumentNullException(nameof(Logger));

        _logger.LogDebug("ConfigReader initialized with path: {Path}", _path);
    }

    public async Task<TModel?> ReadJsonAsync<TModel>()
    {
        _logger.LogDebug("Reading JSON config from: {Path}", _path);

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
                _logger.LogWarning("Config file is empty or contains only whitespace: {Path}", _path);
                return default;
            }

            _logger.LogDebug("Successfully read config file, deserializing...");
            var result = JsonConvert.DeserializeObject<TModel>(text);

            _logger.LogDebug("Config file deserialized successfully");
            return result;
        }
        catch (JsonException JsonEx) { _logger.LogError(JsonEx, "JSON deserialization error in config file: {Path}", _path); throw; }
        catch (Exception E) { _logger.LogError(E, "Error reading config file: {Path}", _path); throw; }
    }
}