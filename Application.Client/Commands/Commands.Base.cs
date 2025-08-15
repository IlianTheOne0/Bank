namespace ApplicationClient.Commands.Base;

public abstract class CommandsBase
{
    public Guid CorrelationId { get; set; }
}