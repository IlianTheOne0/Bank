namespace Database.Interfaces.Repositories.Supabase.Commands;

using global::Supabase.Postgrest.Models;
using static global::Supabase.Postgrest.Constants;

public interface InterfacesRepositoriesSupabaseCommands
{
    Task<List<TModel>> GetAllAsync<TModel>(string? Schema = null)
        where TModel : BaseModel, new();
    Task<List<TModel>> FilterAsync<TModel>(string ColumnName, Operator Oper, object Value, string? Schema = null)
        where TModel : BaseModel, new();
    Task InsertAsync<TModel>(TModel Model, string? Schema = null)
        where TModel : BaseModel, new();
}