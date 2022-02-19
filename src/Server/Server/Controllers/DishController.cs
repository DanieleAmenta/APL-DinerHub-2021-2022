using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using MongoDB.Driver;
using Server.Models;
using System.Text.RegularExpressions;

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
        [Authorize(Roles = "ADMIN")]
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
        [Route("{id}")]
        [HttpGet]
        [Authorize(Roles = "ADMIN, USER, RESTAURANT")]
        public IActionResult Get(int id)
        {
            try
            {
                if (Regex.IsMatch(id.ToString(), _configuration["Regex:Id"]))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<Dish>.Filter.Eq("DishId", id);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish");
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
         * API /dish/create
         * Create a new dish
         */
        [Route("create")]
        [HttpPost]
        [Authorize(Roles = "ADMIN, RESTAURANT")]
        public IActionResult Post(Dish dish)
        {
            try
            {
                if (Regex.IsMatch(dish.Name.ToString(), _configuration["Regex:DishName"])
                        && Regex.IsMatch(dish.Price.ToString(), _configuration["Regex:DishPrice"])
                        )
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    // Get last element and create a new id for the new user
                    var dbDishList = dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish").AsQueryable().ToList();
                    int LastDishId = dbDishList.Count > 0 ? dbDishList.Last().DishId : 0;
                    dish.DishId = LastDishId + 1;

                    dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish").InsertOne(dish);

                    return Ok("Dish added successfully!");
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
         * API /dish/update
         * Update dish information
         */
        [Route("update")]
        [HttpPut]
        [Authorize(Roles = "ADMIN, RESTAURANT")]
        public IActionResult Put(Dish dish)
        {
            try
            {
                if (Regex.IsMatch(dish.Name.ToString(), _configuration["Regex:DishName"])
                        && Regex.IsMatch(dish.Price.ToString(), _configuration["Regex:DishPrice"])
                        )
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
                                                            .Set("RestaurantId", dbList.RestaurantId);     // Cannot override RestaurantId

                        dbClient.GetDatabase("dinerhub").GetCollection<Dish>("Dish").UpdateOne(filter, update);

                        return Ok("Dish update successfully!");
                    }
                    else
                    {
                        return Ok("No dish found with this ID!");
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
         * API /dish/delete/:id
         * Delete a dish
         */
        [Route("delete/{id:int}")]
        [HttpDelete]
        [Authorize(Roles = "ADMIN, RESTAURANT")]
        public IActionResult Delete(int id)
        {
            try
            {
                if (Regex.IsMatch(id.ToString(), _configuration["Regex:Id"]))
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
         * API /dish/restaurant/:id
         * Return all dishes with the specified restaurantId
         */
        [Route("restaurant/{restaurantId:int}")]
        [HttpGet]
        [Authorize(Roles = "ADMIN, USER, RESTAURANT")]
        public IActionResult GetRestaurantDishes(int restaurantId)
        {
            try
            {
                if (Regex.IsMatch(restaurantId.ToString(), _configuration["Regex:Id"]))
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
