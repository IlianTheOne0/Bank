namespace Database.DataSources.Supabase;

using Database.Interfaces.DataSources.Supabase;
using Microsoft.Extensions.Configuration;
using Npgsql;
using System.Data;

public class DataSourcesSupabase : InterfacesDataSourcesSupabase
{
    private readonly string _connectionString;

    public DataSourcesSupabase(IConfiguration Config) => _connectionString = Config["Supabase:ConnectionString"];

    public IDbConnection GetConnection() => new NpgsqlConnection(_connectionString);
}