using Dictionary.Model;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Threading.Tasks;

/// <summary>
/// This class for the communication with the Dictionary API
/// Tha communication works with http get requests, and it is asyncron
/// </summary>

namespace Dictionary.Services
{
    class DictionaryService
    {
        //the main URL for the dictionary API
        private readonly Uri APIUrl = new Uri("https://dictionary.yandex.net/api/v1/dicservice.json");
        //the unique key for the requests
        private readonly string key ="dict.1.1.20210430T075226Z.4c52d1197591553a.140645815d9a9917fc293be3af7d089413da206b";

        //async template funkcion for the http get request, the answer body is json
        private async Task<T> getAsync<T>(Uri uri)
        {
            using (var client = new HttpClient())
            {
                var response = await client.GetAsync(uri); 
                var json = await response.Content.ReadAsStringAsync();
                T result = JsonConvert.DeserializeObject<T>(json); //convert the json to c# object
                return result;
            }
        }
      
        //async function to ask the known languages of the dictionary
        public async Task<List<string>> getLanguages()
        {
            string url = APIUrl + "/getLangs?key=" + key; //the getLangs part is for the supported languages
            return await getAsync<List<string>>(new Uri(url));
        }

        //async function for the translations
        //the word parameter is the word, we like to translate,
        //and the language is a language pair from-to
        public async Task<Word> getMeaning(string word, string language)
        {
            //the lookap part is for the translation, the lang is the language parameter and the text is the word parameter.
            string url = APIUrl + "/lookup?key=" + key + "&lang=" + language + "&text=" + word; 
            return await getAsync<Word>(new Uri(url));
        }
    }
}
