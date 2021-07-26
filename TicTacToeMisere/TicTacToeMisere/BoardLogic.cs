using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TicTacToeMisere
{
	public class BoardLogic
	{
		private const char k_EmptyCell = ' ';
		private char[,] m_BoardMatrix;
		private int m_BoardSize;
		private int m_HowManyPiecesWerePlaced;

		public void SetBoardBySize(int i_BoardSize)
		{
			this.m_BoardSize = i_BoardSize;
			this.m_BoardMatrix = new char[m_BoardSize, m_BoardSize];
			ResetGameBoard();
		}

		public void ResetGameBoard()
		{
			this.m_HowManyPiecesWerePlaced = 0;
			for (int i = 0; i < m_BoardSize; i++)
			{
				for (int j = 0; j < m_BoardSize; j++)
				{
					this.m_BoardMatrix[i, j] = k_EmptyCell;
				}
			}
		}

		public char[,] BoardMatrix
		{
			get
			{
				return this.m_BoardMatrix;
			}
		}

		public int BoardSize
		{
			get
			{
				return this.m_BoardSize;
			}
		}

		public eGameStatus PlayMove(BoardPosition i_BoardPosition, char i_Sign)
		{
			eGameStatus moveStatus;
			if (isQuit(i_BoardPosition))
			{
				moveStatus = eGameStatus.Lose;
			}
			else
			{
				this.m_BoardMatrix[i_BoardPosition.m_Row, i_BoardPosition.m_Col] = i_Sign;
				this.m_HowManyPiecesWerePlaced++;
				moveStatus = checkWinStatus(i_BoardPosition, i_Sign);
			}

			return moveStatus;
		}

		private bool isQuit(BoardPosition i_BoardPosition)
		{
			return i_BoardPosition.m_Row == -1 && i_BoardPosition.m_Col == -1;
		}

		private eGameStatus checkWinStatus(BoardPosition i_BoardPosition, char i_Sign)
		{
			eGameStatus gameStatus = eGameStatus.Continue;
			if (isWin(i_BoardPosition, i_Sign))
			{
				gameStatus = eGameStatus.Lose;
			}
			else if (this.m_HowManyPiecesWerePlaced == this.m_BoardMatrix.Length)
			{
				gameStatus = eGameStatus.Tie;
			}

			return gameStatus;
		}

		private bool isWin(BoardPosition i_BoardPosition, char i_Sign)
		{
			return checkRow(i_BoardPosition.m_Row, i_Sign) ||
				   checkCol(i_BoardPosition.m_Col, i_Sign) ||
				   (isInMainDiagonal(i_BoardPosition) && checkMainDiagonal(i_Sign)) ||
				   (isInAntiDiagonal(i_BoardPosition) && checkAntiDiagonal(i_Sign));
		}

		private bool checkRow(int i_Row, char i_Sign)
		{
			bool isFullRow = true;
			for (int i = 0; i < this.m_BoardSize; i++)
			{
				if (this.m_BoardMatrix[i_Row, i] != i_Sign)
				{
					isFullRow = false;
				}
			}

			return isFullRow;
		}

		private bool checkCol(int i_Col, char i_Sign)
		{
			bool isFullRow = true;
			for (int i = 0; i < this.m_BoardSize; i++)
			{
				if (this.m_BoardMatrix[i, i_Col] != i_Sign)
				{
					isFullRow = false;
				}
			}

			return isFullRow;
		}

		private bool checkMainDiagonal(char i_Sign)
		{
			bool isFull = true;
			for (int i = 0; i < this.m_BoardSize; i++)
			{
				if (i_Sign != this.m_BoardMatrix[i, i])
				{
					isFull = false;
				}
			}

			return isFull;
		}

		private bool checkAntiDiagonal(char i_Sign)
		{
			bool isFull = true;
			for (int i = 0; i < this.m_BoardSize; i++)
			{
				if (i_Sign != this.m_BoardMatrix[this.m_BoardSize - i - 1, i])
				{
					isFull = false;
				}
			}

			return isFull;
		}

		private bool isInMainDiagonal(BoardPosition i_BoardPosition)
		{
			return i_BoardPosition.m_Row == i_BoardPosition.m_Col;
		}

		private bool isInAntiDiagonal(BoardPosition i_BoardPosition)
		{
			return this.m_BoardSize - i_BoardPosition.m_Row - 1 == i_BoardPosition.m_Col;
		}

		public bool IsValidRow(int i_Row)
		{
			return i_Row >= 0 && i_Row < this.m_BoardSize;
		}

		public bool IsValidCol(int i_Col)
		{
			return i_Col >= 0 && i_Col < this.m_BoardSize;
		}

		private bool isEmptyCell(BoardPosition i_BoardPosition)
		{
			return this.m_BoardMatrix[i_BoardPosition.m_Row, i_BoardPosition.m_Col] == k_EmptyCell;
		}

		public bool IsValidMove(BoardPosition i_BoardPosition)
		{
			return IsValidRow(i_BoardPosition.m_Row) &&
				   IsValidCol(i_BoardPosition.m_Col) &&
				   isEmptyCell(i_BoardPosition);
		}

		public char GetSignAtPosition(BoardPosition i_Position)
		{
			return m_BoardMatrix[i_Position.m_Row, i_Position.m_Col];
		}
	}
}
