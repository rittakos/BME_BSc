package fajlrendzer;

import java.io.File;
import java.io.IOException;

public class Main 
{
	public static void main(String[] args) throws IOException
	{
		FileSysten fileSystem = new FileSysten(new File(System.getProperty("user.dir")));
		try
		{
			while(true)
			{
				fileSystem.Read();
			}
		
		} 
		catch (IOException ex) 
		{
			
		}

	}
	
	
}
