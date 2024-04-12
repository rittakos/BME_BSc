package kaszino;

public class Asztal{
	private Jatekos j[]=new Jatekos[10];
	private int length=0;
	private int tet=0;
	private int korok=1;
	
	public void ujJatek()
	{
		tet=0;korok=1;
	}
	
	public void addJatekos(Jatekos uj)
	{
		if(length<10)
		{
			uj.setAsztal(this);
			j[length++]=uj;
		}
	}
	
	public int getKor()
	{
		return korok;
	}
	
	public void emel(double d)
	{
		tet+=d;
	}
	
	public void kor() throws NincsJatekos
	{
		if(length==0)
			throw (new NincsJatekos("Senki nem ül az asztalnál."));

		for(int i=0;i<length;i++)
			j[i].lep();
		korok++;
		System.out.println(tet);
	}
}
