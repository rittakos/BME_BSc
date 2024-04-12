import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class filter {
	public static void main(String args[]) throws FileNotFoundException, IOException
	{
		BufferedReader in;
		PrintWriter out;
		String line;
		String input = null;
		String output = null;
		String pattern = "kutya";
//		System.out.println(pattern);
		for (int i = 0; i < args.length; i++) 
		{
			if ((i+1 < args.length) && args[i].equals("-i")) 
			{
				input = args[++i];
			} 
			else if ((i+1 < args.length) && args[i].equals("-o")) 
			{
				output = args[++i];
			} 
			else if ((i+1 < args.length) && args[i].equals("-p")) 
			{
				pattern = args[++i];
			}
		}
		if(input!=null)
			in=new BufferedReader(new InputStreamReader(new FileInputStream(new File(input))));
		else
			in=new BufferedReader(new InputStreamReader(System.in));
		
		if(output!=null)
			out=new PrintWriter(new File(output));
		else
			out=new PrintWriter(System.out);
		out.flush();
		out.println("Hello");
		
		while(true)
		{
			line=in.readLine();
			if (line == null) break; // fajlvege
			if(line.matches(pattern))
				out.println(line);
			out.flush(); // puffer uritese
		}
		out.close();// kimenet lezarasa
		in.close(); // bemenet lezarasa
		
	}
} 