using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;

namespace ModernLangToolsApp
{
    [XmlRoot("Jedi")]
    public class Jedi
    {
        private string _name;
        private int _midiChlorianCount;

        [XmlAttribute("Nev")]
        //a _namehez tartozo property
        public string Name { get => _name; set => _name = value; }

        [XmlAttribute("MidiChlorianSzam")]
        //a _midichlorianCounthoz tartozo property
        public int MidiChlorianCount
        {
            get => _midiChlorianCount;

            set
            {
                if (value <= 10)
                    throw new ArgumentException("You are not a true jedi!");
                _midiChlorianCount = value;
            }
        }
    }
}
