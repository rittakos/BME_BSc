using System;
using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace mongolab.DAL.Entities
{
    public class Order
    {
        [BsonId]
        public ObjectId ID { get; set; }
        public ObjectId? CustomerID { get; set; }
        public ObjectId? SiteID { get; set; }

        public DateTime? Date { get; set; }
        public DateTime? Deadline { get; set; }
        public string Status { get; set; }
        public PaymentMethod PaymentMethod { get; set; }
        public OrderItem[] OrderItems { get; set; }
        public Invoice Invoice { get; set; }
    }
}
