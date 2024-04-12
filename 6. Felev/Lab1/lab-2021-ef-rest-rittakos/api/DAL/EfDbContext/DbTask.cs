using System.ComponentModel.DataAnnotations.Schema;

namespace api.DAL.EfDbContext
{
    public class DbTask
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public bool Done { get; set; }

        public int StatusId { get; set; }
        [ForeignKey("StatusId")]
        public DbStatus Status { get; set; }
    }
}
