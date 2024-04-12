using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;
using System.Collections.Generic;

namespace mongolab.Pages.Products
{
    public class IndexModel : PageModel
    {
        private readonly IRepository repository;

        public IndexModel(IRepository repository)
        {
            this.repository = repository;
        }

        public IList<Product> Products { get; set; }

        public void OnGet()
        {
            Products = repository.ListProducts();
        }
    }
}
