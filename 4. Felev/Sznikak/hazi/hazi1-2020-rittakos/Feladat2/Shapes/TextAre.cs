using System;
using System.Collections.Generic;
using System.Text;
using Controls;

namespace Shapes
{
    class TextAre : Textbox, IDrawable
    {
        public TextAre(int x, int y, int w, int h) : base(x, y, w, h){}

        public double Area()
        {
            return GetWidth() * GetHeight();
        }
        public string Type()
        {
            return "TextArea";
        }

        public override string ToString()
        {
            return Type() + " (" + GetX() + ";" + GetY() + ") " + Area() + " \"" + GetText() + "\"";
        }
    }
}
