namespace Infrastructure.Server.Interfaces.Utils.ConfigReader;

public interface InterfacesUtilsConfigReader
{
    Task<TMethod?> ReadJsonAsync<TMethod>();
}