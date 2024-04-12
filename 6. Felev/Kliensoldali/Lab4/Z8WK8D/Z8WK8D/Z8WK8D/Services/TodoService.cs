using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Z8WK8D.Models;

namespace Z8WK8D.Services
{
    public class TodoService
    {
        public static TodoService Instance { get; } = new TodoService();
        private Dictionary<int, TodoItem> items = new Dictionary<int, TodoItem>
        {
            {0, new TodoItem {Description = "Nagybevásrálást elintézni", Title = "Bevásárlás", Done = true}},
            {1, new TodoItem {Description = "Lemenni a tóhoz és horgászni egy jót", Title = "Horgászat", Done = false}},
        };
        protected TodoService() { }
        public void AddItem(string title, string description, bool done)
        {
            items.Add(items.Keys.Max() + 1, new TodoItem
            {
                Title = title,
                Description = description,
                Done = done
            }); 
        }
        public TodoItem GetItem(int id)
        {
            return items[id];
        }
        public List<TodoItem> GetAll()
        {
            return items.Values.ToList();
        }

    }
}
