namespace ConsoleApplication.Interfaces.Handler;

using Domain.Interfaces.Commands;

public interface InterfacesCommandsHandler<TCommand>
    where TCommand : InterfacesCommandsVoid
{
    Task HandleAsync(TCommand command);
}