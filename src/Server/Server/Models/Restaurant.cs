using MongoDB.Bson;

namespace Server.Models
{
    public class Restaurant
    {
        public ObjectId Id { get; set; }
        public int RestaurantId { get; set; }
        public string Name { get; set; }
        public string Address { get; set; }
        public string Phone { get; set; }
        public string Email { get; set; }
        public string Psw { get; set; }
        public bool IsRestaurant { get; set; }
    }
}
