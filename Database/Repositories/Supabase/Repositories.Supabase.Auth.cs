namespace Database.Repositories.Supabase;

using Microsoft.Extensions.Logging;

public partial class RepositoriesSupabase
{
    public async Task Login(string EmailDomain, string Email, string Password)
    {
        _logger.LogDebug("Login attempt for: {Email}", Email);
        try
        {
            await SupabaseConnection?.SupabaseClient.Auth.SignIn($"{Email}@{EmailDomain}", Password)!;
            _logger.LogInformation("Login successful for: {Email}", Email);
        }
        catch (Exception E)
        {
            _logger.LogError(E, "Login failed for: {Email}", Email);
            throw new Exception($"Login failed: {E.Message}", E);
        }
    }

    public async Task Logout()
    {
        _logger.LogDebug("Logout requested");
        try
        {
            await SupabaseConnection?.SupabaseClient.Auth.SignOut()!;
            _logger.LogInformation("Logout successful");
        }
        catch (Exception E)
        {
            _logger.LogError(E, "Logout failed");
            throw new Exception($"Logout failed: {E.Message}", E);
        }
    }
}