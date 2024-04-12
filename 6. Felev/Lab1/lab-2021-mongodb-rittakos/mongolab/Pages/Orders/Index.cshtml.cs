using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Orders
{
    public class IndexModel : PageModel
    {
        private readonly IRepository repository;

        public IndexModel(IRepository repository)
        {
            this.repository = repository;
        }

        public IList<Order> Orders { get; set; }

        [BindProperty(SupportsGet = true)]
        public string Status { get; set; }

        public void OnGet()
        {
            Orders = repository.ListOrders(Status);
        }
    }
}
