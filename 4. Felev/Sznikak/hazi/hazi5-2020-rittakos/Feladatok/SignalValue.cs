using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Signals
{
    public class SignalValue
    {
        public readonly double Value;
        public readonly DateTime TimeStamp;

        public SignalValue(double value, DateTime timeStamp)
        {
            Value = value;
            TimeStamp = timeStamp;
        }

        public override string ToString()
        {
            return string.Format("Value: {0}, TimeStamp: {1}", Value, TimeStamp);
        }
    }
}
