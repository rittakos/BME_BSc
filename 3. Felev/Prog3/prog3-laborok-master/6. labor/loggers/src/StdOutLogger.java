public class StdOutLogger implements Observer {

	@Override
	public void report(Observable observable) {
		System.out.println(observable);
	}
}
