using Microsoft.Extensions.Configuration;

namespace Infrastructure.Interfaces.Services.JsonReader;

public interface InterfacesServicesJsonReader
{
    Task InitializeAsync(string Key);
    IConfiguration GetConfiguration();
}