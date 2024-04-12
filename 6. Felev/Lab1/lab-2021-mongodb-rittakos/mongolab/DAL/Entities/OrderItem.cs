using MongoDB.Bson;

namespace mongolab.DAL.Entities
{
    public class OrderItem
    {
        public int? Amount { get; set; }
        public double? Price { get; set; }
        public ObjectId? ProductID { get; set; }
        public string Status { get; set; }
        public InvoiceItem InvoiceItem { get; set; }
    }
}
