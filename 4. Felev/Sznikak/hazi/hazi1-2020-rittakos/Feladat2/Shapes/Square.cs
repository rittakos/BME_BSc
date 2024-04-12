using System;
using System.Collections.Generic;
using System.Text;

namespace Shapes
{
    class Square : Shape
    {
        private double a;

        public Square(int a, int x, int y) : base(x, y)
        {
            this.a = a;
        }


        public double A { get => a; }

        public override double Area()
        {
            return a * a;
        }

        public override string Type()
        {
            return "Square";
        }
    }
}
