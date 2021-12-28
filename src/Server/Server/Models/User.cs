using MongoDB.Bson;

namespace Server.Models
{
    public class User
    {
        public ObjectId Id { get; set; }
        public int UserId { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }
        public string Email { get; set; }
        public string Psw { get; set; }
        public string Phone { get; set; }
        public double? Balance { get; set; }
        public DateTime BirthDate { get; set; }
        public bool IsAdmin { get; set; }
    }
}
