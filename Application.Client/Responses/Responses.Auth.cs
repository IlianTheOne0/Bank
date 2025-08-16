namespace ApplicationClient.Responses.Auth;

using ApplicationClient.Responses.Base;
using Domain.Entities.User.Model;

public class ResponsesAuth : ResponsesBase
{
    public string Token { get; set; }
    public EntitiesUser User { get; set; }
}