using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// This class for c# representation of the JSON result of the synonym request
/// </summary>

namespace Dictionary.Model
{

    //tha main class of synonyms
    public class Synonym
    {
        public Response[] response { get; set; } //the list of the synonyms
    }

    //one of responses
    public class Response
    {
        public List list { get; set; } //the list of the synonyms for this respons
    }

    //the list of the synonyms
    public class List
    {
        public string category { get; set; } //the category of the synonyms, noun, verb, etc...
        public string synonyms { get; set; } //the concatanated string of synonyms
    }


}
