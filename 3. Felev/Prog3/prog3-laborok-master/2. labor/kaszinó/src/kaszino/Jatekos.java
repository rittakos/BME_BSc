package kaszino;

abstract public class Jatekos {
	protected Asztal a;
	protected int id;
	protected static int sum=0;
	
	abstract public void lep();
	public Jatekos()
	{
		id=sum++;
	}
	public void setAsztal(Asztal asztal)
	{
		a=asztal;
	}
        
    public void finalize() throws Throwable
    {
		System.out.println(id + this.toString());
		super.finalize();
	
    }
}
