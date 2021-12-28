using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using MongoDB.Driver;
using Server.Models;

namespace Server.Controllers
{
    [Route("api/dish")]
    [ApiController]
    public class DishController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        public DishController(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        /*
         * API /dish/all
         * Return all dishes
         */
        [Route("all")]
        [HttpGet]
        public IActionResult Get()
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var dbList = dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish").AsQueryable();

                return Ok(dbList);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /dish/:id
         * Return the dish with the specified id
         */
        [HttpGet("{id}")]
        public IActionResult Get(int id)
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<Dish>.Filter.Eq("DishId", id);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish");
                var dbList = collection.Find(filter).FirstOrDefault();

                return Ok(dbList);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /dish/create
         * Create a new dish
         */
        [Route("create")]
        [HttpPost]
        public IActionResult Post(Dish dish)
        {
            try
            {
                // TODO: validation input // Error 400 in this case
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                int LastDishId = dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish").AsQueryable().Count();
                dish.DishId = LastDishId + 1;

                dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish").InsertOne(dish);

                return Ok("Dish added successfully!");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /dish/update
         * Update dish information
         */
        [Route("update")]
        [HttpPut]
        public IActionResult Put(Dish dish)
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<Dish>.Filter.Eq("DishId", dish.DishId);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish");
                var dbList = collection.Find(filter).FirstOrDefault();

                if (dbList != null)
                {
                    var update = Builders<Dish>.Update.Set("Name", dish.Name)
                                                        .Set("Type", dish.Type)
                                                        .Set("Price", dish.Price)
                                                        .Set("RestaurantId", dish.RestaurantId);     // TODO: not change this

                    dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish").UpdateOne(filter, update);

                    return Ok("Dish update successfully!");
                }
                else
                {
                    return Ok("No dish found with this ID!");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /dish/delete/:id
         * Delete a dish
         */
        [Route("delete/{id:int}")]
        [HttpDelete]
        public IActionResult Delete(int id)
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<Dish>.Filter.Eq("DishId", id);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish");
                var dbList = collection.Find(filter).FirstOrDefault();

                if (dbList != null)
                {
                    dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish").DeleteOne(filter);

                    return Ok("Dish deleted successfully!");
                }
                else
                {
                    return Ok("No dish found with this ID!");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /dish/restaurant/:id
         * Return all dishes with the specified restaurantId
         */
        [Route("restaurant/{restaurantId:int}")]
        [HttpGet]
        public IActionResult GetRestaurantDishes(int restaurantId)
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<Dish>.Filter.Eq("RestaurantId", restaurantId);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish");
                var dbList = collection.Find(filter).ToList();

                if (dbList != null)
                {
                    return Ok(dbList);
                }
                else
                {
                    return Ok("No dish found with this ID!");
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
