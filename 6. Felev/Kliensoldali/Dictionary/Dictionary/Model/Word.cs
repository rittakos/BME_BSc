using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// This class for the c# representation for the translation request results
/// Generated from JSON
/// Most of the classes are not used
/// </summary>

namespace Dictionary.Model
{
    //This class is made for the common representetion for the translation results and synonym results
    //It contains only the important datas
    public class ResultWord
    {
        public string text { get; set; } //the translated or synonym word
        public string pos { get; set; } //the type of the word fe.: noun, verb, etc...
    }

    //the main class for the translations c# representetion
    public class Word
    {
        public Head head { get; set; } //empty
        public Def[] def { get; set; } //contains the different deffinitins of the base word
    }

    public class Head
    {
    }

    //one of the base words definitions
    public class Def
    {
        public string text { get; set; } //the translatable word
        public string pos { get; set; } //the category of the word
        public Tr[] tr { get; set; } //the translation results
    }

    //one of the translations
    public class Tr
    {
        public string text { get; set; } //the translated word
        public string pos { get; set; } //the category of the word, noun...
        public Syn[] syn { get; set; } //the synoyms of the word, not used
        public Mean[] mean { get; set; } //the meanings of the word, not used
        public Ex[] ex { get; set; } //examples for the word, not used
    }

    //one of the synonyms, not used
    public class Syn
    {
        public string text { get; set; } //the synonym, not used
    }

    //one of the meanings, not used
    public class Mean
    {
        public string text { get; set; } //the meaning, not used
    }

    //one of the examples, not used
    public class Ex
    {
        public string text { get; set; } //the example, not used
        public Tr1[] tr { get; set; } //translations of the example, not used
    }

    //translation of one of the examples, not used, simpler than the main translation (Tr)
    public class Tr1
    {
        public string text { get; set; } //the translation of the example, not used
    }

}
