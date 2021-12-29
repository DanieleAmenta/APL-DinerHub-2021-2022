using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using MongoDB.Driver;
using Server.Models;
using System.Text.RegularExpressions;

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
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$"))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Restaurant>.Filter.Eq("RestaurantId", id);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    return Ok(dbList);
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
         * API /restaurant/create
         * Insert a new restaurant
         */
        [Route("create")]
        [HttpPost]
        public IActionResult Post(Restaurant restaurant)
        {
            try
            {
                // TODO: encode password
                if (Regex.IsMatch(restaurant.Name.ToString(), @"^[a-zA-Z]{2,}$")
                    && Regex.IsMatch(restaurant.Address.ToString(), @"^[a-zA-Z]{2,}$")
                    && Regex.IsMatch(restaurant.Psw.ToString(), @"^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d\w\W]{8,}$")
                    && Regex.IsMatch(restaurant.Phone.ToString(), @"^\s*(?:\+?(\d{1,3}))?[-. (]*(\d{3})[-. )]*(\d{3})[-. ]*(\d{4})(?: *x(\d+))?\s*$")
                    && Regex.IsMatch(restaurant.Email.ToString().ToLower(), @"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$")
                    )
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    // Email must be unique
                    var filterEmailRestaurant = Builders<Restaurant>.Filter.Eq("Email", restaurant.Email);
                    var collectionRestaurant = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant");
                    var dbListRestaurant = collectionRestaurant.Find(filterEmailRestaurant).FirstOrDefault();

                    var filterEmailUser = Builders<User>.Filter.Eq("Email", restaurant.Email);
                    var collectionUser = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                    var dbListUser = collectionUser.Find(filterEmailUser).FirstOrDefault();

                    if (dbListRestaurant == null && dbListUser == null)
                    {
                        // Get last element and create a new id for the new user
                        var dbRestaurantList = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant").AsQueryable().ToList();
                        int LastRestaurantId = dbRestaurantList.Last().RestaurantId;
                        restaurant.RestaurantId = LastRestaurantId + 1;

                        restaurant.Email = restaurant.Email.ToLower();

                        dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant").InsertOne(restaurant);

                        return Ok("Restaurant added successfully!");
                    }
                    else
                    {
                        return BadRequest("Email already in use!");
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
         * API /restaurant/update
         * Update restaurant information
         */
        [Route("update")]
        [HttpPut]
        public IActionResult Put(Restaurant restaurant)
        {
            try
            {
                    if (Regex.IsMatch(restaurant.Name.ToString(), @"^[a-zA-Z]{2,}$")
                        && Regex.IsMatch(restaurant.Address.ToString(), @"^[a-zA-Z]{2,}$")
                        && Regex.IsMatch(restaurant.Psw.ToString(), @"^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d\w\W]{8,}$")
                        && Regex.IsMatch(restaurant.Phone.ToString(), @"^\s*(?:\+?(\d{1,3}))?[-. (]*(\d{3})[-. )]*(\d{3})[-. ]*(\d{4})(?: *x(\d+))?\s*$")
                        && Regex.IsMatch(restaurant.Email.ToString().ToLower(), @"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$")
                        )
                    {
                        MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                        var filter = Builders<Restaurant>.Filter.Eq("RestaurantId", restaurant.RestaurantId);

                        var collection = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant");
                        var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        // Email must be unique
                        var filterEmailRestaurant = Builders<Restaurant>.Filter.Eq("Email", restaurant.Email);
                        var collectionRestaurant = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant");
                        var dbListRestaurant = collectionRestaurant.Find(filterEmailRestaurant).FirstOrDefault();

                        if (dbListRestaurant == null)
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
                            return BadRequest("Email already in use!");
                        }
                    }
                    else
                    {
                        return Ok("No restaurant found with this ID!");
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
         * API /restaurant/delete/:id
         * Delete a restaurant
         */
        [Route("delete/{id:int}")]
        [HttpDelete]
        public IActionResult Delete(int id)
        {
            try
            {
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$"))
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
