using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Xml.Serialization;

namespace ModernLangToolsApp
{
    //delegate a tanacs valtozasanak nyomonkovetesehez
    public delegate void CouncilChangedDelegate(string message);
    //delegate a countIf parameterenek atadasahoz
    public delegate bool Filter(Jedi jedi);

    class Program
    {
        [Description("Feladat2")]
        static void serializationTest()
        {
            Jedi Obiwan = new Jedi();

            Obiwan.Name = "Obi-Wan";
            Obiwan.MidiChlorianCount = 15000;

            XmlSerializer serializer = new XmlSerializer(typeof(Jedi));
            FileStream stream = new FileStream("jedi.txt", FileMode.Create);
            serializer.Serialize(stream, Obiwan);
            stream.Close();


            XmlSerializer ser = new XmlSerializer(typeof(Jedi));
            FileStream fs = new FileStream("jedi.txt", FileMode.Open);
            Jedi clone = (Jedi)ser.Deserialize(fs);
            fs.Close();

        }

        [Description("Feladat3")]
        static void councilTest()
        {
            JediCouncil council = new JediCouncil();
            //hozzaadja a delegatet
            council.CouncilChanged += MessageRecived;

            council.Add(new Jedi());
            council.Add(new Jedi());

            council.Remove();
            council.Remove();
        }

        [Description("Feladat4")]
        static void beginnerTest()
        {
            JediCouncil council = new JediCouncil();
            initCouncil(ref council);

            List<Jedi> beginners = council.GetBeginners();

            foreach (Jedi j in beginners)
                Console.WriteLine("{0}   {1}", j.Name, j.MidiChlorianCount);
        }

        [Description("Feladat5")]
        static void countIfTest()
        {
            JediCouncil council = new JediCouncil();
            initCouncil(ref council);

            Console.WriteLine(council.Count);

            Console.WriteLine(council.CountIf(Jozsi));
        }

        //A countIfhez hasznalt fuggveny
        static bool Jozsi(Jedi j)
        {
            //if (j.MidiChlorianCount > 10)
            if (j.Name == "Jozsi")
                return true;
            return false;
        }

        //Az inicializalo fuggveny a tanacshoz amit az 5. es 4. feladatban hasznalok
        static void initCouncil(ref JediCouncil council)
        {
            Jedi bela = new Jedi();
            bela.Name = "Bela";
            bela.MidiChlorianCount = 2346;

            Jedi jozsi = new Jedi();
            jozsi.Name = "Jozsi";
            jozsi.MidiChlorianCount = 79;

            Jedi gerzson = new Jedi();
            gerzson.Name = "Gerzson";
            gerzson.MidiChlorianCount = 23;


            council.Add(bela);
            council.Add(jozsi);
            council.Add(gerzson);
        }

        //fuggveny a tanacs valtozasat jegyzo delegethez
        static void MessageRecived(string message)
        {
            Console.WriteLine(message);
        }

        static void Main(string[] args)
        {
            serializationTest();
            Console.WriteLine();
            councilTest();
            Console.WriteLine();
            beginnerTest();
            Console.WriteLine();
            countIfTest();

        }
    }
}
