package asztal;

public class Asztal 
{
	private double tet;
	private int korok;
	private Jatekos[] jatekosok = new Jatekos[10];
	private int player = 0;
	
	public void ujJatek()
	{
		tet = 0;
		korok = 0;
	}
	
	public void addJatekos(Jatekos j)
	{
		++player;
		if(player > 10)
		{
			System.out.print("Nincs hely");
			return;
		}
		j.setAsztal(this);
		jatekosok[player - 1] = j;
	}
	
	public int getKor()
	{
		return korok;
	}
	
	public void emel(double d)
	{
		tet += d;
	}
	
	public void kor() throws NincsJatekos
	{
		if (player == 0)
			throw (new NincsJatekos("Nincsen jatekos"));
		
		for(int idx = 0; idx < player; ++idx)
			jatekosok[idx].lep();
		++korok;
		
		System.out.println(tet);
	}
}
