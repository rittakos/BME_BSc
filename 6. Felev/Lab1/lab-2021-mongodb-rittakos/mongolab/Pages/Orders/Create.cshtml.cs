using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Orders
{
    public class CreateModel : PageModel
    {
        private readonly IRepository repository;

        public CreateModel(IRepository repository)
        {
            this.repository = repository;
        }

        public SelectList Products { get; set; }

        [BindProperty]
        public Order Order { get; set; }

        [BindProperty]
        [Required]
        public string ProductID { get; set; }

        [BindProperty]
        [Range(1, double.PositiveInfinity)]
        public int Amount { get; set; }

        public void OnGet()
        {
            var termekek = repository.ListProducts();
            Products = new SelectList(termekek, "ID", "Name");
        }

        public IActionResult OnPost()
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }

            var termek = repository.FindProduct(ProductID);
            repository.InsertOrder(Order, termek, Amount);

            return RedirectToPage("./Index");
        }
    }
}