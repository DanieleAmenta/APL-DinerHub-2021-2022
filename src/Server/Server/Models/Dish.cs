using MongoDB.Bson;

namespace Server.Models
{
    public class Dish
    {
        public ObjectId Id { get; set; }
        public int DishId { get; set; }
        public string Name { get; set; }
        public DishTypes Type { get; set; }
        public double Price { get; set; }
        public int RestaurantId { get; set; }   // Reference to Restaurant

        // TODO: PHOTO PLACEHOLDER
    }
}
