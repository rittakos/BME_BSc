package hu.bme.aut.todo.data

import androidx.room.*

@Dao
interface TaskDao
{
    @Query("SELECT * FROM task")
    fun getAll(): List<Task>

    @Insert
    fun insert(shoppingItems: Task): Long

    @Update
    fun update(shoppingItem: Task)

    @Delete
    fun deleteItem(shoppingItem: Task)
}
