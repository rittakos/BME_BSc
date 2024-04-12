package minesweeper;


import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class GameTest 
{

	Game game;
	
	@Before
	public void SetUp()
	{
		game = new Game();
	}
	
	
	
	@Test
	public void TestCreateFields()
	{
		boolean succes = true;
		for(Field[] ft : game.GetBoard())
		{
			for(Field f : ft)
			{
				if(f.GetNeighbourMines() != 0)
					succes = false;
				if(!f.isEnabled())
					succes = false;
				if(f.IsMine())
					succes = false;
			}
		}
		
		Assert.assertEquals(true, succes);
	}
	
	@Test
	public void TestNumOfNeighbourMines() 
	{		
		game.GetBoard()[1][1].SetMine(true);
		game.GetBoard()[1][2].SetMine(false);
		game.GetBoard()[1][3].SetMine(false);
		game.GetBoard()[2][1].SetMine(false);
		game.GetBoard()[2][2].SetMine(true);
		game.GetBoard()[2][3].SetMine(false);
		game.GetBoard()[3][1].SetMine(false);
		game.GetBoard()[3][2].SetMine(true);
		game.GetBoard()[3][3].SetMine(false);
		
		
		Assert.assertEquals(true, game.GetBoard()[1][1].IsMine());
		
		
		Assert.assertEquals(2 , game.MinesInNeighborhood(game.GetBoard()[2][2]));
		
		game.GetBoard()[2][3].SetMine(true);
		
		Assert.assertEquals(3 , game.MinesInNeighborhood(game.GetBoard()[2][2]));
		
		game.GetBoard()[2][3].SetMine(false);
		game.GetBoard()[2][2].SetMine(false);
	}
	
	@Test
	public void TestGenerateMines()
	{
		game.GenerateMines(game.GetBoard()[2][2]);
		int mines = 0;
		int fields = 0;
		
		for(Field[] ft : game.GetBoard())
		{
			for(Field f : ft)
			{
				++fields;
				if(f.IsMine())
					++mines;
			}
		}
		
		Assert.assertEquals(100, fields);
		Assert.assertEquals(10, mines);
		Assert.assertEquals(false, game.GetBoard()[2][2].IsMine());
	}

	@Test
	public void TestFold()
	{
		game.GetBoard()[0][0].SetMine(false);
		game.Fold(game.GetBoard()[0][0]);
		Assert.assertEquals(false, game.GetGameOver());
		
		Assert.assertEquals(false, game.GetBoard()[0][0].isEnabled());
	}
	
	@Test
	public void TestUpdateNumOfFlags()
	{
		game.UpdateNumOfFlags(4);
		Assert.assertEquals("6", game.GetFlagsBack());
	}
}
