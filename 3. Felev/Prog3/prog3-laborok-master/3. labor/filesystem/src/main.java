import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class main
{
	public static void main(String args[])
	{
		Filesystem fs=new Filesystem(new File(System.getProperty("user.dir")));
		try 
		{
			while(true)
				fs.runcmd();
		} 
		catch (IOException ex) 
		{
			Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
		}
		
	}
}
