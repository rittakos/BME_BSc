
public class EmptyQueueException extends ArrayIndexOutOfBoundsException{
	public EmptyQueueException()
	{
		super("Üres a sor");
	}
	
	public EmptyQueueException(String err)
	{
		super(err);
	}
	
	public EmptyQueueException(int i)
	{
		super(i);
	}
}
