namespace Database.Interfaces.Repositories.Supabase.Auth;

public interface InterfacesRepositoriesSupabaseAuth
{
    Task Login(string EmailDomain, string Username, string Password);
    Task Logout();
}