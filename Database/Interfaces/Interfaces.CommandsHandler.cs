namespace Database.Interfaces.CommandsHandler;

using ApplicationServer.Responses.Database;

public interface InterfacesCommandsHandler
{
    Task<ResponsesDatabase> Handle<TModel>(TModel Command);
}