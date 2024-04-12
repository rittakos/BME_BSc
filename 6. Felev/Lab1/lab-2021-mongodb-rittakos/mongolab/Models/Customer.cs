namespace mongolab.Models
{
    public class Customer
    {
        public string Name { get; set; }
        public string ZipCode { get; set; }
        public string City { get; set; }
        public string Street { get; set; }
        public double? TotalOrders { get; set; }
    }
}
