using MongoDB.Bson;

namespace Server.Models
{
    public class ReturnRestaurant
    {
        public int RestaurantId { get; set; }
        public string Token { get; set; }

        public bool IsRestaurant { get; set;}
    }
}
