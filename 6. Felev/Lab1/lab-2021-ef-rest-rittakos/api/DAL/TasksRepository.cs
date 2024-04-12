using api.Controllers.Dto;
using api.DAL.EfDbContext;
using api.Model;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;


namespace api.DAL
{
    public class TasksRepository : ITasksRepository
    {
        private readonly TasksDbContext db;

        public TasksRepository(TasksDbContext db)
        {
            this.db = db;
        }

        public Model.Task Delete(int taskId)
        {
            using (var tran = db.Database.BeginTransaction(System.Data.IsolationLevel.RepeatableRead))
            {
                var item = db.Tasks.FirstOrDefault(s => s.Id == taskId);

                if (item == null)
                    return null;

                db.Tasks.Remove(item);

                db.SaveChanges();
                tran.Commit();

                return ToModel(item);
            }
        }

        public Model.Task FindById(int taskId)
        {
            var dbRecord = db.Tasks.Include(t => t.Status).FirstOrDefault(s => s.Id == taskId);
            if (dbRecord == null)
                return null;
            else
                return ToModel(dbRecord);
        }

        public Model.Task Insert(CreateTask value)
        {
            using (var tran = db.Database.BeginTransaction(System.Data.IsolationLevel.RepeatableRead))
            {
                //if(db.Tasks.Any(s => EF.Functions.Like(s.Title, value.Title)))
                //    throw new ArgumentException("title must be unique");

                bool statusExists = false;
                foreach(var i in db.Statuses)
                {
                    if(i.Name == value.Status)
                    {
                        statusExists = true;
                        break;
                    }
                }

                if(!statusExists)
                {
                    db.Statuses.Add(new DbStatus() {Name = value.Status});
                }

                var toInsert = new DbTask() { Title = value.Title, Done = false, Status = new DbStatus() { Name = value.Status } };
                db.Tasks.Add(toInsert);

                db.SaveChanges();
                tran.Commit();

                return new Model.Task(toInsert.Id, toInsert.Title, toInsert.Done, toInsert.Status.Name);
            }
        }

        public IReadOnlyCollection<Model.Task> List()
        {
            return db.Tasks.Include(t => t.Status).Select(ToModel).ToList();
        }

        public Model.Task MarkDone(int taskId)
        {
            using (var tran = db.Database.BeginTransaction(System.Data.IsolationLevel.RepeatableRead))
            {
                var toEdit = db.Tasks.Include(t => t.Status).FirstOrDefault(s => s.Id == taskId);

                if (toEdit == null)
                    return null;

           
                toEdit.Done = true;
                

                db.SaveChanges();
                tran.Commit();

                return new Model.Task(toEdit.Id, toEdit.Title, toEdit.Done, toEdit.Status.Name);
            }
        }

        public Model.Task MoveToStatus(int taskId, string newStatusName)
        {
            using (var tran = db.Database.BeginTransaction(System.Data.IsolationLevel.RepeatableRead))
            { 
                bool statusExists = false;

                DbStatus status = new DbStatus() { Name = newStatusName };

                foreach (var i in db.Statuses)
                {
                    if (i.Name == status.Name)
                    {
                        statusExists = true;
                        break;
                    }
                }

                if (!statusExists)
                {
                    db.Statuses.Add(status);
                }

                var toEdit = db.Tasks.Include(t => t.Status).FirstOrDefault(s => s.Id == taskId);

                toEdit.Status = status;

                db.SaveChanges();
                tran.Commit();

                return ToModel(toEdit);
            }
        }

        private Model.Task ToModel(DbTask value)
        {
            return new Model.Task(value.Id, value.Title, value.Done, value.Status.Name);
        }
    }
}
