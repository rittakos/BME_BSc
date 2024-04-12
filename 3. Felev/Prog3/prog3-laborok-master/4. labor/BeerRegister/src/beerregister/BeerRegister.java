package beerregister;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class BeerRegister {
	public static void main(String[] args) throws IOException, ClassNotFoundException 
	{
		ArrayList<Beer> storage=new ArrayList<>();
		BufferedReader in=new BufferedReader(new InputStreamReader(System.in));
		while(true)
		{
			String cmd[]=in.readLine().split(" ");
			switch(cmd[0])
			{
				case "add":
					storage.add(new Beer(cmd[1], cmd[2], Double.parseDouble(cmd[3])));
					break;
				case "list":
					if (cmd.length>1)
					{
						Comparator<Beer> cmp=null;
						switch(cmd[1])
						{
							case "name":
								cmp=new NameComparator();
								break;
							case "style":
								cmp=new StyleComparator();
								break;
							case "strength":
								cmp=new StrengthComparator();
								break;
							default:
								break;
						}
						Collections.sort(storage, cmp);
					}
					for(Beer element: storage)
						System.out.println(element);
					break;
				case "save":
					ObjectOutputStream os=new ObjectOutputStream(new FileOutputStream(cmd[1]));
					os.writeObject(storage);
					break;
				case "load":
					ObjectInputStream is=new ObjectInputStream(new FileInputStream(cmd[1]));
					storage=(ArrayList<Beer>)is.readObject();
					break;
				case "delete":
					try
					{
						storage.remove(Collections.binarySearch(storage, new Beer(cmd[1], null, 0), new NameComparator()));
					}
					catch (ArrayIndexOutOfBoundsException err)
					{
						System.err.println("szar");
					}
					break;
				default:
					System.exit(0);
					break;
			}
		}
	}
	
}
