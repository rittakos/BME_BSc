using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace mongolab.DAL.Entities
{
    public class Category
    {
        [BsonId]
        public ObjectId ID { get; set; }
        public string Name { get; set; }
        public ObjectId? ParentCategoryID { get; set; }
    }
}
