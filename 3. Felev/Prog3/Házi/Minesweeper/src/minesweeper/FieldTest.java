package minesweeper;

import java.awt.Point;

import org.junit.Before;
import org.junit.Test;
import org.junit.Assert;


public class FieldTest 
{
	Field field;
	
	@Before
	public void SetUp()
	{
		field = new Field(new Point(1, 5), new Game());
		field.SetMine(true);
	}
	
	
	@Test
	public void TestIsMine() 
	{
		Assert.assertEquals(true, field.IsMine());
		field.SetMine(false);
		Assert.assertEquals(false, field.IsMine());
	}
	
	@Test
	public void TestGetCoord() 
	{
		Assert.assertEquals(1, field.GetCoord().x);
		Assert.assertEquals(5, field.GetCoord().y);
	}



}
