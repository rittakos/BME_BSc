using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace SuperCalculator
{
    class DataFifo
    {
        private List<double[]> innerList = new List<double[]>();
        private object syncObject = new object();
        ManualResetEvent hasData = new ManualResetEvent(false);
        ManualResetEvent releaseWorkers = new ManualResetEvent(false);

        public void SignalRelesdeWorkers()
        {
            releaseWorkers.Set();
        }

        public void Put( double[] data )
        {
            lock (syncObject)
            {
                innerList.Add(data);
                hasData.Set();
            }
        }

        public bool TryGet(out double[] data)
        {
            data = null;
            
            if (WaitHandle.WaitAny(new WaitHandle[] { hasData, releaseWorkers}) == 0)
            {
                lock (syncObject)
                {
                    if (innerList.Count > 0)
                    {
                        // Egy kis mesters�ges k�sleltet�s, ami nem befoly�solhatja, 
                        // hogy helyesen m�k�dik-e a FIFO.
                        // Thread.Sleep(500);
                        data = innerList[0];
                        innerList.RemoveAt(0);
                        if (innerList.Count == 0)
                            hasData.Reset();
                        return true;
                    }
                    else
                        return false;
                }
            }
            else return false;
        }
    }
}
