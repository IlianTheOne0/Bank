namespace Database.Repositories.Supabase;

using Database.DataSources.Supabase;
using Database.Interfaces.Repositories.Supabase.Auth;
using Database.Interfaces.Repositories.Supabase.Commands;
using Database.Interfaces.Repositories.Supabase.Init;
using Database.Interfaces.DataSources.Supabase;

using InfrastructureServer.Models.Config;

using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Abstractions;
using Microsoft.IdentityModel.Tokens;

public partial class RepositoriesSupabase : InterfacesRepositoriesSupabaseInit, InterfacesRepositoriesSupabaseCommands, InterfacesRepositoriesSupabaseAuth
{
    public InterfacesDataSourcesSupabase? SupabaseConnection { get; set; } = null;
    private ILogger<RepositoriesSupabase> _logger;

    private string _defaultSchema { get; set; } = null!;

    public void InitDatabase(SupabaseConfig Config, ILogger<RepositoriesSupabase> Logger)
    {
        try
        {
            _logger = Logger ?? NullLogger<RepositoriesSupabase>.Instance;

            if (Config == null || Config.Url.IsNullOrEmpty() || Config.Key.IsNullOrEmpty() || Config.DefaultSchema.IsNullOrEmpty())
            {
                _logger.LogError("Supabase configs are null or invalid");
                throw new Exception("Supabase configs are null!");
            }

            _defaultSchema = Config.DefaultSchema;

            var dataSourceLogger = LoggerFactory.Create
            (
                builder => builder.AddSimpleConsole()
            ).CreateLogger<DataSourcesSupabase>();

            SupabaseConnection = new DataSourcesSupabase($"https://{Config.Url}.supabase.co", Config.Key, dataSourceLogger);
            _logger.LogInformation("Supabase initialized. Schema: {Schema}", _defaultSchema);
        }
        catch (Exception E)
        {
            _logger.LogError(E, "Error initializing Supabase client");
            throw new Exception("Error initializing Supabase client!", E);
        }
    }
}