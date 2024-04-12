using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Products
{
    public class DeleteModel : PageModel
    {
        private readonly IRepository repository;

        public DeleteModel(IRepository repository)
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

        public IActionResult OnPost(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            repository.DeleteProduct(id);

            return RedirectToPage("./Index");
        }
    }
}
