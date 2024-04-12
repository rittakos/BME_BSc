using System;
using System.ComponentModel.DataAnnotations;

namespace mongolab.Models
{
    public class Order
    {
        public string ID { get; set; }

        public DateTime? Date { get; set; }
        public DateTime? Deadline { get; set; }
        [Required]
        public string Status { get; set; }
        [Required]
        public string PaymentMethod { get; set; }
        public double? Total { get; set; }
    }
}
