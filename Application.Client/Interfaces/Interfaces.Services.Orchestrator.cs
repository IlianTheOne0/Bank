namespace ApplicationClient.Interfaces.Services.Orchestrator;

public interface InterfacesServicesOrchestrators
{
    Task<TResponse> Execute<TCommand, TResponse>(TCommand Command);
}