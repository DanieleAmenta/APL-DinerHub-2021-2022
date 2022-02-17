using Microsoft.IdentityModel.Tokens;
using Server.Models;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;

namespace Server.JwtManager
{
    public class JwtFunctions
    {
        // We need to use dependency injection to read variable inside appsettings.json
        private readonly IConfiguration _configuration;
        public JwtFunctions(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        public string GenerateToken(User user)
        {
            var securityKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(_configuration["Jwt:Key"]));
            var credentials = new SigningCredentials(securityKey, SecurityAlgorithms.HmacSha256);

            var isAdmin = user.IsAdmin == true ? "ADMIN" : "USER";

            var userName = user.Name != null ? user.Name : "";
            var userSurname = user.Surname != null ? user.Surname : "";

            var claims = new[]
            {
                new Claim(ClaimTypes.NameIdentifier, user.UserId.ToString()),
                new Claim(ClaimTypes.Email, user.Email),
                new Claim(ClaimTypes.Name, userName),
                new Claim(ClaimTypes.Surname, userSurname),
                new Claim(ClaimTypes.Role, isAdmin)
            };

            var token = new JwtSecurityToken(_configuration["Jwt:Issuer"],
              _configuration["Jwt:Audience"],
              claims,
              expires: DateTime.Now.AddMinutes(15),
              signingCredentials: credentials);

            return new JwtSecurityTokenHandler().WriteToken(token);
        }

        public string GenerateToken(Restaurant restaurant)
        {
            var securityKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(_configuration["Jwt:Key"]));
            var credentials = new SigningCredentials(securityKey, SecurityAlgorithms.HmacSha256);

            var claims = new[]
            {
                new Claim(ClaimTypes.NameIdentifier, restaurant.RestaurantId.ToString()),
                new Claim(ClaimTypes.Email, restaurant.Email),
                new Claim(ClaimTypes.Name, restaurant.Name),
                new Claim(ClaimTypes.Role, "RESTAURANT")
            };

            var token = new JwtSecurityToken(_configuration["Jwt:Issuer"],
              _configuration["Jwt:Audience"],
              claims,
              expires: DateTime.Now.AddMinutes(15),
              signingCredentials: credentials);

            return new JwtSecurityTokenHandler().WriteToken(token);
        }
    }
}
