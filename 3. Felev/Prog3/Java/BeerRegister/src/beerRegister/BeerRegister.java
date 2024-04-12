package beerRegister;

import java.io.*;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class BeerRegister 
{
	public static void main (String[] args) throws IOException, ClassNotFoundException
	{
		ArrayList<Beer> beers = new ArrayList<Beer>();
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		while(true)
		{
			String cmd[] = in.readLine().split(" ");
			if(cmd[0].compareTo("add") == 0)
			{
				beers.add(new Beer(cmd[1], cmd[2], Double.parseDouble(cmd[3])));
			}else if(cmd[0].compareTo("list") == 0)
			{
				Comparator<Beer> cmp = null;
				
				if(cmd[1].compareTo("name") == 0)
				{
					cmp = new NameComparator();
				}else if(cmd[1].compareTo("style") == 0)
				{
					cmp = new StyleComparator();
				}else if(cmd[1].compareTo("strength") == 0)
				{
					cmp = new StrengthComparator();
				}
				Collections.sort(beers, cmp);
				
				for(Beer element: beers)
					System.out.println(element);

			}else if(cmd[0].compareTo("load") == 0)
			{
				ObjectInputStream is = new ObjectInputStream(new FileInputStream(cmd[1]));
				beers = (ArrayList<Beer>)is.readObject();
				is.close();
			}else if(cmd[0].compareTo("save") == 0)
			{
				ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream(cmd[1]));
				os.writeObject(beers);
				os.close();
			}else if(cmd[0].compareTo("delete") == 0)
			{
				try
				{
					beers.remove(Collections.binarySearch(beers, new Beer(cmd[1], null, 0), new NameComparator()));
				}
				catch (ArrayIndexOutOfBoundsException err)
				{
					System.err.println("Nem mukodik");
				}

			}
		}
	}
}
