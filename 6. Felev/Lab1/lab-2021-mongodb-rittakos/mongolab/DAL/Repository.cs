using System;
using System.Collections.Generic;
using System.Linq;
using MongoDB.Bson;
using MongoDB.Driver;
using mongolab.Models;

namespace mongolab.DAL
{
    public class Repository : IRepository
    {

        private readonly IMongoCollection<Entities.Product> productCollection;
        private readonly IMongoCollection<Entities.Category> categoryCollection;
        private readonly IMongoCollection<Entities.Order> orderCollection;
        private readonly IMongoCollection<Entities.Customer> customerCollection;

        public Repository(IMongoDatabase database)
        {
            this.productCollection = database.GetCollection<Entities.Product>("products");
            this.categoryCollection = database.GetCollection<Entities.Category>("categories");
            this.orderCollection = database.GetCollection<Entities.Order>("orders");
            this.customerCollection = database.GetCollection<Entities.Customer>("customers");
        }

        public IList<Product> ListProducts()
        {
            var dbProducts = productCollection.Find(_ => true).ToList();
            return dbProducts.Select(t => new Product
                                {
                                    ID = t.ID.ToString(),
                                    Name = t.Name,
                                    Price = t.Price,
                                    Stock = t.Stock
                                }).ToList();
        }

        public Product FindProduct(string id)
        {
            var dbProduct = productCollection.Find(t => t.ID == ObjectId.Parse(id)).SingleOrDefault();
            if (dbProduct == null)
                return null;
            return new Product{ ID = dbProduct.ID.ToString(),
                                Name = dbProduct.Name,
                                Price = dbProduct.Price,
                                Stock = dbProduct.Stock
                              };
        }

        public void InsertProduct(Product product)
        {
            var dbProduct = new Entities.Product
            {
                Name = product.Name,
                Price = product.Price,
                Stock = product.Stock,
                VAT = new Entities.VAT { Name = "General", Percentage = 20 },
                CategoryID = ObjectId.Parse("5d7e4370cffa8e1030fd2d99"),
            };

            productCollection.InsertOne(dbProduct);
        }

        public bool SellProduct(string id, int amount)
        {
            var result =    productCollection.UpdateOne(
                            filter: t => t.ID == ObjectId.Parse(id) && t.Stock >= amount,
                            update: Builders<Entities.Product>.Update.Inc(t => t.Stock, -amount),
                            options: new UpdateOptions { IsUpsert = false });

            return result.MatchedCount > 0;
        }

        public void DeleteProduct(string id)
        {
            productCollection.DeleteOne(t => t.ID == ObjectId.Parse(id));
        }

        public IList<Category> ListCategories()
        {
            var dbCategories = categoryCollection.Find(_ => true).ToList();

            var productCounts = productCollection
                    .Aggregate()
                    .Group(t => t.CategoryID, g => new { CategoryID = g.Key, NumberOfProducts = g.Count() })
                    .ToList();

            return dbCategories.Select(c =>
                        {
                            string parentCategoryName = null;
                            if (c.ParentCategoryID.HasValue)
                                parentCategoryName = dbCategories.Single(p => p.ID == c.ParentCategoryID.Value).Name;

                            var numProd = productCounts.SingleOrDefault(pc => pc.CategoryID == c.ID)?.NumberOfProducts ?? 0;
                            return new Category { Name = c.Name, ParentCategoryName = parentCategoryName, NumberOfProducts = numProd };
                        })
                        .ToList();
        }

        public IList<Order> ListOrders(string status = null)
        {
            List<Entities.Order> dbOrders;
            if (string.IsNullOrEmpty(status))
            {
                dbOrders = orderCollection.Find(_ => true).ToList();
            }
            else
            {
                dbOrders = orderCollection.Find(t => t.Status == status).ToList();
            }

            return dbOrders.Select(t => {
                    double? sum = 0;
                    foreach (var o in t.OrderItems)
                        sum += o.Amount * o.Price;
                    return new Order {  ID = t.ID.ToString(), Date = t.Date,
                                        Deadline = t.Deadline, Status = t.Status,
                                        PaymentMethod = t.PaymentMethod.Method,
                                        Total = sum
                                     };
                }).ToList();
        }

        public Order FindOrder(string id)
        {
            var dbOrder = orderCollection.Find(t => t.ID == ObjectId.Parse(id)).SingleOrDefault();
            if (dbOrder == null)
                return null;

            double? sum = 0;
            foreach (var o in dbOrder.OrderItems)
                sum += o.Amount * o.Price;

            return new Order
            {
                ID = dbOrder.ID.ToString(),
                Date = dbOrder.Date,
                Deadline = dbOrder.Deadline,
                Status = dbOrder.Status,
                PaymentMethod = dbOrder.PaymentMethod.Method,
                Total = sum
            };
        }

       
        public void InsertOrder(Order order, Product product, int amount)
        {
            Entities.OrderItem[] orderItems = { new Entities.OrderItem { ProductID = ObjectId.Parse(product.ID), Price = product.Price, Amount = amount, Status = order.Status } };

            var dbOrder = new Entities.Order
            {
                CustomerID = ObjectId.Parse("5d7e4370cffa8e1030fd2d92"),
                SiteID = ObjectId.Parse("5d7e4370cffa8e1030fd2d93"),
                Date = order.Date,
                Deadline = order.Deadline,
                Status = order.Status,
                PaymentMethod = new Entities.PaymentMethod {Method = order.PaymentMethod, Deadline = null},
                OrderItems = orderItems                    
            };

            orderCollection.InsertOne(dbOrder);
        }

        public bool UpdateOrder(Order order)
        {
            var updates = new List<UpdateDefinition<Entities.Order>>();

            updates.Add(Builders<Entities.Order>.Update.Set(x => x.Date, order.Date));
            updates.Add(Builders<Entities.Order>.Update.Set(x => x.Deadline, order.Deadline));
            updates.Add(Builders<Entities.Order>.Update.Set(x => x.Status, order.Status));
            updates.Add(Builders<Entities.Order>.Update.Set(x => x.PaymentMethod.Method, order.PaymentMethod));


            var result = orderCollection.UpdateOne(
                           filter: t => t.ID == ObjectId.Parse(order.ID),
                           update: Builders<Entities.Order>.Update.Combine(updates),
                           options: new UpdateOptions { IsUpsert = false });

            return result.MatchedCount > 0;
        }

        public void DeleteOrder(string id)
        {
            orderCollection.DeleteOne(t => t.ID == ObjectId.Parse(id));
        }

        public IList<Customer> ListCustomers()
        {
            var dbCustomers = customerCollection.Find(_ => true).ToList();

            var orderCounts = orderCollection
                                    .Aggregate()
                                    .Group(t => t.CustomerID, g => 
                                                new {CustomerID = g.Key, TotalOrders = g.Sum(y => y.OrderItems.Sum(z => z.Amount * z.Price))})
                                    .ToList();



            return dbCustomers.Select(c =>
            {
                var mainSite = c.Sites.ToList().Find(x => x.ID == c.MainSiteID);
                var totalOrders = orderCounts.SingleOrDefault(pc => pc.CustomerID == c.ID)?.TotalOrders;
                //var totalOrders = orderCounts.SingleOrDefault(pc => pc.CustomerID == c.ID)?.TotalOrders ?? 0;
                return new Customer { Name = c.Name, ZipCode = mainSite.ZipCode, City = mainSite.City, Street = mainSite.Street, TotalOrders = totalOrders };
            }).ToList();
        }

        public OrderGroups GroupOrders(int groupsCount)
        {
            throw new NotImplementedException();
        }
    }
}
