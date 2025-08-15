namespace ApplicationClient.Responses.Auth;

using ApplicationClient.Responses.Base;

public class ResponsesAuth : ResponsesBase
{
    public string Token { get; set; }
    public Guid UserId { get; set; }
}