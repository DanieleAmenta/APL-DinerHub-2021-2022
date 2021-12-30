using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using MongoDB.Driver;
using Server.Models;
using Microsoft.AspNetCore.Http;
using System.Text.RegularExpressions;

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
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$"))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<User>.Filter.Eq("UserId", id);
                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    // Hide password
                    dbList.Psw = "";

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
         * API /user/registration
         * Register a user
         */
        [Route("registration")]
        [HttpPost]
        public IActionResult Post(User user)
        {
            try {
                if (Regex.IsMatch(user.Name.ToString(), @"^[a-zA-Z]{2,}$")
                    && Regex.IsMatch(user.Surname.ToString(), @"^[a-zA-Z]{2,}$")
                    && Regex.IsMatch(user.Phone.ToString(), @"^\s*(?:\+?(\d{1,3}))?[-. (]*(\d{3})[-. )]*(\d{3})[-. ]*(\d{4})(?: *x(\d+))?\s*$")
                    && Regex.IsMatch(user.Email.ToString().ToLower(), @"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$")
                    )
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    // Email must be unique
                    var filterEmailUser = Builders<User>.Filter.Eq("Email", user.Email);
                    var collectionUser = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                    var dbListUser = collectionUser.Find(filterEmailUser).FirstOrDefault();

                    if (dbListUser == null)
                    {
                        // Get last element and create a new id for the new user
                        var dbUserList = dbClient.GetDatabase("dinerhub").GetCollection<User>("User").AsQueryable().ToList();
                        int LastUserId = dbUserList.Last().UserId;
                        user.UserId = LastUserId + 1;

                        user.Balance = 0.00;
                        user.Email = user.Email.ToLower();

                        dbClient.GetDatabase("dinerhub").GetCollection<User>("User").InsertOne(user);

                        return Ok("User added successfully");
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
         * API /user/login
         * User login
         */
        [Route("login")]
        [HttpPost]
        public IActionResult Post(string email, string psw)
        {
            try {
                if (Regex.IsMatch(email.ToString().ToLower(), @"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$"))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var emailFilterUser = Builders<User>.Filter.Eq("Email", email.ToLower());
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
         * API /user/update
         * Update user information
         */
        [Route("update")]
        [HttpPut]
        public IActionResult Put(User user)
        {
            try {
                if (Regex.IsMatch(user.UserId.ToString(), @"^[1-9]\d*$")
                    && Regex.IsMatch(user.Name.ToString(), @"^[a-zA-Z]{2,}$")
                    && Regex.IsMatch(user.Surname.ToString(), @"^[a-zA-Z]{2,}$")
                    && Regex.IsMatch(user.Phone.ToString(), @"^\s*(?:\+?(\d{1,3}))?[-. (]*(\d{3})[-. )]*(\d{3})[-. ]*(\d{4})(?: *x(\d+))?\s*$")
                    && Regex.IsMatch(user.Email.ToString().ToLower(), @"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$")
                    )
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<User>.Filter.Eq("UserId", user.UserId);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        // Email must be unique
                        var filterEmailUser = Builders<User>.Filter.Eq("Email", user.Email);
                        var filterIdUser = Builders<User>.Filter.Ne("UserId", user.UserId);

                        var combineFiltersEmail = Builders<User>.Filter.And(filterEmailUser, filterIdUser);

                        var collectionUser = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                        var dbListUser = collectionUser.Find(combineFiltersEmail).FirstOrDefault();

                        if (dbListUser == null)
                        {
                            var update = Builders<User>.Update.Set("Name", user.Name)
                                                            .Set("Surname", user.Surname)
                                                            .Set("Email", user.Email.ToLower())
                                                            .Set("Psw", user.Psw)
                                                            .Set("Phone", user.Phone)
                                                            .Set("BirthDate", user.BirthDate)
                                                            .Set("IsAdmin", user.IsAdmin);

                            dbClient.GetDatabase("dinerhub").GetCollection<User>("User").UpdateOne(filter, update);

                            return Ok("User update successfully!");
                        }
                        else
                        {
                            return BadRequest("Email already in use!");
                        }
                    }
                    else
                    {
                        return Ok("No user found with this ID!");
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
         * API /user/delete/:id
         * Delete an user
         */
        [Route("delete/{id:int}")]
        [HttpDelete]
        public IActionResult Delete(int id)
        {
            try {
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$")) {
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
         * API /user/update/balance/
         * Update user balance, both increase and decrease
         */
        [Route("update/balance/")]
        [HttpPatch]
        public IActionResult Patch(int id, double balance)
        {
            try {
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$")
                    && Regex.IsMatch(balance.ToString(), @"^[1-9]\d*$"))
                {
                    MongoClient dbClient = new MongoClient(_configuration.GetConnectionString("DinerHubConn"));

                    var filter = Builders<User>.Filter.Eq("UserId", id);

                    var collection = dbClient.GetDatabase("dinerhub").GetCollection<User>("User");
                    var dbList = collection.Find(filter).FirstOrDefault();

                    if (dbList != null)
                    {
                        double oldBalance = (double)dbList.Balance;
                        double newBalance = oldBalance + balance;

                        if (newBalance >= 0)
                        {
                            var update = Builders<User>.Update.Set("Balance", newBalance);

                            dbClient.GetDatabase("dinerhub").GetCollection<User>("User").UpdateOne(filter, update);

                            return Ok("Balance update successfully!");
                        } else
                        {
                            return BadRequest("Not enough balance!");
                        }
                        
                    }
                    else
                    {
                        return Ok("No user found with this ID!");
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
         * API /user/balance/:id
         * Return user balance
         */
        [Route("balance/{id:int}")]
        [HttpGet]
        public IActionResult GetBalanceUserId(int id)
        {
            try
            {
                if (Regex.IsMatch(id.ToString(), @"^[1-9]\d*$"))
                {
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