namespace Database.Interfaces.Repositories.Supabase.Init;

using Database.Repositories.Supabase;

using InfrastructureServer.Models.Config;

using Microsoft.Extensions.Logging;

public interface InterfacesRepositoriesSupabaseInit
{
    void InitDatabase(SupabaseConfig Config, ILogger<RepositoriesSupabase> Logger);
}