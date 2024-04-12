package hu.bme.aut.todo.data

import androidx.room.Database
import androidx.room.RoomDatabase
import androidx.room.TypeConverters

@Database(entities = [Task::class], version = 1)
@TypeConverters(value = [Category::class])
abstract class ToDoDatabase : RoomDatabase()
{
    abstract fun taskDao(): TaskDao
}