package sample.prog;

import sample.calc.*;
import sample.echo.Echo;

public class Program {
	public static void main(String[] args)
	{
		int x=5;
		int y=8;
		Calculator c=new Calculator();
		int sum=c.add(x,y);
		Echo e = new Echo();
		int sumEcho=e.number(sum);
		System.out.println("sumecho="+sumEcho);
	}
}
