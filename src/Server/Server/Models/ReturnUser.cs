using MongoDB.Bson;

namespace Server.Models
{
    public class ReturnUser
    {
        public int UserId { get; set; }
        public string Token { get; set; }

        public bool IsAdmin { get; set; }
    }
}
