﻿using api.Controllers.Dto;
using api.DAL.EfDbContext;
using api.Model;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;

namespace api.DAL
{
    public class StatusesRepository : IStatusesRepository
    {
        private readonly TasksDbContext db;

        public StatusesRepository(TasksDbContext db)
        {
            this.db = db;
        }

        public bool ExistsWithName(string statusName)
        {
            return db.Statuses.Any(s => EF.Functions.Like(s.Name, statusName));
        }

        public Status FindById(int statusId)
        {
            var dbRecord = db.Statuses.FirstOrDefault(s => s.Id == statusId);
            if (dbRecord == null)
                return null;
            else
                return ToModel(dbRecord);
        }

        public Status Insert(CreateStatus value)
        {
            using (var tran = db.Database.BeginTransaction(System.Data.IsolationLevel.RepeatableRead))
            {
                if (db.Statuses.Any(s => EF.Functions.Like(s.Name, value.Name)))
                    throw new ArgumentException("name must be unique");

                var toInsert = new DbStatus() { Name = value.Name };
                db.Statuses.Add(toInsert);

                db.SaveChanges();
                tran.Commit();

                return new Model.Status(toInsert.Id, toInsert.Name);
            }
        }

        public IReadOnlyCollection<Status> List()
        {
            return db.Statuses.Select(ToModel).ToList();
        }

        private static Model.Status ToModel(DbStatus value)
        {
            return new Model.Status(value.Id, value.Name);
        }
    }
}
