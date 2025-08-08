namespace Domain.Entities.User;

using Domain.Entities.Card;

public class UserExtended : User
{
    public User Base { get; set; }
    public List<Card> Cards { get; set; }

    public UserExtended(User Base, List<Card> Cards) { this.Base = Base; this.Cards = Cards; }
    
    public User ToBase() => Base;
}