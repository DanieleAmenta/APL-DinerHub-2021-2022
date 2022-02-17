using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace Server.Controllers
{
    [Route("")]
    [ApiController]
    public class ServerController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        public ServerController(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        /*
         * API /ping
         */
        [Route("ping")]
        [HttpGet]
        [AllowAnonymous]
        public IActionResult Ping()
        {
            return Ok("Pong");
        }
    }
}
