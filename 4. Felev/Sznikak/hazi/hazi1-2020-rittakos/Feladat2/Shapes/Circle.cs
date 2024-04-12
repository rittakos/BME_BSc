using System;
using System.Collections.Generic;
using System.Text;

namespace Shapes
{
    class Circle : Shape
    {
        private double r;

        public Circle(int r, int x, int y) : base(x, y)
        {
            this.r = r;
        }

        
        public double R { get => r;}

        public override double Area()
        {
            return Math.PI * r * r;
        }

        public override string Type()
        {
            return "Circle";
        }
    }
}
