using api.DAL;
using api.Model;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;

namespace api.Controllers
{
    [Route("api/statuses/z8wk8d")] // REPLACE neptun WITH YOUR NEPTUN CODE SMALL CAPS - CSERELD LE A neptun-t a SAJAT NEPTUN KODODRA KISBETUKKEL
    [ApiController]
    public class StatusesController : ControllerBase
    {
        private readonly IStatusesRepository repository;

        // DO NOT CHANGE THE CONSTRUCTOR - NE VALTOZTSD MEG A KONSTRUKTORT
        public StatusesController(IStatusesRepository repository)
        {
            this.repository = repository;
        }

        [HttpGet]
        public IEnumerable<Status> List()
        {
            return repository.List();
        }

        [HttpHead("{statusName}")]
        [ProducesResponseType(StatusCodes.Status200OK)]
        [ProducesResponseType(StatusCodes.Status404NotFound)]
        public ActionResult ExistsWithName(string statusName)
        {
            var exists = repository.ExistsWithName(statusName);
            if (exists)
                return Ok();
            else
                return NotFound();
        }

        [HttpGet("{id}")]
        [ProducesResponseType(StatusCodes.Status200OK)]
        [ProducesResponseType(StatusCodes.Status404NotFound)]
        public ActionResult<Status> Get(int id)
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
        public ActionResult<Status> Create([FromBody] Dto.CreateStatus value)
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
    }
}
