namespace Database.Repositories.Supabase;

using Microsoft.Extensions.Logging;
using global::Supabase.Postgrest.Models;
using static global::Supabase.Postgrest.Constants;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

public partial class RepositoriesSupabase
{
    private string BuildDetailedErrorMessage(string Method, Type ModelType, string? Schema, Dictionary<string, object?> Parameters, Exception Exception)
    {
        var paramDetails = string.Join(", ", Parameters.Select(kv => $"{kv.Key}={kv.Value ?? "null"}"));

        return
            $@"[{nameof(RepositoriesSupabase)}] {Method}<{ModelType.Name}> failed.
            Schema: {Schema ?? _defaultSchema}
            Parameters: {paramDetails}
            Exception: {Exception.GetType().FullName}
            Message: {Exception.Message}
            Inner: {Exception.InnerException?.Message ?? "none"}
            StackTrace: {Exception.StackTrace}";
    }

    private async Task ChangeTheSchema(string? Schema = null)
    {
        string targetSchema = Schema ?? _defaultSchema;
        _logger.LogDebug("Changing schema to: {Schema}", targetSchema);
        SupabaseConnection!.SupabaseClient.Postgrest.Options.Schema = targetSchema;
    }

    public async Task<List<TModel>> GetAllAsync<TModel>(string? Schema = null)
        where TModel : BaseModel, new()
    {
        _logger.LogDebug("GetAllAsync<{ModelType}> started", typeof(TModel).Name);
        try
        {
            await ChangeTheSchema(Schema);
            var result = await SupabaseConnection?.SupabaseClient.From<TModel>().Get()!;
            
            _logger.LogDebug("GetAllAsync<{ModelType}> returned {Count} items", typeof(TModel).Name, result.Models.Count);
            return result.Models.ToList();
        }
        catch (Exception E)
        {
            string errorMessage = BuildDetailedErrorMessage
            (
                Method: nameof(GetAllAsync),
                ModelType: typeof(TModel),
                Schema: Schema,
                Parameters: new Dictionary<string, object?>(),
                Exception: E
            );
            _logger.LogError(E, errorMessage);
            throw new Exception(errorMessage, E);
        }
    }

    public async Task<List<TModel>> FilterAsync<TModel>(string ColumnName, Operator Oper, object Value, string? Schema = null)
        where TModel : BaseModel, new()
    {
        _logger.LogDebug("FilterAsync<{ModelType}> started", typeof(TModel).Name);
        try
        {
            await ChangeTheSchema(Schema);
            var result = await SupabaseConnection?.SupabaseClient.From<TModel>().Filter(ColumnName, Oper, Value).Get()!;

            _logger.LogDebug("FilterAsync<{ModelType}> returned {Count} items", typeof(TModel).Name, result.Models.Count);
            return result.Models;
        }
        catch (Exception E)
        {
            string errorMessage = BuildDetailedErrorMessage
            (
                Method: nameof(FilterAsync),
                ModelType: typeof(TModel),
                Schema: Schema,
                Parameters: new Dictionary<string, object?>
                {
                    { nameof(ColumnName), ColumnName },
                    { nameof(Oper), Oper },
                    { nameof(Value), Value }
                },
                Exception: E
            );
            _logger.LogError(E, errorMessage);
            throw new Exception(errorMessage, E);
        }
    }

    public async Task InsertAsync<TModel>(TModel Model, string? Schema = null)
        where TModel : BaseModel, new()
    {
        _logger.LogDebug("InsertAsync<{ModelType}> started", typeof(TModel).Name);
        try
        {
            await ChangeTheSchema(Schema);
            var result = await SupabaseConnection?.SupabaseClient.From<TModel>().Insert(Model)!;
            _logger.LogDebug("InsertAsync<{ModelType}> returned {Count} items", typeof(TModel).Name, result.Models.Count);
        }
        catch (Exception E)
        {
            var parameters = Model.GetType().GetProperties().ToDictionary(p => p.Name, p => p.GetValue(Model));
            string errorMessage = BuildDetailedErrorMessage
            (
                Method: nameof(InsertAsync),
                ModelType: typeof(TModel),
                Schema: Schema,
                Parameters: parameters,
                Exception: E
            );
            _logger.LogError(E, errorMessage);
            throw new Exception(errorMessage, E);
        }
    }
}