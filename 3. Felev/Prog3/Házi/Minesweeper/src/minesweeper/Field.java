package minesweeper;
import java.awt.Insets;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JButton;


public class Field extends JButton implements MouseListener
{
	private static final long serialVersionUID = 1L;

	private Game game;
	
	private int status;
	private int neighbourMines;
	private Point coord;
	private boolean mine;
	
	
	public Field(Point coord, Game game) 
	{
		this.game = game;
		status = 0;
		neighbourMines = 0;
		mine = false;
		this.coord = coord;
		
		setMargin(new Insets(1, 1, 1, 1));
		addMouseListener(this);
		this.setEnabled(true);
	}

	public Point GetCoord()
	{
		return coord;
	}
	
	public int GetNeighbourMines()
	{
		return neighbourMines;
	}
	
	public void SetNeighbourMines(int mines)
	{
		neighbourMines = mines;
	}
	
	@Override
 	public void mousePressed(MouseEvent e) 
	{
		if (e.getButton() == MouseEvent.BUTTON1) 
		{
			game.Fold(this);
			game.CheckWin();
			
		}else if (e.getButton() == MouseEvent.BUTTON3) 
		{
			int numOfFlags = game.GetNumOfFlags();
			if (status == 0) 
			{
				status = 1;
				setIcon(game.GetImage(1));
				numOfFlags += 1;
				
			}else if (status == 1) 
			{
				status = 2;
				setIcon(game.GetImage(2));
				numOfFlags -= 1;
				
			}else if(status == 2)
			{
				status = 0;
				setIcon(game.GetImage(0));
			}
			
			game.UpdateNumOfFlags(numOfFlags);
		}
		
	}

	public boolean IsMine()
	{
		return mine;
	}

	public void SetMine(boolean mine)
	{
		this.mine = mine;
	}

	public int GetStatus()
	{
		return status;
	}
	
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
}
