package minesweeper;


public class Score
{
	private String name;
	private int time;
	
	public Score(String name, int time)
	{
		this.name = name;
		this.time = time;
	}
	
	public String GetName()
	{
		return name;
	}
	
	public int GetTime()
	{
		return time;
	}
	
	public String toString()
	{
		return name + "\t" + time;
	}

}
