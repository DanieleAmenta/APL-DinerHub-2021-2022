using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using MongoDB.Driver;
using Server.Models;
using Microsoft.AspNetCore.Http;

namespace Server.Controllers
{
    [Route("api/user")]
    [ApiController]
    public class UserController : ControllerBase
    {
        // We need to use dependency injection to read variable inside appsettings.json
        private readonly IConfiguration _configuration;
        public UserController(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        /*
         * API /user/all
         * Return all users
         */
        [Route("all")]
        [HttpGet]
        public IActionResult Get()
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<User>.Filter.Eq("IsAdmin", false);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");

                var dbList = collection.Find(filter).ToList();

                // The response code is always 200 because
                // even if the list is empty, empty list is also an information
                return Ok(dbList);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /user/:id
         * Return the user with the specified id
         */
        [HttpGet("{id}")]
        public IActionResult Get(int id)
        {
            try
            {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<User>.Filter.Eq("UserId", id);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");

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
         * API /user/registration
         * Register a user
         */
        [Route("registration")]
        [HttpPost]
        public IActionResult Post(User user)
        {
            try {
                // TODO: encode password
                // TODO: validation input
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                // TODO: unique email
                int LastUserId = dbClient.GetDatabase("dinerhub").GetCollection<User>("User").AsQueryable().Count();
                user.UserId = LastUserId + 1;

                dbClient.GetDatabase("dinerhub").GetCollection<User>("User").InsertOne(user);

                return Ok("User added successfully");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /user/login
         * User login
         */
        [Route("login")]
        [HttpPost]
        public IActionResult Post(string email, string psw)
        {
            try {
                // TODO: Check if email and psw are null // Error 400 in this case
                // TODO: Check only in lowercase
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var emailFilterUser = Builders<User>.Filter.Eq("Email", email);
                var pswFilterUser = Builders<User>.Filter.Eq("Psw", psw);
                var combineFiltersUser = Builders<User>.Filter.And(emailFilterUser, pswFilterUser);

                var collectionUser = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                var dbListUser = collectionUser.Find(combineFiltersUser).FirstOrDefault();

                if (dbListUser == null)
                {
                    // If is not an Admin or an User, it could be a Restaurant
                    var emailFilterRestaurant = Builders<Restaurant>.Filter.Eq("Email", email);
                    var pswFilterRestaurant = Builders<Restaurant>.Filter.Eq("Psw", psw);
                    var combineFiltersRestaurant = Builders<Restaurant>.Filter.And(emailFilterRestaurant, pswFilterRestaurant);

                    var collectionRestaurant = dbClient.GetDatabase("dinerhub").GetCollection<Restaurant>("Restaurant");
                    var dbListRestaurant = collectionRestaurant.Find(combineFiltersRestaurant).FirstOrDefault();

                    return Ok(dbListRestaurant);
                }

                // If the user not exist, the status code is 204 (No Content)
                return Ok(dbListUser);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /user/update
         * Update user information
         */
        [Route("update")]
        [HttpPut]
        public IActionResult Put(User user)
        {
            try {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<User>.Filter.Eq("UserId", user.UserId);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                var dbList = collection.Find(filter).FirstOrDefault();

                if (dbList != null)
                {
                    var update = Builders<User>.Update.Set("Name", user.Name)
                                                        .Set("Surname", user.Surname)
                                                        .Set("Email", user.Email)
                                                        .Set("Psw", user.Psw)
                                                        .Set("Phone", user.Phone)
                                                        .Set("BirthDate", user.BirthDate)
                                                        .Set("IsAdmin", user.IsAdmin);

                    dbClient.GetDatabase("dinerhub").GetCollection<User>("User").UpdateOne(filter, update);

                    return Ok("User update successfully!");
                } else
                {
                    return Ok("No user found with this ID!");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /user/delete/:id
         * Delete an user
         */
        [Route("delete/{id:int}")]
        [HttpDelete]
        public IActionResult Delete(int id)
        {
            try {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<User>.Filter.Eq("UserId", id);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                var dbList = collection.Find(filter).FirstOrDefault();

                if (dbList != null)
                {
                    dbClient.GetDatabase("dinerhub").GetCollection<User>("User").DeleteOne(filter);

                    return Ok("User deleted successfully!");
                } else
                {
                    return Ok("No user found with this ID!");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /user/update/balance/
         * Update user balance, both increase and decrease
         */
        [Route("update/balance/")]
        [HttpPatch]
        public IActionResult Patch(int id, double balance)
        {
            try {
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<User>.Filter.Eq("UserId", id);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                var dbList = collection.Find(filter).FirstOrDefault();

                // TODO: check on balance value (not go in negative values)
                // Error 400 in this case
                if (dbList != null)
                {
                    var oldBalance = dbList.Balance;
                    var update = Builders<User>.Update.Set("Balance", oldBalance + balance);

                    dbClient.GetDatabase("dinerhub").GetCollection<User>("User").UpdateOne(filter, update);

                    return Ok("Balance update successfully!");
                }
                else
                {
                    return Ok("No user found with this ID!");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Internal Server Error: ", ex.Message);
                return new StatusCodeResult(StatusCodes.Status500InternalServerError);
            }
        }

        /*
         * API /user/balance/:id
         * Return user balance
         */
        [Route("balance/{id:int}")]
        [HttpGet]
        public IActionResult GetBalanceUserId(int id)
        {
            try
            {
                // TODO: check if parameter is int
                MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                var filter = Builders<User>.Filter.Eq("UserId", id);

                var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                var dbList = collection.Find(filter).FirstOrDefault();

                if (dbList != null)
                {
                    return Ok(dbList.Balance);
                }
                else
                {
                    return Ok("No user found with this ID!");
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