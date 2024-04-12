package kaszino;

public class Kezdo extends Jatekos{

	public String toString()
	{
		return "Kezdo "+id+": "+a.getKor()+". kör.";
	}
	
	public void lep()
	{
		System.out.println(this.toString());
		if(a.getKor()%2==0)
			a.emel(50);
	}
}
