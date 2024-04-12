package com.example.androidwallet

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.LayoutInflater
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.Toast
import com.google.android.material.snackbar.Snackbar
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.salary_row.view.*

class MainActivity : AppCompatActivity() {

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu);
        return true;
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId)
        {
            R.id.delete_all -> {
                list_of_rows.removeAllViews();
                true;
            }
            else -> super.onOptionsItemSelected(item);
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var summa = 0;

        save_button.setOnClickListener()
        {
            if(salary_name.text.isEmpty() || salary_amount.text.isEmpty())
            {
                Snackbar.make(it, R.string.warn_message, Snackbar.LENGTH_SHORT).show();
                //Toast.makeText(this, R.string.warn_message, Toast.LENGTH_LONG).show();
                return@setOnClickListener;
            }

            if(expense_or_income.isChecked)
            {
                summa -= salary_amount.text.toString().toInt();
            }else
            {
                summa += salary_amount.text.toString().toInt();
            }

            if(summa == 0)
            {
                sum_value.visibility = View.INVISIBLE;
            }else
            {
                sum_value.text = "Summa: " + summa.toString();
                sum_value.visibility = View.VISIBLE;
            }

            val rowItem = LayoutInflater.from(this).inflate(R.layout.salary_row, null);
            rowItem.salary_direction_icon.setImageResource(if(expense_or_income.isChecked){R.drawable.expense} else {R.drawable.income})
            rowItem.row_salary_name.text = salary_name.text.toString();
            rowItem.row_salary_amount.text = salary_amount.text.toString();
            list_of_rows.addView(rowItem);
        }
    }
}