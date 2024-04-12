using System;
using System.Collections.Generic;
using System.Text;

namespace Shapes
{
    interface IDrawable
    {
        double Area();
        string Type();

        string ToString();
    }
}
