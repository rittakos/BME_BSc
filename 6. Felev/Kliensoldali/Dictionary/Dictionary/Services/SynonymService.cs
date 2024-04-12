using Dictionary.Model;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// This class for the communication with the Synonym API
/// Tha communication works with http get requests, and it is asyncron
/// </summary>


namespace Dictionary.Services
{
    class SynonymService
    {
        //the unique key for the requests
        private const string key = "w4CvlqGfJFKmb5aJhF1K";
        //the main URL for the synonym API
        private const string api = "http://thesaurus.altervista.org/thesaurus/v1";

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

        //async function for the synonyms
        //the word parameter is the word,
        //and the language of the word
        public async Task<Synonym> getSynonyms(string word, string language)
        {
            return await getAsync<Synonym>(new Uri(api + "?word=" + word + "&language=" + language + "&key=" + key + "&output=json"));
        }

        //function to ask the known languages of the synonym, can not asked from the API
        public List<string> getLanguages()
        {
            return new List<string> { "cs_CZ", "da_DK", "de_CH", "de_DE", "en_US", "el_GR", "es_ES", "fr_FR", "hu_HU", "it_IT", "no_NO", "pl_PL", "pt_PT", "ro_RO", "ru_RU", "sk_SK" };
        }
    }
}
