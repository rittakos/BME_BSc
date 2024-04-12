using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MultiThreadedApp
{  
    public partial class Form1 : Form
    {
        private object syncObject = new Object();


        //A start panelen megallasert felelosek
        ManualResetEvent canContinue = new ManualResetEvent(false);
        bool stopped = false;

        //A rest panelen megallasert felelosek
        AutoResetEvent rested = new AutoResetEvent(false);
        bool rest = false;

        long pixels = 0; //Az eddig megtett pixelek
        int startPos; //A biciklik kezdo pixele

        public Form1()
        {
            InitializeComponent();
        }

        private void bStart_Click(object sender, EventArgs e)
        {

            //Elindulnak a biciklik
            startPos = bBike1.Left;
            canContinue.Reset();
            rested.Reset();
            startBike(bBike1);
            startBike(bBike2);
            startBike(bBike3);
        }

        private void startBike(Button bBike)
        {
            //Letrejon egy szal ami a bicikli mozgasat szamolja
            Thread t = new Thread(BikeThreadFunction);
            bBike.Tag = t; //Eltarolja a szalat
            t.IsBackground = true; // Ne blokkolja a szál a processz megszűnését
            t.Start(bBike);
        }

        public void BikeThreadFunction(object param)
        {
            Button bike = (Button)param;
            //bike.Tag = Thread.CurrentThread;
            while (bike.Left < pTarget.Left)//Addig megy amig el nem eri a celpanelt
            {
                if (bike.Left >= pStart.Left && !stopped) //Amikor eleri a startpanelt
                {
                    //Addig var amig a Step1 megnyomasa at nem allitja a canContinuet
                    if (WaitHandle.WaitAny(new WaitHandle[] { canContinue }) == 0)
                    {
                        stopped = true;
                    }
                }

                if (bike.Left >= pRest.Left && !rest) //Amikor eleri a restpanelt
                {
                    //Addig var amig a Step2 megnyomasa at nem allitja a restedt
                    if (WaitHandle.WaitAny(new WaitHandle[] { rested }) == 0)
                    {
                        rest = true;
                    }
                }
                MoveBike(bike); //Mozog a bicikli
                Thread.Sleep(100);
            }
        }

        void increasePixels(long step)
        {
            //kolcsonos kizarassal noveli a megtett pixeleket
            lock (syncObject)
            {
                pixels += step;
            }
        }

        long getPixels()
        {
            //kolcsonos kizarassal lekeri a megtett pixeleket
            lock (syncObject)
            {
                return pixels;
            }
        }

        delegate void BikeAction(Button bike); //delegate a bicikli mozgatasara
        Random random = new Random();

        public void MoveBike(Button bike)
        {
            if (InvokeRequired)
            {
                Invoke(new BikeAction(MoveBike), bike);
            }
            else
            {
                int moveValue = random.Next(3, 9);
                bike.Left += moveValue;
                increasePixels(moveValue);
            }
        }

        private void bStep1_Click(object sender, EventArgs e)
        {
            canContinue.Set();
        }

        private void bStep2_Click(object sender, EventArgs e)
        {
            rested.Set();
        }

        private void bPixels_Click(object sender, EventArgs e)
        {
            bPixels.Text = Convert.ToString(getPixels());
        }
    
        private void bike_Click(object sender, EventArgs e)
        {
            try
            {
                Button bike = (Button)sender;
                Thread thread = (Thread)bike.Tag;

                if (thread == null)
                    return;

                thread.Interrupt();

                thread.Join();

                bike.Left = startPos;
                stopped = false;
                rest = false;

                canContinue.Reset();
                rested.Reset();

                startBike(bike);

            }catch(ThreadInterruptedException)
            {

            }
        }
    }
}
