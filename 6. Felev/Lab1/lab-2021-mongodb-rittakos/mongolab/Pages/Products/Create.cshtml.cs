using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Products
{
    public class CreateModel : PageModel
    {
        private readonly IRepository repository;

        public CreateModel(IRepository repository)
        {
            this.repository = repository;
        }

        public IActionResult OnGet()
        {
            return Page();
        }

        [BindProperty]
        public Product Product { get; set; }

        public IActionResult OnPost()
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }

            repository.InsertProduct(Product);

            return RedirectToPage("./Index");
        }
    }
}