package asztal;

 abstract public class Jatekos 
{
	protected Asztal asztal;
	static int id;
	
	
	public Jatekos()
	{
		++id;
	}
	
	abstract public void lep();
	
	public void setAsztal(Asztal a)
	{
		asztal = a;
	}
	
	
	public String toString()
	{
		return "Jatekos" + id;
	}
	
	public void finalize()
	{
		System.out.print(id + toString());
	}
}
