package hu.bme.aut.android.shoppinglist.fragments


import android.app.Dialog
import android.content.Context
import android.opengl.ETC1.isValid
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.widget.ArrayAdapter
import android.widget.CheckBox
import android.widget.EditText
import android.widget.Spinner
import androidx.appcompat.app.AlertDialog
import androidx.fragment.app.DialogFragment
import hu.bme.aut.android.shoppinglist.R
import hu.bme.aut.android.shoppinglist.data.Category
import hu.bme.aut.android.shoppinglist.data.Task


import kotlinx.coroutines.NonCancellable.cancel

class NewTaskDialogFragment : DialogFragment()
{
    interface NewTaskDialogListener
    {
        fun onTaskCreated(newItem: Task)
    }

    private lateinit var listener: NewTaskDialogListener

    override fun onAttach(context: Context)
    {
        super.onAttach(context)
        listener = context as? NewTaskDialogListener?: throw RuntimeException("NewTaskDialogListener interface is not implemented!")
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
                resources.getStringArray(R.array.category_items)
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
                                    deadline = deadlineEditText.text.toString(),
                                    category = Category.getByOrdinal(categorySpinner.selectedItemPosition)
                                        ?: Category.TASK,
                                    important = importantCheckBox.isChecked,
                                    done = doneCheckBox.isChecked
    )

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog
    {
        return AlertDialog.Builder(requireContext()).setTitle(R.string.new_shopping_item).setView(getContentView())
            .setPositiveButton(R.string.ok) { dialogInterface, i ->
                if (isValid()) {
                    listener.onTaskCreated(getTask());
                }
            }.setNegativeButton(R.string.cancel, null).create()
    }

    companion object
    {
        const val TAG = "NewTaskDialogFragment"
    }
}