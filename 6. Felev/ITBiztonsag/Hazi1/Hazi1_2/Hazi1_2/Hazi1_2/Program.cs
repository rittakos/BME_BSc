using System;
using System.Collections.Generic;
using System.IO;

namespace Hazi1_2
{
    class Program
    {
        static List<List<byte>> GetLines(String filename)
        {
            FileStream fs = File.OpenRead(filename);

            int length = (int)fs.Length;
            byte[] data = new byte[length];

            fs.Read(data, 0, length);

            List<List<byte>> lines = new List<List<byte>>();

            List<byte> line = new List<byte>(16);
            for (int idx = 0; idx < length; ++idx)
            {
                if (idx % 16 == 0)
                {
                    lines.Add(line);
                    line = new List<byte>(16);
                }

                line.Add(data[idx]);
            }
            lines.Add(line);

            return lines;
        }

        static List<byte> XorLineByLine(List<byte> line1, List<byte> line2)
        {
            List<byte> result = new List<byte>();
            for (int idx = 0; idx < line1.Count; ++idx)
                result.Add((byte)(line1[idx] ^ line2[idx]));
            return result;
        }

        static void Main(string[] args)
        {
            List<List<byte>> lines1 = GetLines(@"D:\BME\ITBiztonsag\Hazi1_2\Hazi1_2\Hazi1_2\LabProfile-v1.crypt");
            List<List<byte>> lines2 = GetLines(@"D:\BME\ITBiztonsag\Hazi1_2\Hazi1_2\Hazi1_2\LabProfile-v1.1.crypt");

            List<byte> spaces = new List<byte>(16);
            for (int idx = 0; idx < 16; ++idx)
                spaces.Add(32);

            List<List<byte>> result = new List<List<byte>>();
            result.Add(XorLineByLine(XorLineByLine(lines1[9], lines2[9]), spaces));

            for(int idx = 10; idx < lines2.Count; ++idx)
            {
                result.Add(XorLineByLine(XorLineByLine(lines1[idx], lines2[idx]),result[result.Count - 1]));
            }

            byte x = 1;
            Console.WriteLine("--" + (char)x + "--");

            for(int idx = 0; idx < 16; ++idx)
            {
                Console.Write(result[result.Count - 1][idx] + " ");
            }
            Console.WriteLine();
            foreach (List<byte> l in result)
                foreach (char c in l)
                    Console.Write(c);
        }
    }
}
