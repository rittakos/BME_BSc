package minesweeper;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTable;




public class ScoreBoard implements Serializable
{
	private static final long serialVersionUID = 1L;
	
	private ArrayList<Score> scoreBoard;
	private String filename;
	
	
	private BufferedWriter bw;
	private BufferedReader br;
	
	public ScoreBoard(String filename)
	{
		scoreBoard = new ArrayList<Score>();
		
		this.filename = filename;
		
		Read();	
	}
	
	private void Read()
	{
		try
		{
			br = new BufferedReader(new FileReader(new File(filename)));
			
			String line;
			while((line = br.readLine()) != null)
			{
				scoreBoard.add(new Score(line.split("\t")[0], Integer.parseInt(line.split("\t")[1])));
			}
			
			
			br.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
	}
	
	private void Write()
	{
		try
		{
			FileWriter f = new FileWriter(filename);
			bw = new BufferedWriter(f);
			
			
			
			for(Score score : scoreBoard)
			{
				bw.write(score.toString() + "\n");
				//System.out.print(score.GetName() + "\t" + score.GetTime() + "\n");
			}
			
			bw.close();
			f.close();
			
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
	}
	
	public void AddScore(Score score)
	{
		if(scoreBoard.size() < 10)
		{
			scoreBoard.add(score);
		}else
		{
			if(scoreBoard.get(9).GetTime() >= score.GetTime())
				scoreBoard.set(9, score);
		}
		Collections.sort(scoreBoard, new TimeComparator());
		

		Write();
	}
	
	public void DeleteScoreBoard()
	{
		for(int idx = 0; idx < scoreBoard.size(); ++idx)
			scoreBoard.remove(idx);
			
	}
	
	public ArrayList<Score> GetScoreBoard()
	{
		return scoreBoard;
	}
	
 	public String toString()
	{
		String result = "";
		
		for(Score score : scoreBoard)
		{
			result += (score.toString() + "\n");
		}
			
		return result;
	}
	
	public void OpenScoreBoard()
	{
		JFrame f = new JFrame();    
  
	    String[][] data = new String[scoreBoard.size()][3]; 
	    int idx = 0;
	    for(Score score : scoreBoard)
	    {
	    	data[idx][0] = String.valueOf(idx + 1);
	    	data[idx][1] = score.GetName();
	    	data[idx][2] = String.valueOf(score.GetTime());
	    	++idx;
	    }
	    
	    
	    String column[] = {"Place", "Name", "Time"};         
	    JTable jt = new JTable(data,column);    
	    jt.setBounds(30,40,200,300);          
	    JScrollPane sp = new JScrollPane(jt);    
	    f.add(sp);          
	    f.setSize(300,400);    
	    f.setVisible(true);    
	}

}
