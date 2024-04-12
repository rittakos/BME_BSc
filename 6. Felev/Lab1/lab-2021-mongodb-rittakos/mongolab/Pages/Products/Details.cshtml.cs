using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Products
{
    public class DetailsModel : PageModel
    {
        private readonly IRepository repository;

        public DetailsModel(IRepository repository)
        {
            this.repository = repository;
        }

        public Product Product { get; set; }

        public IActionResult OnGet(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            Product = repository.FindProduct(id);

            if (Product == null)
            {
                return NotFound();
            }
            return Page();
        }
    }
}
