using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using MongoDB.Bson.Serialization.Conventions;
using MongoDB.Driver;

namespace mongolab.DAL
{
    public static class MongoConnectionConfig
    {
        public static void AddMongoConnection(this IServiceCollection services)
        {
            services.AddSingleton<IMongoClient>(serviceProvider =>
            {
                var configuration = serviceProvider.GetRequiredService<IConfiguration>();

                // A SZERVER ELERESET MEGVALTOZTATHATOD - YOU CAN CHANGE THE SERVER ADDRESS IF YOU NEED TO
                return new MongoClient(@"mongodb://localhost:27017");
            });

            services.AddSingleton(serviceProvider =>
            {
                var client = serviceProvider.GetRequiredService<IMongoClient>();

                // AZ ADATBAZIS NEVET MEGVALTOZTATHATOD - YOU CAN CHANGE THE DB NAME IF YOU NEED TO
                return client.GetDatabase("datadriven");
            });

            var pack = new ConventionPack
            {
                new ElementNameConvention(),
            };
            ConventionRegistry.Register("MyConventions", pack, _ => true);
        }
    }
}
