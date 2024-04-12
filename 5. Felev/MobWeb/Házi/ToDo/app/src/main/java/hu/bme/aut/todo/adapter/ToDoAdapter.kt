package hu.bme.aut.todo.adapter

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.annotation.DrawableRes
import androidx.recyclerview.widget.RecyclerView
import hu.bme.aut.todo.R
import hu.bme.aut.todo.data.Category
import hu.bme.aut.todo.data.Task
import java.util.*

class ToDoAdapter(private val listener: ItemClickListener) : RecyclerView.Adapter<ToDoAdapter.ToDoViewHolder>()
{
    private val items = mutableListOf<Task>()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ToDoViewHolder
    {
        val itemView: View = LayoutInflater.from(parent.context).inflate(R.layout.tasks_layout, parent, false);
        return ToDoViewHolder(itemView);
    }

    /*@DrawableRes
    private fun getImageResource(category: Category) = when (category)
    {
        ShoppingItem.Category.BOOK -> R.drawable.open_book
        ShoppingItem.Category.ELECTRONIC -> R.drawable.lightning
        ShoppingItem.Category.FOOD -> R.drawable.groceries
    }*/

    override fun onBindViewHolder(holder: ToDoViewHolder, position: Int)
    {
        val item = items[position]
        holder.nameTextView.text = item.name
        holder.descriptionTextView.text = item.description
        holder.categoryTextView.text = item.category.name
        holder.deadlineDate = item.deadline
        holder.importantCheckBox.isChecked = item.important
        holder.doneCheckBox.isChecked = item.done
        holder.importantCheckBox.isChecked = item.important

        holder.item = item
    }


    fun addItem(item: Task)
    {
        items.add(item)
        notifyItemInserted(items.size - 1)
    }

    fun update(tasks: List<Task>)
    {
        items.clear()
        items.addAll(tasks)
        notifyDataSetChanged()
    }

    fun deleteItem(item: Task)
    {
        notifyItemRemoved(items.indexOf(item));
        items.remove(item);
    }

    override fun getItemCount(): Int
    {
        return items.size
    }

    interface ItemClickListener
    {
        fun onItemChanged(item: Task)
        fun onItemDeleted(item: Task)
    }

    inner class ToDoViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView)
    {
        val nameTextView: TextView
        val descriptionTextView: TextView
        val categoryTextView: TextView
        var deadlineDate: String
        val doneCheckBox: CheckBox
        val importantCheckBox: CheckBox
        val removeButton: ImageButton

        var item: Task? = null

        init
        {
            nameTextView = itemView.findViewById(R.id.NameTextView)
            descriptionTextView = itemView.findViewById(R.id.DescriptionTextView)
            categoryTextView = itemView.findViewById(R.id.CategoryTextView)
            deadlineDate = itemView.findViewById(R.id.DeadlineTextView)
            removeButton = itemView.findViewById(R.id.RemoveButton)
            doneCheckBox = itemView.findViewById(R.id.DoneCheckBox)
            doneCheckBox.setOnCheckedChangeListener(CompoundButton.OnCheckedChangeListener { buttonView, isChecked ->
                item?.let {
                    val newItem = it.copy(done = isChecked)
                    item = newItem
                    listener.onItemChanged(newItem)
                }
            })
            importantCheckBox = itemView.findViewById(R.id.ImportantCheckBox)
            importantCheckBox.setOnCheckedChangeListener(CompoundButton.OnCheckedChangeListener { buttonView, isChecked ->
                item?.let {
                    val newItem = it.copy(important = isChecked)
                    item = newItem
                    listener.onItemChanged(newItem)
                }
            })
            removeButton.setOnClickListener{
                item?.let { it1 -> listener.onItemDeleted(it1) };
                item?.let { it1 -> deleteItem(it1) };

            }
        }
    }
}
