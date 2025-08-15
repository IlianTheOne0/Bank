namespace Database.Loop;

using Database.Repositories.Supabase;

using InfrastructureServer.Models.Config;

using Microsoft.Extensions.DependencyInjection;

internal partial class DatabaseLoop
{
    private static async Task SupabaseLogin(ServiceProvider Services, AppConfig Config)
    {
        RepositoriesSupabase repositorySupabase = Services.GetRequiredService<RepositoriesSupabase>();
        await repositorySupabase.Login(Config.Supabase.EmailDomain, Config.Supabase.Email, Config.Supabase.Password);
    }

    private static async Task SupabaseLogout(ServiceProvider Services)
    {
        RepositoriesSupabase repositorySupabase = Services.GetRequiredService<RepositoriesSupabase>();
        await repositorySupabase.Logout();
    }
}