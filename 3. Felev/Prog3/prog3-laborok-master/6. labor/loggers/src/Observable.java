import java.util.ArrayList;
import java.util.List;

public class Observable {
	private List<Observer> observers = new ArrayList<Observer>();
	public void register(Observer observer) {
		observers.add(observer);
	}
	
	public void unregister(Observer observer) {
		observers.remove(observer);
	}
	
	public void reportToObservers() {
		for(Observer x: observers)
			x.report(this);
	}
}
