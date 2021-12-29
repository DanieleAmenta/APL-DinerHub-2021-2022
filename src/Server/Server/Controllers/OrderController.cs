using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using MongoDB.Driver;
using Server.Models;
using System.Text.RegularExpressions;

namespace Server.Controllers
{
    [Route("api/order")]
    [ApiController]
    public class OrderController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        public OrderController(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        /*
         * API /order/all
         * Return all orders
         */
        [Route("all")]
        [HttpGet]
        public IActionResult Get()
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var dbList = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order").AsQueryable();

                return Ok(dbList);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/:id
         * Return the order with the specified id
         */
        [HttpGet("{id}")]
        public IActionResult Get(int id)
        {
            try
            {
                if(Regex.IsMatch(id.ToString(), @"^\d+$"))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Order>.Filter.Eq("OrderId", id);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    return Ok(dbList);
                } else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/create
         * Create a new order
         */
        [Route("create")]
        [HttpPost]
        public IActionResult Post(Order order)
        {
            try
            {
                // We check only this fields because we
                // override orderId, status and total
                if (Regex.IsMatch(order.UserId.ToString(), @"^[1-9]\d*$")
                    && Regex.IsMatch(order.RestaurantId.ToString(), @"^[1-9]\d*$")
                    )
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    // Get last element and create a new id for the new order
                    var dbOrderList = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order").AsQueryable().ToList();
                    int LastOrderId = dbOrderList.Last().OrderId;
                    order.OrderId = LastOrderId + 1;

                    double tmpTotal = 0.0;
                    foreach (var dish in order.Dishes)
                    {
                        // Check if dish price is positive ( > 0 )
                        if (dish.Dish.Price > 0)
                        {
                            tmpTotal += (dish.Dish.Price * dish.quantity);
                        }
                        else
                        {
                            return BadRequest("One or more validation errors occurred.");
                        }
                    }
                    order.Total = tmpTotal;
                    order.Status = 0;           // Order status = Created

                    // Check if user is able to submit this order
                    double userBalance = 0.0;

                    var filter = Builders<User>.Filter.Eq("UserId", order.UserId);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        userBalance = (double) dbList.Balance;
                    }
                    else
                    {
                        return BadRequest("No user found with this ID!");
                    }

                    if (userBalance >= order.Total)
                    {
                        // Decrease user balance
                        var oldBalance = dbList.Balance;
                        var update = Builders<User>.Update.Set("Balance", oldBalance - order.Total);

                        dbClient.GetDatabase("dinerhub").GetCollection<User>("User").UpdateOne(filter, update);

                        dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order").InsertOne(order);

                        return Ok("Order created successfully!");
                    }
                    else
                    {
                        return BadRequest("Not enough balance!");
                    }
                }
                else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/update
         * Update order information
         */
        [Route("update")]
        [HttpPut]
        public IActionResult Put(Order order)
        {
            try
            {
                if (Regex.IsMatch(order.UserId.ToString(), @"^[1-9]\d*$")
                    && Regex.IsMatch(order.RestaurantId.ToString(), @"^[1-9]\d*$")
                    && Regex.IsMatch(order.Total.ToString(), @"^[1-9]\d*$")
                    && Regex.IsMatch(order.Status.ToString(), @"^[0-2]$")
                    )
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Order>.Filter.Eq("OrderId", order.OrderId);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        var update = Builders<Order>.Update.Set("Status", order.Status)
                                                            .Set("Total", order.Total)
                                                            .Set("UserId", dbList.UserId)   // No override to userId
                                                            .Set("RestaurantId", dbList.RestaurantId)    // No override to restaurantId
                                                            .Set("Dishes", order.Dishes);

                        dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order").UpdateOne(filter, update);

                        return Ok("Order update successfully!");
                    }
                    else
                    {
                        return Ok("No order found with this ID!");
                    }
                }
                else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/delete/:id
         * Delete an order
         */
        [Route("delete/{id:int}")]
        [HttpDelete]
        public IActionResult Delete(int id)
        {
            try
            {
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$")) {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Order>.Filter.Eq("OrderId", id);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order").DeleteOne(filter);

                        return Ok("Order deleted successfully!");
                    }
                    else
                    {
                        return Ok("No order found with this ID!");
                    }
                }
                else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/update/status
         * Update order status
         */
        [Route("update/status")]
        [HttpPatch]
        public IActionResult Patch(int id, OrderStatus status)
        {
            try
            {
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$")
                    && Regex.IsMatch(status.ToString(), @"^[0-2]$"))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Order>.Filter.Eq("OrderId", id);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        var update = Builders<Order>.Update.Set("Status", status);

                        dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order").UpdateOne(filter, update);

                        return Ok("Order update successfully!");
                    }
                    else
                    {
                        return Ok("No order found with this ID!");
                    }
                }
                else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/status/:id
         * Return order status
         */
        [Route("status/{orderId:int}")]
        [HttpGet]
        public IActionResult GetStatus(int orderId)
        {
            try
            {
                if (Regex.IsMatch(orderId.ToString(), @"^[1-9]\d*$")) {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Order>.Filter.Eq("OrderId", orderId);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        return Ok(dbList.Status);
                    }
                    else
                    {
                        return Ok("No order found with this ID!");
                    }
                }
                else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/dish/:id
         * Return all dishes of an order
         */
        [Route("dish/{orderId:int}")]
        [HttpGet]
        public IActionResult GetDish(int orderId)
        {
            try
            {
                if (Regex.IsMatch(orderId.ToString(), @"^[1-9]\d*$")) {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Order>.Filter.Eq("OrderId", orderId);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        return Ok(dbList.Dishes);
                    }
                    else
                    {
                        return Ok("No order found with this ID!");
                    }
                }
                else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/user/:id
         * Return all user's orders
         */
        [Route("user/{userId:int}")]
        [HttpGet]
        public IActionResult GetOrdersByUserId(int userId)
        {
            try
            {
                if (Regex.IsMatch(userId.ToString(), @"^[1-9]\d*$"))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Order>.Filter.Eq("UserId", userId);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order");
                    var dbList = collection.Find(filter).ToList();

                    if (dbList != null)
                    {
                        // Return order, ordered by status
                        // First Created order, then ReadyToPickup and Collected
                        IEnumerable<Order> newList = dbList.OrderBy(x => x.Status);
                        return Ok(newList);
                    }
                    else
                    {
                        return Ok("No orders by this user!");
                    }
                }
                else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /order/restaurant/status/
         * Return all restaurant's orders with specified status
         */
        [Route("restaurant/status/")]
        [HttpGet]
        public IActionResult GetOrdersByRestaurantAndStatus(int id, int status)
        {
            try
            {
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$")
                    && Regex.IsMatch(status.ToString(), @"^[0-2]$"))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filterRestaurantId = Builders<Order>.Filter.Eq("RestaurantId", id);
                    var filterStatus = Builders<Order>.Filter.Eq("Status", status);
                    var combineFiltersRestaurant = Builders<Order>.Filter.And(filterRestaurantId, filterStatus);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Order>("Order");
                    var dbListOrders = collection.Find(combineFiltersRestaurant).ToList();

                    if (dbListOrders != null)
                    {
                        return Ok(dbListOrders);
                    }
                    else
                    {
                        return Ok("No orders found!");
                    }
                }
                else
                {
                    return BadRequest("One or more validation errors occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }
    }
}