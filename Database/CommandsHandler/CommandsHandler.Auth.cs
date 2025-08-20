namespace Database.CommandsHandler.Transactions;

using ApplicationServer.Commands.Auth;
using ApplicationServer.Responses.Database;
using Database.Interfaces.CommandsHandler;
using Database.Interfaces.Repositories.Supabase.Commands;
using Infrastructure.Server.Interfaces.Utils.Hasher;
using InfrastructureServer.Models.User.Model;
using Microsoft.Extensions.Logging;
using System.Diagnostics;
using static Supabase.Postgrest.Constants;

public class CommandsHandlerAuth : InterfacesCommandsHandler
{
    private readonly InterfacesRepositoriesSupabaseCommands _repositorySupabase;
    private readonly InterfacesUtilsHasher _hasher;
    private readonly ILogger<CommandsHandlerAuth> _logger;

    public CommandsHandlerAuth(InterfacesRepositoriesSupabaseCommands RepositorySupabase, InterfacesUtilsHasher Hasher, ILogger<CommandsHandlerAuth> Logger = null!)
    {
        _repositorySupabase = RepositorySupabase ?? throw new ArgumentNullException(nameof(RepositorySupabase), "Supabase commands repository cannot be null. Please provide a valid repository instance.");
        _hasher = Hasher;
        _logger = Logger;
    }

    public async Task<ResponsesDatabase> Handle<TModel>(TModel Command)
    {
        var stopwatch = Stopwatch.StartNew();
        string modelType = typeof(TModel).Name;
        ResponsesDatabase response;

        try
        {
            _logger?.LogDebug($"Starting auth handling for {modelType}");

            if (Command == null) { throw new ArgumentNullException($"Cannot process null {modelType} command. Please provide a valid command instance.", nameof(Command)); }

            if (Command is CommandsAuth auth)
            {
                if (auth.NewUser != null) { response = await HandleNewAuth(auth); }
                else { response = await HandleAuth(auth); }
            }
            else { throw new NotSupportedException($"Command type {modelType} is not supported by this handler. This handler only processes ModelsTransaction commands."); }

            _logger?.LogInformation($"Successfully processed {modelType} command in {stopwatch.ElapsedMilliseconds}ms");

            return response;
        }
        catch (Exception E)
        {
            _logger?.LogError($"Failed to process {modelType} command after {stopwatch.ElapsedMilliseconds}ms. Error: {E.Message}", E);
            throw;
        }
    }

    private async Task<ResponsesDatabase> HandleAuth(CommandsAuth Auth)
    {
        var usersTableResult = await _repositorySupabase.FilterAsync<ModelsUser>("Username", Operator.Equals, Auth.Username!);
        if (usersTableResult == null || usersTableResult.Count == 0) { return ResponsesDatabase.Fail("Authentication Error", $"The username {Auth.Username} does not exist!"); }
        var user = usersTableResult.FirstOrDefault();
        if (user == null) { return ResponsesDatabase.Fail("Authentication Error", $"Could not retrieve user details for username: {Auth.Username}"); }

        if (!_hasher.VerifyHash(Auth.Password, user.PasswordHash)) { return ResponsesDatabase.Fail("Authentication Error", $"The password is incorrect!"); }

        _logger?.LogDebug($"Processed user (Username: {Auth.Username ?? "N/A"})");
        return ResponsesDatabase.Ok(user);
    }

    private async Task<ResponsesDatabase> HandleNewAuth(CommandsAuth Auth)
    {
        var newUser = Auth.NewUser;
        
        var usersTableResult = await _repositorySupabase.FilterAsync<ModelsUser>("Username", Operator.Equals, newUser!.Username);
        if (usersTableResult!.Count != 0) { return ResponsesDatabase.Fail("Registration Error", $"The username {newUser.Username} already exists!"); }

        var emailTableResult = await _repositorySupabase.FilterAsync<ModelsUser>("Email", Operator.Equals, newUser!.Email);
        if (emailTableResult!.Count != 0) { return ResponsesDatabase.Fail("Registration  Error", $"The email {newUser.Email} already exists!"); }

        var phoneNumberTableResult = await _repositorySupabase.FilterAsync<ModelsUser>("PhoneNumber", Operator.Equals, newUser!.PhoneNumber);
        if (phoneNumberTableResult!.Count != 0) { return ResponsesDatabase.Fail("Registration Error", $"The phone number {newUser.PhoneNumber} already exists!"); }

        var userModel = newUser.ToModel();
        userModel.PasswordHash = _hasher.Hash(newUser.Password);

        await _repositorySupabase.InsertAsync<ModelsUser>(userModel);

        _logger?.LogDebug($"Processed new user (Username: {Auth.Username ?? "N/A"})");
        return ResponsesDatabase.Ok(newUser);
    }
}