namespace InfrastructureServer.Interfaces.Utils.ConfigReader;

public interface InterfacesUtilsConfigReader
{
    Task<TMethod?> ReadJsonAsync<TMethod>();
}