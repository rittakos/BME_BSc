/*
In computer science, a priority queue is an abstract data type which is 
like a regular queue or stack data structure, but where additionally each element 
has a "priority" associated with it. In a priority queue, an element with high priority 
is served before an element with low priority. If two elements have the same priority, 
they are served according to their order in the queue.
https://en.wikipedia.org/wiki/Priority_queue
*/


import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class PQueue <T extends Comparable> implements Iterable<T>{
	private ArrayList<T> f = null;

	public PQueue() {
		f = new ArrayList<>();
	}
	
	int size()
	{
		return f.size();
	}
		
	void push (T t)
	{
		f.add(t);
	}
	
	T top()
	{
		if(size()<1)
			throw new EmptyQueueException("Nincs elem a listában");
		return (T) Collections.max(f);
	}
	
	T pop()
	{
		T top = this.top();
		f.remove(top);
		return top;
	}
	
	void clear()
	{
		f.clear();
	}

	public Iterator<T> iterator() {
		Collections.sort(f, new ReverseComparator<T>());
		return f.iterator();
	}
}
