using Microsoft.EntityFrameworkCore;

namespace api.DAL.EfDbContext
{
    public class TasksDbContext : DbContext
    {
        public DbSet<DbStatus> Statuses { get; set; }

        public DbSet<DbTask> Tasks { get; set; }

        // DO NOT CHANGE THE CONSTRUCTOR - NE VALTOZTASD MEG A KONSTRUKTORT
        public TasksDbContext(DbContextOptions options)
            : base(options)
        {
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<DbStatus>().ToTable("statuses");

            modelBuilder.Entity<DbStatus>().HasKey(s => s.Id);

            modelBuilder.Entity<DbStatus>().Property(s => s.Name).HasMaxLength(50)
                .IsRequired(required: true).IsUnicode(unicode: true);

            modelBuilder.Entity<DbStatus>().HasData(new[]
                                        {
                                            new DbStatus() { Id = 1, Name = "new" },
                                            new DbStatus() { Id = 2, Name = "in progress" },
                                        });

            modelBuilder.Entity<DbTask>().ToTable("tasks");

            modelBuilder.Entity<DbTask>().HasKey(s => s.Id);

            modelBuilder.Entity<DbTask>().Property(s => s.Title).HasMaxLength(50)
                .IsRequired(required: true).IsUnicode(unicode: true);

            modelBuilder.Entity<DbTask>().HasData(new[]
                                        {
                                            new DbTask() { Id = 1, Title = "aaa", Done = false, StatusId = 1},
                                            new DbTask() { Id = 2, Title = "bbb", Done = false, StatusId = 1}
                                        });
        }
    }
}
