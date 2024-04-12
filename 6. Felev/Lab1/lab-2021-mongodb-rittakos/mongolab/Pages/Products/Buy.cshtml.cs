using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Products
{
    public class BuyModel : PageModel
    {
        private readonly IRepository repository;

        public BuyModel(IRepository repository)
        {
            this.repository = repository;
        }

        public Product Product { get; set; }

        [BindProperty]
        [Range(1, double.PositiveInfinity)]
        public int Amount { get; set; }

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

        public IActionResult OnPost(string id)
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }

            var success = repository.SellProduct(id, Amount);

            if (success)
            {
                return RedirectToPage("./Index");
            }
            else
            {
                Product = repository.FindProduct(id);
                ModelState.AddModelError(nameof(Amount), "Not enough product in stock!");
                return Page();
            }
        }
    }
}
