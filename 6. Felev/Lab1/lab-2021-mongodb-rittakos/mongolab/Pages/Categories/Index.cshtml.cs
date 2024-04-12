using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;
using System.Collections.Generic;

namespace mongolab.Pages.Categories
{
    public class IndexModel : PageModel
    {
        private readonly IRepository repository;

        public IndexModel(IRepository repository)
        {
            this.repository = repository;
        }

        public IList<Category> Categories { get; set; }

        public void OnGet()
        {
            Categories = repository.ListCategories();
        }
    }
}