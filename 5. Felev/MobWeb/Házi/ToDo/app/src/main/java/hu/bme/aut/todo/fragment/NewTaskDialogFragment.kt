package hu.bme.aut.todo.fragment

import android.app.DatePickerDialog
import android.app.Dialog
import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.widget.*
import androidx.appcompat.app.AlertDialog
import androidx.fragment.app.DialogFragment
import hu.bme.aut.todo.R
import hu.bme.aut.todo.data.Category
import hu.bme.aut.todo.data.Task
import java.util.*


class NewTaskDialogFragment : DialogFragment()
{
    interface NewTaskDialogListener
    {
        fun onTaskCreated(newItem: Task)
    }

    private lateinit var listener: NewTaskDialogListener

    override fun onAttach(context: Context)
    {
        super.onAttach(context);
        listener = context as? NewTaskDialogListener?: throw RuntimeException("Not implemented NewTaskDialogListener interface");
    }

    private lateinit var nameEditText: EditText
    private lateinit var descriptionEditText: EditText
    private lateinit var deadlineEditText: EditText
    private lateinit var categorySpinner: Spinner
    private lateinit var importantCheckBox: CheckBox
    private lateinit var doneCheckBox: CheckBox

    private fun getContentView(): View
    {
        val contentView = LayoutInflater.from(context).inflate(R.layout.new_task_layout, null)
        nameEditText = contentView.findViewById(R.id.NameEditText)
        descriptionEditText = contentView.findViewById(R.id.DescriptionEditText)
        deadlineEditText = contentView.findViewById(R.id.DeadlineEditText)
        categorySpinner = contentView.findViewById(R.id.CategorySpinner)
        categorySpinner.setAdapter(
            ArrayAdapter(
                requireContext(),
                android.R.layout.simple_spinner_dropdown_item,
                resources.getStringArray(R.array.category)
            )
        )
        importantCheckBox = contentView.findViewById(R.id.ImportantCheckBox)
        doneCheckBox = contentView.findViewById(R.id.DoneCheckBox)
        return contentView
    }

    private fun isValid() = nameEditText.text.isNotEmpty()

    private fun getTask() = Task(
                                    id = null,
                                    name = nameEditText.text.toString(),
                                    description = descriptionEditText.text.toString(),
                                    deadline  = deadlineEditText.text.toString(), //TODO(datum)
                                    category = Category.getByOrdinal(categorySpinner.selectedItemPosition) ?: Category.TASK,
                                    important = importantCheckBox.isChecked,
                                    done = doneCheckBox.isChecked
                                )

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog
    {
        return AlertDialog.Builder(requireContext())
            .setTitle("New Task")
            .setView(getContentView())
            .setPositiveButton("OK") { dialogInterface, i ->
                if(isValid())
                {
                    listener.onTaskCreated(getTask())
                }
            }
            .setNegativeButton("Cancel", null)
            .create()
    }

    companion object {
        const val TAG = "NewTaskDialogFragment"
    }

}
