package hu.bme.aut.android.shoppinglist.data

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.TypeConverter

@Entity(tableName = "shoppingitem")
data class Task(
    @ColumnInfo(name = "id") @PrimaryKey(autoGenerate = true) val id: Long?,
    @ColumnInfo(name = "name") val name: String,
    @ColumnInfo(name = "description") val description: String,
    @ColumnInfo(name = "category") val category: Category,
    @ColumnInfo(name = "deadline") val deadline: String,
    @ColumnInfo(name = "important") val important: Boolean,
    @ColumnInfo(name = "done") val done: Boolean
) {

}