package kaszino;

public class Robot extends Jatekos
{
	public String toString()
	{
		return "Robot "+id+": "+a.getKor()+". kör.";
	}
	
	public void lep()
	{
		System.out.println(this.toString());
	}
}
