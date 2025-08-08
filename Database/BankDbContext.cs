namespace Infrastructure.Data.DbContext;

using Domain.Entities.Transactions.Model;
using Microsoft.EntityFrameworkCore;

public class BankDbContext : DbContext
{
    public BankDbContext(DbContextOptions<BankDbContext> opts) : base(opts) { }

    public DbSet<Transaction> Transactions { get; set; } = null!;
}