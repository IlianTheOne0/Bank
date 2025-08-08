namespace Database.Interfaces.DataSources.Supabase;

using System.Data;

public interface InterfacesDataSourcesSupabase
{
    IDbConnection GetConnection();
}