using System;

namespace Shapes
{
    class Program
    {
        static void Main(string[] args)
        {
            Circle circle = new Circle(5, 10, 10);
            Console.WriteLine(circle);

            TextAre ta = new TextAre(10, 10, 4, 3);
            ta.SetText("fsdfsd");
            Console.WriteLine(ta);
            Console.WriteLine();

            ShapeContainer shapes = new ShapeContainer();

            shapes.Add(circle);
            shapes.Add(ta);
            shapes.Add(new Square(34, 54, 65));

            shapes.Write();

            shapes.Remove(circle);
            shapes.Write();

        }
    }
}
