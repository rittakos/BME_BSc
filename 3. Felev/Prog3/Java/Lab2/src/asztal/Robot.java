package asztal;

public class Robot extends Jatekos
{
	public String toString ()
	{
		return "Robot " + id;
	}
	
	public void lep()
	{
		System.out.println(toString());
	}
}
