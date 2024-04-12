package minesweeper;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class ScoreTest {

private Score score;
	
	@Before
	public void SetUp()
	{
		score = new Score("Bela", 33);
	}
	
	@Test
	public void TestScoreToString()
	{
		Assert.assertEquals(score.toString(), "Bela" + "\t" + "33");
	}
	
	@Test
	public void TestGetNameGetTime()
	{
		Assert.assertEquals(score.GetTime(), 33);
		Assert.assertEquals(score.GetName(), "Bela");
	}
}
