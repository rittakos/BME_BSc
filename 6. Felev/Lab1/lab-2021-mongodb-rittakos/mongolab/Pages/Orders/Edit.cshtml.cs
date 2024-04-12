using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Orders
{
    public class EditModel : PageModel
    {
        private readonly IRepository repository;

        public EditModel(IRepository repository)
        {
            this.repository = repository;
        }

        [BindProperty]
        public Order Order { get; set; }

        public IActionResult OnGet(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            Order = repository.FindOrder(id);

            if (Order == null)
            {
                return NotFound();
            }
            return Page();
        }

        public IActionResult OnPost()
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }

            bool success = repository.UpdateOrder(Order);
            if (success)
                return RedirectToPage("./Index");
            else
                return NotFound();
        }
    }
}
