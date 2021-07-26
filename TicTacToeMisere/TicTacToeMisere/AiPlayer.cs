using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TicTacToeMisere
{
	public class AiPlayer
	{
		private readonly BoardLogic r_BoardLogic;
		private readonly char r_PlayerSign;

		public AiPlayer(BoardLogic i_BoardLogic, char i_PlayerSign)
		{
			this.r_BoardLogic = i_BoardLogic;
			this.r_PlayerSign = i_PlayerSign;
		}

		public BoardPosition GetMove()
		{
			int minNeighborsCount = 10;
			BoardPosition position = new BoardPosition();
			BoardPosition minNeighborsPosition = new BoardPosition();

			for (int i = 0; i <= r_BoardLogic.BoardSize; i++)
			{
				for (int j = 0; j <= r_BoardLogic.BoardSize; j++)
				{
					position.m_Row = i;
					position.m_Col = j;
					if (r_BoardLogic.IsValidMove(position))
					{
						int tempMinNeighborsCount = countNeighborsWithSameSign(position);
						if (tempMinNeighborsCount < minNeighborsCount)
						{
							minNeighborsPosition.m_Col = position.m_Col;
							minNeighborsPosition.m_Row = position.m_Row;
							minNeighborsCount = tempMinNeighborsCount;
						}
					}
				}
			}

			return minNeighborsPosition;
		}

		private int countNeighborsWithSameSign(BoardPosition i_Position)
		{
			int neighborsCount = 0;
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					BoardPosition tempPosition;
					tempPosition.m_Row = i_Position.m_Row + i;
					tempPosition.m_Col = i_Position.m_Col + j;
					if (r_BoardLogic.IsValidRow(tempPosition.m_Row) &&
					    r_BoardLogic.IsValidCol(tempPosition.m_Col) &&
					    r_BoardLogic.GetSignAtPosition(tempPosition) == r_PlayerSign)
					{
						neighborsCount++;
					}
				}
			}

			return neighborsCount;
		}
	}
}
