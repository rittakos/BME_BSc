package fajlrendzer;

import java.io.*;


public class FileSysten 
{
	File wd;
	
	public FileSysten(File file)
	{
		wd = file;
	}
	
	BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
	
	public void Read() throws IOException
	{
		String line = reader.readLine();
		String[] cmd = line.split(" ");
		
		if(cmd[0].equals("exit"))
		{
			exit(cmd);
		}else if(cmd[0].equals("ls"))
		{
			ls(cmd);
		}else if(cmd[0].equals("pwd"))
		{
			pwd(cmd);
		}else if(cmd[0].equals("cd"))
		{
			cd(cmd);
		}else if(cmd[0].equals("mkdir"))
		{
			mkdir(cmd);
		}else if(cmd[0].equals("cp"))
		{
			cp(cmd);
		}else if(cmd[0].equals("head"))
		{
			head(cmd);
		}
		
	}
	
	protected void head(String[] cmd) throws IOException 
	{
		int n = 10;
		File file;
		
		if(cmd[1].equals("-n" ))
		{
			n = Integer.parseInt(cmd[2]);
			file = new File(wd, cmd[3]);
		}
		else
			file = new File(wd, cmd[1]);
		
		BufferedReader in = new BufferedReader(new FileReader(file));
		
		for(int idx = 0; idx < n; ++idx)
			System.out.println(in.readLine());
		
		in.close();
	}
	
	protected void cp(String[] cmd) throws IOException 
	{   
    	FileInputStream in = new FileInputStream(cmd[1]);
      	FileOutputStream out = new FileOutputStream(cmd[2]);
  
      	int c;
      	
    	
		while ((c = in.read()) != 1) 
		{
		    out.write(c);
		}
		
		in.close();
        out.close();
	}
	
	protected void mkdir(String[] cmd) 
	{
		 File newFile = new File(cmd[1]);
		 try{
		        newFile.mkdir();
		    } 
		    catch(SecurityException se){
		        
		    }
	}
	
	protected void cd(String[] cmd) 
	{
		if(cmd[1] == "..")
			wd = wd.getParentFile();
		else
		{
			File f = new File(cmd[1]);
			wd = f;
		}
	}
	
	protected void exit(String[] cmd) 
	{
		System.exit(0);
	}
	
	protected void pwd(String[] cmd) throws IOException 
	{
		System.out.print(wd.getCanonicalPath());
	}
	
	protected void ls(String[] cmd) 
	{
		for(File file : wd.listFiles())  
		{
			System.out.print(file.getName());
			
			if(cmd.length > 1 && cmd[1].equals("-l"))
			{
				System.out.print("a " + file.length());
				if(file.isDirectory())
					System.out.print(" d");
				else if(file.isFile())
					System.out.print(" f");
			}
			System.out.println();
		}
		
		
	}
}

