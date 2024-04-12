package hu.bme.aut.android.simpledrawer

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.view.SubMenu
import androidx.appcompat.app.AlertDialog
import hu.bme.aut.android.simpledrawer.sqlite.PersistentDataHelper
import hu.bme.aut.android.simpledrawer.view.DrawingView
import kotlinx.android.synthetic.main.activity_drawing.*

class DrawingActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_drawing)
        dataHelper = PersistentDataHelper(this)
        dataHelper.open()
        restorePersistedObjects()
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        val toolbarMenu: Menu = toolbar.menu
        menuInflater.inflate(R.menu.menu_toolbar, toolbarMenu)
        //clearButton.setOnClickListener {}
        for (i in 0 until toolbarMenu.size()) {
            val menuItem: MenuItem = toolbarMenu.getItem(i)
            menuItem.setOnMenuItemClickListener { item -> onOptionsItemSelected(item) }
            if (menuItem.hasSubMenu()) {
                val subMenu: SubMenu = menuItem.getSubMenu()
                for (j in 0 until subMenu.size()) {
                    subMenu.getItem(j)
                        .setOnMenuItemClickListener { item -> onOptionsItemSelected(item) }
                }
            }
        }
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.menu_style_line -> {
                canvas.currentDrawingStyle = DrawingView.DRAWINGSTYLE_LINE
                item.isChecked = true
                true
            }
            R.id.menu_style_point -> {
                canvas.currentDrawingStyle = DrawingView.DRAWINGSTYLE_POINT
                item.isChecked = true
                true
            }
            R.id.clearButton -> {
               canvas.clear();
                canvas.invalidate()
               true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }

    private lateinit var dataHelper: PersistentDataHelper


    override fun onResume() {
        super.onResume()
        dataHelper.open()
    }

    override fun onPause() {
        dataHelper.close()
        super.onPause()
    }

    private fun restorePersistedObjects() {
        canvas.restoreObjects(dataHelper.restorePoints(), dataHelper.restoreLines())
    }

    override fun onBackPressed() {
        AlertDialog.Builder(this)
            .setMessage(R.string.are_you_sure_want_to_exit)
            .setPositiveButton(R.string.ok) { dialogInterface, i -> onExit() }
            .setNegativeButton(R.string.cancel, null)
            .show()
    }

    private fun onExit() {
        canvas.points?.let { dataHelper.persistPoints(it) }
        canvas.lines?.let { dataHelper.persistLines(it) }
        dataHelper.close()
        finish()
    }
}