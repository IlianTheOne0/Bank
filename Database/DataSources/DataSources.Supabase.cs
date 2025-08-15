namespace Database.DataSources.Supabase;

using Database.Interfaces.DataSources.Supabase;

using global::Supabase;
using Microsoft.Extensions.Logging;

public class DataSourcesSupabase : InterfacesDataSourcesSupabase
{
    public Client SupabaseClient { get; private set; } = null!;
    private readonly ILogger<DataSourcesSupabase> _logger;

    public DataSourcesSupabase(string Url, string Key, ILogger<DataSourcesSupabase> Logger)
    {
        _logger = Logger;

        try
        {
            _logger.LogInformation("Initializing Supabase client with URL: {Url}", Url);

            SupabaseOptions options = new SupabaseOptions { AutoConnectRealtime = true };
            SupabaseClient = new Client(Url, Key, options);

            _logger.LogInformation("Supabase client initialized successfully");
        }
        catch (Exception E) { _logger.LogError(E, "Failed to initialize Supabase client"); throw; }
    }
}