namespace Infrastructure.Interfaces.Kafka.Commands.Processor;

using System.Data;

public interface InterfacesKafkaCommandsProcessor
{
    bool CanProcess(CommandTypes type);
    Task ProcessAsync(string data);
}