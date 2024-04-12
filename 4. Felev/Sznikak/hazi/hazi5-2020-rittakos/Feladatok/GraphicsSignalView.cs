using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Diagnostics;

namespace Signals
{
    //Megvalositja az IView interfacet
    public partial class GraphicsSignalView : UserControl, IView
    { 
        //a dokumentum, melynek adatait a nezet megjeleniti
        private SignalDocument document;

        private double skalar = 1; //skalartenyezo, alapertelmezetten 1

        //default konstruktor
        public GraphicsSignalView() 
        {
            InitializeComponent();
        }

        //egyparameteres konstruktor
        public GraphicsSignalView(SignalDocument document)
        {
            InitializeComponent();
            this.document = document;
        }


        //a view sorszama
        private int viewNumber;
        public int ViewNumber 
        {
            get { return viewNumber; }
            set { viewNumber = value; }
        }

        //visszater a tarolt documet-tel
        public Document GetDocument()
        {
            return document;
        }

        private void PaintCoordinateSystem(PaintEventArgs e)// koordinatatengelyek kirajzolasa
        {
            Pen pen = new Pen(Color.Green, 2); //zold szinu
            pen.DashStyle = DashStyle.Dot; //pontozott
            pen.EndCap = LineCap.ArrowAnchor; //nyil van rajta

            e.Graphics.DrawLine(pen, 1, ClientSize.Height, 1, 0); //y tengely
            e.Graphics.DrawLine(pen, 0, ClientSize.Height / 2, ClientSize.Width, ClientSize.Height / 2); //x tengely
        }

        //kiszamolja az ertekek alapjan a pontok koordinatait
        private List<Point> CalculatePoints(double pixelPerSec, double pixelPerValue, IReadOnlyList<SignalValue> signals)
        {
            List<Point> points = new List<Point>(); //az abrazolando pontok
            int x = 1; //alapertelmezetten az x tengelyen van
            int y = 0;
            for (int idx = 0; idx < signals.Count; ++idx) //pontok kiszamitasa
            {
                y = ClientSize.Height / 2; //alapertelmezetten az y tengelyen van
                y -= Convert.ToInt32(signals[idx].Value * pixelPerValue * skalar); //a balfelso sarok 0;0 ezert levonni kell nem hozzaadni
                if (idx != 0) //az also elemnel x = 1;
                {
                    x += Convert.ToInt32((signals[idx].TimeStamp - signals[idx - 1].TimeStamp).Seconds * pixelPerSec * skalar); //a ket ido kulonbsege tickben szorozva az aranyszammal
                }

                points.Add(new Point(x, y)); //eltarolom a pontot a kiszamolt koordinatakkal
            }
            return points;
        }

        //kirajzolja a diagrammot
        private void DrawDiagramm(PaintEventArgs e, List<Point> points)
        {
            Brush brush = new SolidBrush(Color.Blue); //kek szinu brush, a teglalaprajzolashoz
            foreach (Point p in points) //vegigmegyek a pontokon
                e.Graphics.FillRectangle(brush, p.X - 1, p.Y - 1, 3, 3); //3 oldalu negyzet, aminek a kozepe a ponton van

            Pen pe = new Pen(Color.Blue); //kek pen
            for (int idx = 0; idx < points.Count - 1; ++idx) //vegigmegy a pontokon, az utolsot leszamitva
                e.Graphics.DrawLine(pe, points[idx], points[idx + 1]); //oszekot ket egymast koveto pontot
        }

        //abrazolja a document adatait
        protected override void OnPaint(PaintEventArgs e)
        {
            PaintCoordinateSystem(e);

            double pixelPerSec = 4; //az x tengely surusege
            double pixelPerValue = 50; //az y tengely surusege

            IReadOnlyList<SignalValue> signals = document.Signals; //az abrazolando jelek

            List<Point> points = CalculatePoints(pixelPerSec, pixelPerValue, signals); //a diagramm pontjai

            DrawDiagramm(e, points); //kirajzolja a diagrammot

        }

        //Nagyitas novelese
        private void bEnlarge_Click(object sender, EventArgs e)
        {
            skalar *= 1.2; //a skalar novelese
            Invalidate();
        }

        //Nagyitas kicsinyitese
        private void bReduct_Click(object sender, EventArgs e)
        {
            skalar /= 1.2; //a skalar novelese
            Invalidate();
        }
    }
}
