namespace InfrastructureServer.Utils.Hasher;

using Infrastructure.Server.Interfaces.Utils.Hasher;
using Microsoft.Extensions.Logging;
using System.Security.Cryptography;
using System.Text;


public class UtilsHasher : InterfacesUtilsHasher
{
    private readonly ILogger<UtilsHasher> _logger;

    public UtilsHasher(ILogger<UtilsHasher> logger) => _logger = logger;

    public string Hash(string Hash)
    {
        using var sha256 = SHA256.Create();
        var hashedBytes = sha256.ComputeHash(Encoding.UTF8.GetBytes(Hash));
        return Convert.ToBase64String(hashedBytes);
    }

    public bool VerifyHash(string Hash, string StoredHash)
    {
        try
        {
            var hashOfInput = this.Hash(Hash);
            return hashOfInput == StoredHash;
        }
        catch (Exception ex) { _logger.LogError(ex, "PIN verification failed"); return false; }
    }
}