using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace mongolab.DAL.Entities
{
    public class InvoiceIssuer
    {
        [BsonId]
        public ObjectId ID { get; set; }
        public string Name { get; set; }
        public string ZipCode { get; set; }
        public string City { get; set; }
        public string Street { get; set; }
        public string TaxIdentifier { get; set; }
        public string BankAccount { get; set; }
    }
}
