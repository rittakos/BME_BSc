package hu.bme.aut.android.shoppinglist.data

import androidx.room.Database
import androidx.room.RoomDatabase
import androidx.room.TypeConverters

@Database(entities = [Task::class], version = 1)
@TypeConverters(value = [Category::class])
abstract class ShoppingListDatabase : RoomDatabase() {
    abstract fun shoppingItemDao(): ShoppingItemDao
}