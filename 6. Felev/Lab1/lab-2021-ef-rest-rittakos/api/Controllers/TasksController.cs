using api.DAL;
using api.Model;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;

namespace api.Controllers
{
    [Route("api/tasks/z8wk8d")] // REPLACE neptun WITH YOUR NEPTUN CODE SMALL CAPS - CSERELD LE A neptun-t a SAJAT NEPTUN KODODRA KISBETUKKEL
    [ApiController]
    public class TasksController : ControllerBase
    {
        private readonly ITasksRepository repository;
        public TasksController(ITasksRepository repository)
        {
            this.repository = repository;
        }

        [HttpGet]
        public IEnumerable<Task> List()
        {
            return repository.List();
        }

        [HttpGet("{id}")]
        [ProducesResponseType(StatusCodes.Status200OK)]
        [ProducesResponseType(StatusCodes.Status404NotFound)]
        public ActionResult<Task> Get(int id)
        {
            var value = repository.FindById(id);
            if (value == null)
                return NotFound();
            else
                return Ok(value);
        }

        [HttpPost]
        [ProducesResponseType(StatusCodes.Status201Created)]
        [ProducesResponseType(StatusCodes.Status400BadRequest)]
        public ActionResult<Task> Create([FromBody] Dto.CreateTask value)
        {
            try
            {
                var created = repository.Insert(value);
                return CreatedAtAction(nameof(Get), new { id = created.Id }, created);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(new { error = ex.Message });
            }
        }

        [HttpDelete("{id}")]
        [ProducesResponseType(StatusCodes.Status204NoContent)]
        [ProducesResponseType(StatusCodes.Status404NotFound)]
        public ActionResult<Task> Delete(int id)
        {
            var value = repository.FindById(id);

            if (value == null)
                return NotFound();
            else
            {
                repository.Delete(id);
                return NoContent();
            }
        }

        [HttpPatch("{id}/done")]
        [ProducesResponseType(StatusCodes.Status200OK)]
        [ProducesResponseType(StatusCodes.Status404NotFound)]
        public ActionResult<Task> MarkDone(int id)
        {
            var value = repository.FindById(id);

            if (value == null)
                return NotFound();
            else
            {
                return Ok(repository.MarkDone(id));
            }
        }


        [HttpPatch("{id}/move")]
        [ProducesResponseType(StatusCodes.Status200OK)]
        [ProducesResponseType(StatusCodes.Status404NotFound)]
        public ActionResult<Task> ChangeStatus(int id, [FromQuery] string newStatusName)
        {
            var value = repository.FindById(id);

            if (value == null)
                return Ok();
            else
            {
                return Ok(repository.MoveToStatus(id, newStatusName));
            }
        }
    }
}
