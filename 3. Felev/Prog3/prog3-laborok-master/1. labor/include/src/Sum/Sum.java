package Sum;

import sample.calc.Calculator;

public class Sum {
	public static void main(String args[])
	{
		int sum=0;
		for(int i=0;i<args.length; i++)
		{
			Calculator szg=new Calculator();
			sum=szg.add(sum,Integer.parseInt(args[i]));
		}
		System.out.println(sum);
	}
	
}
