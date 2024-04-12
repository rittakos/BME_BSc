using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// The language class for the from to language pairs
/// Only for the translation requests
/// </summary>

namespace Dictionary.Model
{
    class Language
    {
        public string from { get; set; } //the from language
        public string to { get; set; } //the to language

        public string toString() //conver to string for the API
        {
            return from + "-" + to;
        }
    }
}
