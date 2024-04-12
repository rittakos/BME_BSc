using System;
using System.Collections.Generic;
using System.IO;

namespace MusicApp
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Song> songs = new List<Song>();


            StreamReader sr = null;
            string line;

            try
            {
                sr = new StreamReader(@"c:\temp\music.txt");

                while((line = sr.ReadLine()) != null)
                {
                    string[] parts = line.Split(';');

                    if(parts.Length != 0)
                    {
                        string author = parts[0].Trim();

                        for(int idx = 1; idx < parts.Length; ++idx)
                        {
                            Song song = new Song(author, parts[idx].Trim());
                            songs.Add(song);
                        }
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("HIBA");
                Console.WriteLine(e.Message);
            }finally
            {
                if(sr != null)
                    sr.Close();
            }

            foreach(Song song in songs)
            {
                Console.WriteLine(song);
            }
        }
    }
}
