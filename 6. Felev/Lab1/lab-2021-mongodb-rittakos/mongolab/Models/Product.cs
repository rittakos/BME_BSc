using System.ComponentModel.DataAnnotations;

namespace mongolab.Models
{
    public class Product
    {
        public string ID { get; set; }

        [Required]
        public string Name { get; set; }
        [Required]
        public double? Price { get; set; }
        [Required]
        public int? Stock { get; set; }
    }
}
