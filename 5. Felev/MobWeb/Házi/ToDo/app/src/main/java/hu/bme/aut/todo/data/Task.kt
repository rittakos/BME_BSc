package hu.bme.aut.todo.data

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey
import java.util.*

@Entity(tableName = "task")
data class Task(@ColumnInfo(name = "id") @PrimaryKey(autoGenerate = true) val id: Long?,
                @ColumnInfo(name = "name") val name: String,
                @ColumnInfo(name = "description") val description: String,
                @ColumnInfo(name = "category") val category: Category,
                @ColumnInfo(name = "deadline") val deadline: String,
                @ColumnInfo(name = "important") val important: Boolean,
                @ColumnInfo(name = "done") val done: Boolean)
{

}
