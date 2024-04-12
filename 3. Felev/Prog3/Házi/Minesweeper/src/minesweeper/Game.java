package minesweeper;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.util.Random;

import javax.swing.ButtonGroup;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.Timer;
import javax.swing.border.EmptyBorder;


public class Game extends JFrame implements ActionListener 
{
	private static final long serialVersionUID = 1L;

	private Icon[] images;
	private ScoreBoard[] scoreBoards;
	
	private int numOfRows;
	private int numOfColumns; 
	private int numOfMines;
	private int time;
	private int numOfFlags;
	
	private boolean gameOver;
	
	private Dimension size;
	
	private JPanel gamePanel = new JPanel();
	private JPanel statusPanel;
	
	
	private TextField timerText;
	private TextField numOfFlagsText;
	
	private Timer timer;
	
	private int level;
	
	private JRadioButtonMenuItem[] levels;
	
	private Field[][] board;
	
	
	
	public Game() 
	{
		super("Minesweeper");
		
		InitImages();
		
		InitWindow();
		
		StartGame();
		
		setVisible(true);
		setLocationRelativeTo(null);
	}
	
	
	
	private void InitScoreBoards()
	{
		String[] scoreBoardFilenames = {"beginnerscores.txt", "intermediatescores.txt", "advancedscores.txt"};
		scoreBoards = new ScoreBoard[scoreBoardFilenames.length];
		for(int idx = 0; idx < scoreBoardFilenames.length; ++idx)
		{
			scoreBoards[idx] = new ScoreBoard(scoreBoardFilenames[idx]);
		}
	}
	
	private void InitImages()
	{
		String[] imagenames = {"", "flag.png", "question_mark.png", "cross.png", "mine.png"};
		images = new Icon[imagenames.length];
		
		for (int idx = 0; idx < images.length; ++idx)
		{
			images[idx] = new ImageIcon(imagenames[idx]);
		}
	}

	private void InitWindow()
	{
		numOfRows = 10;
		numOfColumns = 10;
		numOfMines = 10;
		level = 0;
		
		size = new Dimension(numOfRows * 40, numOfColumns * 50);
		setPreferredSize(size);
		
		levels = new JRadioButtonMenuItem[3];
		JMenuBar menuBar = new JMenuBar();
		JMenu levelMenu = new JMenu("Level");
		ButtonGroup levelGroup = new ButtonGroup();
		
		levels[0] = new JRadioButtonMenuItem("Beginner", true);
		levels[0].setMnemonic(KeyEvent.VK_B);
		levels[1] = new JRadioButtonMenuItem("Intermediate", false);
		levels[1].setMnemonic(KeyEvent.VK_I);
		levels[2] = new JRadioButtonMenuItem("Advanced", false);
		levels[2].setMnemonic(KeyEvent.VK_A);
		
        for (JRadioButtonMenuItem level : levels) 
        {
            levelGroup.add(level);
            level.addActionListener(this);
            levelMenu.add(level);
        }
        levelMenu.setMnemonic(KeyEvent.VK_L);
		
		menuBar.add(levelMenu);
		setJMenuBar(menuBar);
	}

	private void InitPanel()
	{
		setLayout(new BorderLayout());
		gamePanel.setBorder(new EmptyBorder(20, 20, 0, 20));
		add(gamePanel, BorderLayout.CENTER);
		gamePanel.setLayout(new GridLayout(numOfRows, numOfColumns));
		
		CreateFields(gamePanel);
		
		statusPanel = new JPanel();
		
		JLabel timeLabel = new JLabel("time: ");
		timerText = new TextField("0", 1);
		timerText.setEditable(false);
		statusPanel.add(timeLabel);
		statusPanel.add(timerText);
		
		JLabel flagsLabel;
		flagsLabel = new JLabel("flags: ");
		numOfFlagsText = new TextField(1);
		numOfFlagsText.setEditable(false);
		statusPanel.add(flagsLabel);
		statusPanel.add(numOfFlagsText);
		
		add(statusPanel, BorderLayout.SOUTH);
	}
	
	private void CreateFields(JPanel gamePanel) 
	{
		board = new Field[numOfRows][numOfColumns];
		Point currentPoint;
		
		for (int rowId = 0; rowId < numOfRows; ++rowId) 
		{
			for (int columnId = 0; columnId < numOfColumns; ++columnId) 
			{
				currentPoint = new Point(rowId, columnId);
				board[rowId][columnId] = new Field(currentPoint, this);
				gamePanel.add(board[rowId][columnId]);
			}
		}
	}

	

	private void StartGame() 
	{
		this.setPreferredSize(size);
		InitScoreBoards();
		
		gameOver = false; 
		time = 0; 
		numOfFlags = 0;
		
		InitPanel();
		
		timer = new Timer(1000, new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				timerText.setText(Integer.toString(++time));
			}
		});
		
		UpdateNumOfFlags(numOfFlags);
		pack();
	}
	
	
	
	public void GenerateMines(Field firstField) 
	{
		Random rnd = new Random();
		
		int currentRow, currentColumn;
		
		for (int countOfMines = 0; countOfMines < numOfMines;) 
		{
			currentRow = rnd.nextInt(numOfRows);
			currentColumn = rnd.nextInt(numOfColumns);
			
			if (!board[currentRow][currentColumn].IsMine()) 
			{
				if(!(firstField.GetCoord().x == currentRow && firstField.GetCoord().y == currentColumn))
				{
					board[currentRow][currentColumn].SetMine(true);
					++countOfMines;
				}
			}
		}
	}

	private void SurroundMines() 
	{
		for(int i = 0; i < numOfRows; ++i)
		{
			for(int j = 0; j < numOfColumns; ++j)
			{
				board[i][j].SetNeighbourMines(MinesInNeighborhood(board[i][j]));
			}
		}
	}
	
	public int MinesInNeighborhood(Field currentField)
	{
	    int numOfMines = 0;
	    int row = currentField.GetCoord().x;
	    int column = currentField.GetCoord().y;
	    
	    for(int columnId = column - 1; columnId <= column + 1; ++columnId)
	    {
	        for (int rowId = row - 1; rowId <= row + 1; ++rowId)
	        {
	             if(!(rowId == row && columnId == column))        
	             {
		               	try
		                {
		                    if (board[rowId][columnId].IsMine())
		                         ++numOfMines;
		                }catch(IndexOutOfBoundsException e)
		                {
		                    continue;
		                }
	             }
	        }
	    }
	    return numOfMines;
	}
		
	private void FoldNeighbours(Field currentField)
	{
		int currentRow = currentField.GetCoord().x;
		int currentColumn = currentField.GetCoord().y;
		
		for (int rowId = currentRow - 1; rowId <= currentRow + 1; ++rowId) 
		{
			if (rowId >= 0 && rowId < numOfRows) 
			{
				for (int columnId = currentColumn - 1; columnId <= currentColumn + 1; ++columnId) 
				{
					if (columnId >= 0 && columnId < numOfColumns && !board[rowId][columnId].IsMine()) 
					{
						Fold(board[rowId][columnId]);
					}
				}
			}
		}
	}
	
	private void FoldAllFields() 
	{
		for (int rowId = 0; rowId < numOfRows; ++rowId) 
		{
			for (int columnId = 0; columnId < numOfColumns; ++columnId) 
			{
				if (!board[rowId][columnId].IsMine() && board[rowId][columnId].GetStatus() >= 1)
				{
					board[rowId][columnId].setIcon(this.GetImage(3));
				}
				Fold(board[rowId][columnId]);
			}
		}
	}

	public void CheckWin() 
	{
		boolean win = true;
		for (int rowId = 0; rowId < numOfRows && win; ++rowId) 
		{
			for (int columnId = 0; columnId < numOfColumns; ++columnId) 
			{
				if (!board[rowId][columnId].IsMine() && board[rowId][columnId].isEnabled()) 
				{
					win = false;
					break;
				}
			}
		}
		if (win) {
			gameOver = true;
			GameWon();
		}
	}

	private void GameWon() 
	{
		scoreBoards[level].AddScore(new Score(System.getProperty("user.name"), Integer.parseInt(timerText.getText())));
		scoreBoards[level].OpenScoreBoard();
		
		timer.stop();
		
		Object[] options = {"Play Again", "Exit"};
		
		int selection = JOptionPane.showOptionDialog(this, "Your Time: " + timerText.getText() + " seconds", "You Won", JOptionPane.YES_NO_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);
		
		
		if (selection == JOptionPane.YES_OPTION) 
		{
			size = getSize();
			remove(statusPanel);
			gamePanel.removeAll();
			StartGame();
		} else 
		{
			System.exit(0);
		}
	}

	private void GameLost() 
	{
		timer.stop();
		
		FoldAllFields();
		Object[] options = {"Play Again", "Exit"};
		int selection = JOptionPane.showOptionDialog(this, "You Lost", "You Lost", JOptionPane.YES_NO_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);
		if (selection == JOptionPane.YES_OPTION) 
		{
			size = getSize();
			remove(statusPanel);
			gamePanel.removeAll();
			StartGame();
		} else 
		{
			System.exit(0);
		}
	}

	private void RestartGame(ActionEvent e) 
	{
		int selection = JOptionPane.showConfirmDialog(this, "Do you want restart the game?");
		
		if (selection == JOptionPane.YES_OPTION) 
		{
			timer.stop();
			
			if (e.getSource() == levels[0]) 
			{
				numOfRows = 10;
				numOfColumns = 10;
				numOfMines = 10;
				level = 0;
				size = new Dimension(numOfRows * 40, numOfColumns * 50);
				
			} else if (e.getSource() == levels[1]) 
			{
				numOfRows = 16; 
				numOfColumns = 16;
				numOfMines = 40;
				level = 1;
				size = new Dimension(numOfRows * 30, numOfColumns * 40);
				
			} else if (e.getSource() == levels[2]) 
			{
				numOfRows = 16; 
				numOfColumns = 30;
				numOfMines = 99;
				size = new Dimension(numOfRows * 50, numOfColumns * 20);
			}
			
			remove(statusPanel);
			gamePanel.removeAll();
			
			StartGame();
			setLocationRelativeTo(null);
			
		} else 
		{
			switch (numOfMines) 
			{
			case 10:
				levels[0].setSelected(true);
				break;
			case 40:
				levels[1].setSelected(true);
				break;
			case 99:
				levels[2].setSelected(true);
				break;
			default:
				break;
			}
		}
	}

	
	
	@Override
	public void actionPerformed(ActionEvent e) 
	{
		RestartGame(e);
	}

	public int GetNumOfFlags()
	{
		return numOfFlags;
	}
	
	public void UpdateNumOfFlags(int numOfFlags) 
	{
		this.numOfFlags = numOfFlags;
		numOfFlagsText.setText(Integer.toString(numOfMines - numOfFlags));
	}

	public String GetFlagsBack()
	{
		return numOfFlagsText.getText();
	}

	public boolean GetGameOver()
	{
		return gameOver;
	}
	
	public void Fold(Field currentField) 
	{
		if (time == 0) 
		{
			timer.start();
			GenerateMines(currentField);
			++time;
			SurroundMines();
		}
		if (currentField.isEnabled() && currentField.GetStatus() == 0) 
		{
			if(currentField.IsMine())
			{
				currentField.setIcon(this.GetImage(4));
				if (!gameOver) 
				{
					gameOver = true;
					GameLost();
				}
			}else if(currentField.GetNeighbourMines() == 0)
			{
				currentField.setEnabled(false);
				currentField.setText("");
				
				
				FoldNeighbours(currentField);
			}else
			{
				currentField.setEnabled(false);
				currentField.setText(Integer.toString(currentField.GetNeighbourMines()));
			}
			
		}
	}

	public Icon GetImage(int idx)
	{
		return images[idx];
	}

	public Field[][] GetBoard()
	{
		return board;
	}
	
	public static void main (String[] args) throws IOException, ClassNotFoundException 
	{
		new Game();		
	}
}