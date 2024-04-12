package asztal;

public class Kezdo extends Jatekos
{
	public String toString ()
	{
		return "Kezdo " + id;
	}
	
	public void lep()
	{
		System.out.println(toString());
		if(asztal.getKor() % 2 == 1)
			asztal.emel(1);
			
	}
}
