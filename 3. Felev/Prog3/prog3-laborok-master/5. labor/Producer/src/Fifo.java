import java.util.ArrayList;

public class Fifo{
	protected ArrayList<String> s;
	{
		s = new ArrayList<>(10); //csak azért, hogy használjak már inicializáló blokkot is
	}
	public synchronized void put(String e) throws InterruptedException
	{
		System.out.println("put: " + Thread.currentThread());
		while(s.size()>=10)
			this.wait();
		s.add(e);
		this.notify();
		System.out.println("produced " + e + " " +
							System.currentTimeMillis() % 10000);
	}
	
	public synchronized String get() throws InterruptedException
	{
		System.out.println("get: " + Thread.currentThread());
		while(s.size()<=0)
			this.wait();
		String ret=s.get(0);
		s.remove(ret);
		this.notify();
		return ret;
	}
}
