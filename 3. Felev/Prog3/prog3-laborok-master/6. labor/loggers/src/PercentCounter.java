public class PercentCounter extends Observable {
	private int percent;
	public void run() {
		for(percent=0;percent<=100;percent++)
			if(percent%10==0)
				this.reportToObservers();
	}
	
	@Override
	public String toString()
	{
		return percent + "%";
	}
}
