package hu.bme.aut.android.simpledrawer.sqlite

import android.database.sqlite.SQLiteDatabase
import android.util.Log

object DbConstants {

    const val DATABASE_NAME = "simpledrawer.db"
    const val DATABASE_VERSION = 1

    object Points {
        const val DATABASE_TABLE = "points"

        enum class Columns {
            _id, coord_x, coord_y
        }

        private val DATABASE_CREATE ="""create table if not exists $DATABASE_TABLE (
            ${Columns._id.name} integer primary key autoincrement,
            ${Columns.coord_x.name} real not null,
            ${Columns.coord_y} real not null
            );"""

        const val DATABASE_DROP = "drop table if exists $DATABASE_TABLE;"

        fun onCreate(database: SQLiteDatabase) {
            database.execSQL(DATABASE_CREATE)
        }

        fun onUpgrade(database: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
            Log.w(
                DbConstants.Points::class.java.name,
                "Upgrading from version $oldVersion to $newVersion"
            )
            database.execSQL(DATABASE_DROP)
            onCreate(database)
        }
    }

    object Lines {
        const val DATABASE_TABLE = "lines"

        enum class Columns {
            _id, start_x, start_y, end_x, end_y
        }

        private val DATABASE_CREATE ="""create table if not exists $DATABASE_TABLE (
        ${Columns._id.name} integer primary key autoincrement,
        ${Columns.start_x} real not null,
        ${Columns.start_y} real not null,
        ${Columns.end_x} real not null,
        ${Columns.end_y} real not null

        );"""

        const val DATABASE_DROP = "drop table if exists $DATABASE_TABLE;"

        fun onCreate(database: SQLiteDatabase) {
            database.execSQL(DATABASE_CREATE)
        }

        fun onUpgrade(database: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
            Log.w(
                DbConstants.Lines::class.java.name,
                "Upgrading from version $oldVersion to $newVersion"
            )
            database.execSQL(DATABASE_DROP)
            onCreate(database)
        }
    }
}