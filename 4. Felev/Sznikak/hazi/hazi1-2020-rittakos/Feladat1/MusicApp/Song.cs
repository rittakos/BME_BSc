using System;
using System.Collections.Generic;
using System.Text;

namespace MusicApp
{
    class Song
    {
        private readonly string author_;
        private readonly string title_;


        public Song(string author, string title)
        {
            author_ = author;
            title_ = title;
        }

        public override string ToString()
        {
            return author_ + ": " + title_;
        }
    }
}
