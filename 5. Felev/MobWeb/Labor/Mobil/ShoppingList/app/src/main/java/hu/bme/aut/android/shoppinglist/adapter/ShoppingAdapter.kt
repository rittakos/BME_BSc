package hu.bme.aut.android.shoppinglist.adapter

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.annotation.DrawableRes
import androidx.recyclerview.widget.RecyclerView
import hu.bme.aut.android.shoppinglist.R
import hu.bme.aut.android.shoppinglist.data.Category
import hu.bme.aut.android.shoppinglist.data.Task


class ShoppingAdapter(private val listener: ShoppingItemClickListener) : RecyclerView.Adapter<ShoppingAdapter.ShoppingViewHolder>()
{

    private val items = mutableListOf<Task>()
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ShoppingViewHolder
    {
        val itemView: View = LayoutInflater.from(parent.context).inflate(R.layout.list_layout, parent, false)
        return ShoppingViewHolder(itemView)
    }

    /*@DrawableRes
    private fun getImageResource(category: Category) = when (category) {
        ShoppingItem.Category.BOOK -> R.drawable.open_book
        ShoppingItem.Category.ELECTRONIC -> R.drawable.lightning
        ShoppingItem.Category.FOOD -> R.drawable.groceries
    }*/

    override fun onBindViewHolder(holder: ShoppingViewHolder, position: Int) {
        val item = items[position]
        holder.nameTextView.text = item.name
        holder.descriptionTextView.text = item.description
        holder.categoryTextView.text = item.category.name
        holder.deadlineTextView.text = item.deadline
        holder.importantCheckBox.isChecked = item.important
        holder.doneCheckBox.isChecked = item.done
        holder.item = item
    }


    fun addItem(item: Task) {
        items.add(item)
        notifyItemInserted(items.size - 1)
    }

    fun update(tasks: List<Task>) {
        items.clear()
        items.addAll(tasks)
        notifyDataSetChanged()
    }

    fun deleteItem(item: Task)
    {
        notifyItemRemoved(items.indexOf(item));
        items.remove(item);
    }

    override fun getItemCount(): Int {
        return items.size
    }

    interface ShoppingItemClickListener {
        fun onItemChanged(item: Task)
        fun onItemDeleted(item: Task)
    }

    inner class ShoppingViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView){
        val nameTextView: TextView
        val descriptionTextView: TextView
        val categoryTextView: TextView
        val deadlineTextView: TextView
        val importantCheckBox: CheckBox
        val doneCheckBox: CheckBox
        val removeButton: ImageButton

        var item: Task? = null

        init {
            nameTextView = itemView.findViewById(R.id.NameTextView)
            descriptionTextView = itemView.findViewById(R.id.DescriptionTextView)
            categoryTextView = itemView.findViewById(R.id.CategoryTextView)
            deadlineTextView = itemView.findViewById(R.id.DeadlineTextView)
            importantCheckBox = itemView.findViewById(R.id.ImportantCheckBox)
            doneCheckBox = itemView.findViewById(R.id.DoneCheckBox)
            removeButton = itemView.findViewById(R.id.RemoveButton)
            importantCheckBox.setOnCheckedChangeListener(CompoundButton.OnCheckedChangeListener { buttonView, isChecked ->
                item?.let {
                    val newItem = it.copy(
                        important = isChecked
                    )
                    item = newItem
                    listener.onItemChanged(newItem)
                }
            })
            doneCheckBox.setOnCheckedChangeListener(CompoundButton.OnCheckedChangeListener { buttonView, isChecked ->
                item?.let {
                    val newItem = it.copy(
                        done = isChecked
                    )
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