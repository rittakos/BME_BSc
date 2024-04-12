using System;

namespace mongolab.Models
{
    public class OrderGroup
    {
        public DateTime Date { get; set; }
        public long Pieces { get; set; }
        public double? Total { get; set; }
    }
}
