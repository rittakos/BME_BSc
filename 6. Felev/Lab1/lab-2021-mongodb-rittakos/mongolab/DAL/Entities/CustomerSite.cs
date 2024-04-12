using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace mongolab.DAL.Entities
{
    public class CustomerSite
    {
        [BsonId]
        public ObjectId ID { get; set; }
        public string ZipCode { get; set; }
        public string City { get; set; }
        public string Street { get; set; }
        public string Tel { get; set; }
        public string Fax { get; set; }
    }
}
