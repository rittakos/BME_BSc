namespace mongolab.Models
{
    public class Category
    {
        public string Name { get; set; }
        public string ParentCategoryName { get; set; }
        public int NumberOfProducts { get; set; }
    }
}
