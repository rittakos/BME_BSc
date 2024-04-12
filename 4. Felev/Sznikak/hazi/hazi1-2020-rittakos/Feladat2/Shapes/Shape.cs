using System;
using System.Collections.Generic;
using System.Text;

namespace Shapes
{
    public abstract class Shape : IDrawable
    {
        private int x, y;

        public int X { get => x; }
        public int Y { get => y; }

        public Shape(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public abstract double Area();
        public abstract string Type();


        public override string ToString()
        {
            return Type()+ " (" + X + ";" + Y + ") " + Area();
        }
    }
}
