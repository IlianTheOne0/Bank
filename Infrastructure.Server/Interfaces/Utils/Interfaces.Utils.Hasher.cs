namespace Infrastructure.Server.Interfaces.Utils.Hasher;

public interface InterfacesUtilsHasher
{
    string Hash(string Hash);
    bool VerifyHash(string Hash, string StoredHash);
}