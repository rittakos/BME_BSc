using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace Shapes
{
    class ShapeContainer
    {
        private List<IDrawable> shapes;
        public ShapeContainer()
        {
            shapes = new List<IDrawable>();
        }

        public void Write()
        {
            foreach (IDrawable i in shapes)
                Console.WriteLine(i);
        }

        public void Add(IDrawable i)
        {
            shapes.Add(i);
        }

        public void Remove(IDrawable i)
        {
            shapes.Remove(i);
        }
    }
}
