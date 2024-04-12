public class Application {
	public static void main(String args[]) throws InterruptedException
	{
		Fifo storage = new Fifo();
		Thread threads[] = new Thread[7];
		for(int i=0;i<3;i++)
			threads[i] = new Thread(new Producer(storage, "producer", (int) Math.random()));
		for(int i=3;i<7;i++)
			threads[i] = new Thread(new Consumer(storage, "consumer", (int) Math.random()));
		
		for(int i=0;i<7;i++)
			threads[i].start();
	}
}