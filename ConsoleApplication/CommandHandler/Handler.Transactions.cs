namespace ConsoleApplication.Commands.Handler.Transactions;

using ConsoleApplication.Interfaces.Handler;
using Domain.Interfaces.Repositories.Transactions;
using Domain.Commands.Transactions;
using System.Threading.Tasks;

public class ProcessTransactionHandler
    : InterfacesCommandsHandler<ProcessTransactionCommand>
{
    private readonly InterfacesRepositoriesTransactions _repo;
    public ProcessTransactionHandler(InterfacesRepositoriesTransactions Repository) => _repo = Repository;

    public async Task HandleAsync(ProcessTransactionCommand Cmd)
    {
        var tx = new ProcessTransactionCommand
        {
            Amount = Cmd.Amount,
            TimeStamp = Cmd.TimeStamp,
            Description = Cmd.Description,
            SenderUserId = Cmd.SenderUserId,
            ReceiverUserId = Cmd.ReceiverUserId,
            SenderCardId = Cmd.SenderCardId,
            ReceiverCardId = Cmd.ReceiverCardId,
            Type = Cmd.Type
        };

        await _repo.AddAsync(tx);
    }
}