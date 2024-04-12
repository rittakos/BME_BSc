using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Signals
{
    public class SignalDocument : Document
    {
        private List<SignalValue> signals;

        private SignalValue[] testValues = new SignalValue[]
        {
            new SignalValue(-1.3, new DateTime(1999, 4, 5, 11, 11, 11)),
            new SignalValue(1.9, new DateTime(2000, 7, 29, 5, 32, 01)),
            new SignalValue(2.3, new DateTime(2001, 9, 1, 1, 45, 34)),
            new SignalValue(-2.0, new DateTime(2002, 1, 31, 17, 56, 55))
        };

        public IReadOnlyList<SignalValue> Signals
        {
            get { return signals; }
        }

        public SignalDocument(string name) : base(name) 
        {
            signals = new List<SignalValue>();
            signals.AddRange(testValues);   
        }

        public override void SaveDocument(string filePath)
        {
            using (StreamWriter sw = new StreamWriter(filePath))
            {
                foreach (SignalValue signal in signals)
                {
                    string dt = signal.TimeStamp.ToUniversalTime().ToString("o");

                    sw.WriteLine(signal.Value.ToString() + '\t' + dt);
                }
            }
            
        }

        public override void LoadDocument(string filePath)
        {
            signals.Clear();
            using (StreamReader sr = new StreamReader(filePath))
            {
                string line;
                while ((line = sr.ReadLine()) != null)
                {
                    string[] columns = line.Split('\t');
                    double value = double.Parse(columns[0]);
                    DateTime dt = DateTime.Parse(columns[1]);
                    DateTime local = dt.ToLocalTime();
                    SignalValue sv = new SignalValue(value, dt);
                    signals.Add(sv);
                }
            }
            UpdateAllViews();
            TraceValues();
        }

        void TraceValues()
        {
            foreach (SignalValue signal in signals)
                Trace.WriteLine(signal.ToString());
        }
    }
}
