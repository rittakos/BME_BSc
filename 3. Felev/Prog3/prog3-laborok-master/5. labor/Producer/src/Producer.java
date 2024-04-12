import static java.lang.Thread.sleep;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Producer implements Runnable{
	private String message;
	private Fifo storage;
	private int sleepTime;
	
	public Producer(Fifo f, String s, int n)
	{
		message = s;
		storage = f;
		sleepTime = n;
	}
	
	public void go() throws InterruptedException
	{
		int i=0;
		while(true)
		{
			storage.put(message + " " + i++);
			try {
				sleep(sleepTime);
			}
			catch (InterruptedException ex) {
				Logger.getLogger(Producer.class.getName()).log(Level.SEVERE, null, ex);
			}
		}
	}
	
	@Override
	public void run()
	{
		try {
			this.go();
		} catch (InterruptedException ex) {
			Logger.getLogger(Producer.class.getName()).log(Level.SEVERE, null, ex);
		}
	}
}
