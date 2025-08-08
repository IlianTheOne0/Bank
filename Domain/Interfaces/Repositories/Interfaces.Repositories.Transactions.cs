namespace Domain.Interfaces.Repositories.Transactions;

using Domain.Commands.Transactions;

public interface InterfacesRepositoriesTransactions
{
    Task AddAsync(ProcessTransactionCommand command);
}