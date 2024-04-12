package hu.bme.aut.todo

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.room.Room
import hu.bme.aut.todo.adapter.ToDoAdapter
import hu.bme.aut.todo.data.Task
import hu.bme.aut.todo.data.ToDoDatabase
import hu.bme.aut.todo.fragment.NewTaskDialogFragment
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.tasks_layout.*
import kotlin.concurrent.thread


class MainActivity : AppCompatActivity(), ToDoAdapter.ItemClickListener, NewTaskDialogFragment.NewTaskDialogListener
{
    private lateinit var recyclerView: RecyclerView
    private lateinit var adapter: ToDoAdapter
    private lateinit var database: ToDoDatabase

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        setSupportActionBar(toolbar);

        fab.setOnClickListener{NewTaskDialogFragment().show(supportFragmentManager, NewTaskDialogFragment.TAG)}

        database = Room.databaseBuilder(applicationContext, ToDoDatabase::class.java,"ToDo").build();

        //initRecyclerView();
    }

    override fun onTaskCreated(newItem: Task)
    {
        thread {
            val newId = database.taskDao().insert(newItem)
            val newTask = newItem.copy(id = newId)
            runOnUiThread {adapter.addItem(newTask)}
        }
    }

    private fun initRecyclerView()
    {
        recyclerView = MainRecyclerView
        adapter = ToDoAdapter(this)
        loadItemsInBackground()
        recyclerView.layoutManager = LinearLayoutManager(this)
        recyclerView.adapter = adapter
    }

    override fun onItemChanged(item: Task)
    {
        thread {
            database.taskDao().update(item)
            Log.d("MainActivity", "Task update was successful")
        }
    }

    override fun onItemDeleted(item: Task)
    {
        thread {
            database.taskDao().deleteItem(item);
        }
    }

    private fun loadItemsInBackground()
    {
        thread {
            val items = database.taskDao().getAll()
            runOnUiThread { adapter.update(items)}
        }
    }

    /*override fun onCreateOptionsMenu(menu: Menu): Boolean
    {
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean
    {
        return when (item.itemId) {
            R.id.action_settings -> true
            else -> super.onOptionsItemSelected(item)
        }
    }*/
}