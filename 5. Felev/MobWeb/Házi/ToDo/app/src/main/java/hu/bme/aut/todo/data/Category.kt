package hu.bme.aut.todo.data

import androidx.room.TypeConverter

enum class Category
{
    TASK;
    companion object
    {
        @JvmStatic
        @TypeConverter
        fun getByOrdinal(ordinal: Int): Category?
        {
            var ret: Category? = null
            for (cat in values()) {
                if (cat.ordinal == ordinal)
                {
                    ret = cat
                    break
                }
            }
            return ret
        }

        @JvmStatic
        @TypeConverter
        fun toInt(category: Category): Int
        {
            return category.ordinal
        }
    }
}