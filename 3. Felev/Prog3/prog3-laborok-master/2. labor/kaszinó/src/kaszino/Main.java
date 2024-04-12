package kaszino;

public class Main {
	public static void main(String args[])
	{
		Asztal a=new Asztal();
		a.ujJatek();
		a.addJatekos(new Robot());
		a.addJatekos(new Kezdo());
		a.addJatekos(new Kezdo());
		for(int i=0;i<3;i++)
			a.kor();
        a=null;
        System.gc();
		System.gc();
	}
	
}
