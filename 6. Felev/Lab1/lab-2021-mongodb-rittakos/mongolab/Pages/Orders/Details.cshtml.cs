using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.Orders
{
    public class DetailsModel : PageModel
    {
        private readonly IRepository repository;

        public DetailsModel(IRepository repository)
        {
            this.repository = repository;
        }

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
    }
}
