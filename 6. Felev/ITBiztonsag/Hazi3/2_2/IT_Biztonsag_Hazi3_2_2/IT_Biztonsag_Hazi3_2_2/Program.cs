﻿using ICSharpCode.SharpZipLib.Zip.Compression.Streams;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Text;

namespace IT_Biztonsag_Hazi3_2_2
{
    class Program
    {
        //java -jar C:\Users\akosr\Downloads\jd-cli-1.2.0-dist\jd-cli.jar D:\BME\ITBiztonsag\Hazi3\HW-Malware-HU\files\matrijava.jar \ -skipResources -od decompiled -oc
        
        //parancssori parancs segitsegevel decompileolas
        static string decompile(string filesToDecompile, int idx, bool first)
        {
            //a program helye
            const string jd_cliPath = @"C:\Users\akosr\Downloads\jd-cli-1.2.0-dist\";
            const string options = @" -od ";
            string destination = @"D:\BME\ITBiztonsag\Hazi3\2_2\IT_Biztonsag_Hazi3_2_2\decompiled\" + idx.ToString() + @"\";

            //az osszeallitott parancs
            string command = "/C java -jar " + jd_cliPath + "jd-cli.jar " + options + destination + " " + filesToDecompile;
            //parancs vegrehalytasa
            System.Diagnostics.Process process = System.Diagnostics.Process.Start("CMD.exe", command);
            
            //ha elso fejtes, akkor mashol keresse a filet
            if(first)
                return destination + @"matrijava\matrijava\Class1.java";

            //a fejtett file helye
            return destination + @"out.java";
        }

        //filebol olvasas, sorokat ad vissza
        static List<string> readFile(string file)
        {
            List<string> lines = new List<string>();

            using (var sr = new StreamReader(file))
            {
                string line;
                while ((line = sr.ReadLine()) != null)
                {
                    lines.Add(line);
                }
            }
            return lines;
        }

        //a felyetett osztaly alapjan torteno unzip
        public static byte[] unzip(byte[] data)
        {
            var outputStream = new MemoryStream();
            using (var compressedStream = new MemoryStream(data))
            using (var inputStream = new InflaterInputStream(compressedStream))
            {
                inputStream.CopyTo(outputStream);
                outputStream.Position = 0;
                return outputStream.ToArray();
                //return outputStream;
                //StreamReader sr = new StreamReader(inputStream);
                //return Convert.ToBase64String(sr.ReadToEnd());
            }
        }

        //egy class soraibol kiszedi az osszefuzott szoveget
        public static string getcodedText(string decodedFilePath)
        {
            List<string> decodedLines = new List<string>();

            decodedLines = readFile(decodedFilePath);

            string codedText = "";

            foreach (string s in decodedLines)
            {
                //ha van a sorban append, akkor kell a fuggveny parametere
                if (s.Contains("stringBuilder.append"))
                {
                    //levagja az elejet meg a veget
                    codedText += s.Remove(s.Length - 3).Substring("stringBuilder.append".Length + 6);
                }
            }
            return codedText;
        }

        //egy lepes fuggvenye, (visszafejtendo file, probalozas szama, elso probalkozas-e)
        static bool step(string filesToDecompile, int idx, bool first = false)
        {
            //parancssori paranccsal decompilol
            string decodedFilePath = decompile(filesToDecompile, idx, first);

                
            //a decompilolt osztalybol kiszedett ossszefuzendo szoveg
            string codedText = getcodedText(decodedFilePath);

            //ha a szoveg ures vege a visszafejtesnek
            if (codedText.Equals(""))
                return false;

            //a kitomoritett byte tomb
            byte[] result = unzip(Convert.FromBase64String(codedText));

            //kiirom a bitetombot fileba
            File.WriteAllBytes(@"D:\BME\ITBiztonsag\Hazi3\2_2\IT_Biztonsag_Hazi3_2_2\decompiled\" + idx.ToString() + @"\out", result);

            //az irt file decompileolasa, aminek az eredmenye a kovetkezo lepes osztalya
            decompile(@"D:\BME\ITBiztonsag\Hazi3\2_2\IT_Biztonsag_Hazi3_2_2\decompiled\" + idx.ToString() + @"\out", idx + 1, first);

            return true;
            //step(@"D:\BME\ITBiztonsag\Hazi3\2_2\IT_Biztonsag_Hazi3_2_2\decompiled\" + (idx + 1).ToString() + @"\out.java", idx + 1);
        }

        static void Main(string[] args)
        {
            //a kiindulasi konyvtar, ahol a kiadott file talalhato
            string filesToDecompile = @" D:\BME\ITBiztonsag\Hazi3\HW-Malware-HU\files\matrijava.jar ";
            //jeloli a lepesek szamat
            int idx = 0;

            //a kiadott file visszafejtes
            step(filesToDecompile, idx++, true);

            //ciklus az egyes lepeseknek
            while (true)
            {
                if (!step(filesToDecompile, idx++)) //ha hamis, akkor megvan a megoldas
                    break;
                System.Threading.Thread.Sleep(1000); //var, hogy befejezodjon a muvelet
                //az uj visszafejteno file
                filesToDecompile = @"D:\BME\ITBiztonsag\Hazi3\2_2\IT_Biztonsag_Hazi3_2_2\decompiled\" + (idx + 1).ToString() + @"\out.java";
                
            }

            //while(step(filesToDecompile, idx++))
            //{
            //    System.Threading.Thread.Sleep(1000);
            //    filesToDecompile = @"D:\BME\ITBiztonsag\Hazi3\2_2\IT_Biztonsag_Hazi3_2_2\decompiled\" + (idx + 1).ToString() + @"\out.java";
            //}


            //Console.WriteLine(Convert.ToBase64String(result));
            //string result = Encoding.UTF8.GetString(data);

            //using (var sr = new StreamWriter("out.txt"))
            //{
            //    sr.Write(codedText);
            //}

            //decompile("out.jar", 1);
            //Console.WriteLine(result);
        }
    }
}