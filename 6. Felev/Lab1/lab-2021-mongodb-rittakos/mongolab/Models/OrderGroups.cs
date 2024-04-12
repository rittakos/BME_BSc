using System;
using System.Collections.Generic;

namespace mongolab.Models
{
    public class OrderGroups
    {
        public IList<DateTime> Thresholds { get; set; }
        public IList<OrderGroup> Groups { get; set; }
    }
}
