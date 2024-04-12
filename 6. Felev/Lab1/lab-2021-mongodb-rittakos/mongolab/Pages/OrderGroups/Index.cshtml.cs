using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using mongolab.DAL;
using mongolab.Models;

namespace mongolab.Pages.OrderGroups
{
    public class IndexModel : PageModel
    {
        private readonly IRepository repository;

        public IndexModel(IRepository repository)
        {
            this.repository = repository;
        }

        public IList<DateTime> Thresholds { get; set; }
        public Dictionary<DateTime, OrderGroup> Groups { get; set; }

        [BindProperty(SupportsGet = true)]
        [Range(1, double.PositiveInfinity)]
        public int GroupCount { get; set; } = 5;

        public void OnGet()
        {
            if (!ModelState.IsValid)
            {
                return;
            }

            var orderGroups = repository.GroupOrders(GroupCount);
            Thresholds = orderGroups.Thresholds;
            Groups = orderGroups.Groups.ToDictionary(cs => cs.Date);
        }
    }
}