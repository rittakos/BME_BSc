package minesweeper;

import org.junit.Before;
import org.junit.Test;

import org.junit.Assert;

public class TimeComparatorTest 
{
	TimeComparator tc;
	Score s1;
	Score s2;
	
	@Before
	public void SetUp()
	{
		s1 = new Score("Bela", 12);
		s2 = new Score("Pista", 23);
		tc = new TimeComparator();
	}
	
	@Test
	public void test() 
	{
		Assert.assertEquals(-1, tc.compare(s1, s2));
		Assert.assertEquals(1, tc.compare(s2, s1));
		Assert.assertEquals(0, tc.compare(s1, new Score("Peti", 12)));
	}

}
