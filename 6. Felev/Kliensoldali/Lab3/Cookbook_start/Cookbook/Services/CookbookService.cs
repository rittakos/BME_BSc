using Cookbook.Models;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Template10;

namespace Cookbook.Services
{
    class CookbookService
    {
        private async Task<T> GetAsync<T>(Uri uri)
        {
            using (var client = new HttpClient())
            {
                var response = await client.GetAsync(uri);
                var json = await response.Content.ReadAsStringAsync();
                T result = JsonConvert.DeserializeObject<T>(json);
                return result;
            }
        }

        private readonly Uri serverUrl = new Uri("https://bmecookbook.azurewebsites.net");
        public async Task<List<RecipeGroup>> GetRecipeGroupsAsync()
        {
            return await GetAsync<List<RecipeGroup>>(new Uri(serverUrl, "api/Recipes/Groups"));
        }

        public async void PostCommentAsync(Dictionary<string, string> values)
        {
            using (var client = new HttpClient())
            {
                var content = new FormUrlEncodedContent(values);
                var response = await client.PostAsync(new Uri(serverUrl, "api/Recipes/{id}/Comments"), content);
                var responseString = await response.Content.ReadAsStringAsync();
            }
        }

        public async Task<Recipe> GetRecipeAsync(int id)
        {
            return await GetAsync<Recipe>(new Uri(serverUrl, $"api/Recipes/{id}"));
        }
    }
}
