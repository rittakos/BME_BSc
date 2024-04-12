package hu.bme.aut.android.shoppinglist.data

import androidx.room.*

@Dao
interface ShoppingItemDao {
    @Query("SELECT * FROM shoppingitem")
    fun getAll(): List<Task>

    @Insert
    fun insert(shoppingItems: Task): Long

    @Update
    fun update(shoppingItem: Task)

    @Delete
    fun deleteItem(shoppingItem: Task)
}