using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Customers
{
    public class IndexModel : PageModel
    {
        private readonly IRepository repository;

        public IndexModel(IRepository repository)
        {
            this.repository = repository;
        }

        public IList<Customer> Customers { get; set; }

        public void OnGet()
        {
            Customers = repository.ListCustomers();
        }
    }
}