package asztal;

public class Main 
{
	public static void main(String[] args)
	{
		Asztal asztal = new Asztal();
		Jatekos j1 = new Kezdo();
		Jatekos j2 = new Kezdo();
		Jatekos j3 = new Robot();
		
		asztal.ujJatek();
		
		asztal.addJatekos(j1);
		asztal.addJatekos(j2);
		asztal.addJatekos(j3);
		
		for(int idx = 0; idx < 3; ++idx)
		{
			asztal.kor();
		}
		
		Asztal asztal2 = new Asztal();
		asztal2.ujJatek();
		try
		{
			asztal2.kor();
		}catch(NincsJatekos  nincsJatekos)
		{
			
		}
		
		asztal = null;
		j1 = null;
		j2 = null;
		j3 = null;
		System.out.println("Jatek vege");
		System.gc();
	}
}
