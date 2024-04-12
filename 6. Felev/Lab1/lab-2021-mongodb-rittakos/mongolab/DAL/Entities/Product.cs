using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace mongolab.DAL.Entities
{
    [BsonIgnoreExtraElements]
    public class Product
    {
        [BsonId]
        public ObjectId ID { get; set; }
        public ObjectId? CategoryID { get; set; }

        public string Name { get; set; }
        public double? Price { get; set; }
        public int? Stock { get; set; }
        public VAT VAT { get; set; }
    }
}
