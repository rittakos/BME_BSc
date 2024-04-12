using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace mongolab.DAL.Entities
{
    public class Customer
    {
        [BsonId]
        public ObjectId ID { get; set; }

        public string Name { get; set; }
        public string BankAccount { get; set; }
        public string Login { get; set; }
        public string Password { get; set; }
        public string Email { get; set; }

        public ObjectId MainSiteID { get; set; }
        public CustomerSite[] Sites { get; set; }
    }
}
