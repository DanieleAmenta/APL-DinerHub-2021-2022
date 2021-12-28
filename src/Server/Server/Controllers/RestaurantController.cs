using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using MongoDB.Driver;
using Server.Models;

namespace Server.Controllers
{
    [Route("api/restaurant")]
    [ApiController]
    public class RestaurantController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        public RestaurantController(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        /*
         * API /restaurant/all
         * Return all restaurants
         */
        [Route("all")]
        [HttpGet]
        public IActionResult Get()
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var dbList = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant").AsQueryable();

                return Ok(dbList);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /restaurant/:id
         * Return the restaurant with the specified id
         */
        [HttpGet("{id}")]
        public IActionResult Get(int id)
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<Restaurant>.Filter.Eq("RestaurantId", id);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant");
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
         * API /restaurant/create
         * Insert a new restaurant
         */
        [Route("create")]
        [HttpPost]
        public IActionResult Post(Restaurant restaurant)
        {
            try
            {
                // TODO: validation input // Error 400 in this case
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                int LastRestaurantId = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant").AsQueryable().Count();
                restaurant.RestaurantId = LastRestaurantId + 1;

                dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant").InsertOne(restaurant);

                return Ok("Restaurant added successfully!");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /restaurant/update
         * Update restaurant information
         */
        [Route("update")]
        [HttpPut]
        public IActionResult Put(Restaurant restaurant)
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<Restaurant>.Filter.Eq("RestaurantId", restaurant.RestaurantId);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant");
                var dbList = collection.Find(filter).FirstOrDefault();

                if (dbList != null)
                {
                    var update = Builders<Restaurant>.Update.Set("Name", restaurant.Name)
                                                        .Set("Address", restaurant.Address)
                                                        .Set("Phone", restaurant.Phone)
                                                        .Set("Email", restaurant.Email)
                                                        .Set("Psw", restaurant.Psw)
                                                        .Set("IsRestaurant", true);     // Cannot override IsRestaurant

                    dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant").UpdateOne(filter, update);

                    return Ok("Update Successfully");
                }
                else
                {
                    return Ok("No restaurant found with this ID!");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /restaurant/delete/:id
         * Delete a restaurant
         */
        [Route("delete/{id:int}")]
        [HttpDelete]
        public IActionResult Delete(int id)
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<Restaurant>.Filter.Eq("RestaurantId", id);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant");
                var dbList = collection.Find(filter).FirstOrDefault();

                if (dbList != null)
                {
                    dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant").DeleteOne(filter);

                    return Ok("Deleted Successfully");
                }
                else
                {
                    return Ok("No restaurant found with this ID!");
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
