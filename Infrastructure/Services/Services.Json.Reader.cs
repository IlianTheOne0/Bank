namespace Infrastructure.Services.JsonReader;

using Infrastructure.Interfaces.Services.JsonReader;
using Microsoft.Extensions.Configuration;
using System.Threading.Tasks;

public class JsonReaderService : InterfacesServicesJsonReader
{
    private readonly string _filePath;
    private IConfiguration? _configuration;

    public JsonReaderService(string FilePath)
    {
        if (string.IsNullOrWhiteSpace(FilePath)) { throw new ArgumentException("File path cannot be null or empty", nameof(FilePath)); }

        _filePath = FilePath;
    }

    public async Task InitializeAsync(string Key)
    {
        try
        {
            await Task.Run(() =>
            {
                _configuration = new ConfigurationBuilder()
                    .SetBasePath(Directory.GetCurrentDirectory())
                    .AddJsonFile(_filePath, optional: false, reloadOnChange: false)
                    .Build();

                if (!string.IsNullOrEmpty(Key) && _configuration[Key] == null) { throw new KeyNotFoundException($"Configuration key '{Key}' not found"); }
            });
        }
        catch (Exception E) { throw new InvalidOperationException( $"Failed to initialize configuration from file '{_filePath}'. " + $"See inner exception for details.", E); }
    }

    public IConfiguration GetConfiguration() { return _configuration ?? throw new InvalidOperationException("Configuration has not been initialized. Call InitializeAsync first."); }
}