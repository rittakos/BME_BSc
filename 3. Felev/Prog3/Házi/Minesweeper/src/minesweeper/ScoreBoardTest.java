package minesweeper;

import org.junit.Before;
import org.junit.Test;
import org.junit.Assert;

public class ScoreBoardTest 
{

	ScoreBoard sb;

	@Before
	public void SetUp()
	{
		sb = new ScoreBoard("test.txt");
		sb.DeleteScoreBoard();
	}
	
	@Test
	public void TestAddScore() 
	{
		sb.AddScore(new Score("Alfonz", 10));
		Assert.assertEquals("Alfonz", sb.GetScoreBoard().get(0).GetName());
		Assert.assertEquals(10, sb.GetScoreBoard().get(0).GetTime());
		sb.DeleteScoreBoard();
	}
	
	@Test
	public void TestAddScoreSort() 
	{
		sb.AddScore(new Score("Alfonz", 10));
		Assert.assertEquals("Alfonz", sb.GetScoreBoard().get(0).GetName());
		Assert.assertEquals(10, sb.GetScoreBoard().get(0).GetTime());
		sb.AddScore(new Score("Sanyi", 0));
		Assert.assertEquals("Sanyi", sb.GetScoreBoard().get(0).GetName());
		sb.DeleteScoreBoard();
	}
}
