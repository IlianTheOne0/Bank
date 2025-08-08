using Domain.Interfaces.Commands;
using System.ComponentModel.DataAnnotations.Schema;

namespace Domain.Commands.Transactions;

public record ProcessTransactionCommand(
    decimal Amount,
    DateTime TimeStamp,
    string Description,
    Guid SenderUserId,
    Guid ReceiverUserId,
    int? SenderCardId,
    int? ReceiverCardId,
    string Type
) : InterfacesCommandsVoid;