using MongoDB.Bson;

namespace Server.Models
{
    public class Order
    {
        public ObjectId Id { get; set; }
        public int OrderId { get; set; }
        public OrderStatus Status { get; set; }
        public double Total { get; set; }
        public int UserId { get; set; }             // Reference to User
        public int RestaurantId { get; set; }       // Reference to Restaurant
        public OrderDish[] Dishes { get; set; }

        public DateTime Date { get; set; }
    }
}
