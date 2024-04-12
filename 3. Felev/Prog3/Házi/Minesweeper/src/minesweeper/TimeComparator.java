package minesweeper;

import java.util.Comparator;

public class TimeComparator implements Comparator<Score>
{
	public int compare(Score a, Score b) 
	{ 
		if(a.GetTime() == b.GetTime())
			return 0;
		else if(a.GetTime() < b.GetTime())
			return -1;
		else 
			return 1;
	}  
}
