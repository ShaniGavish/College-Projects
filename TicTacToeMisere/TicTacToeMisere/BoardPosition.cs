using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TicTacToeMisere
{
	public struct BoardPosition
	{
		public int m_Row;
		public int m_Col;

		public BoardPosition(int i_Row, int i_Col)
		{
			m_Row = i_Row;
			m_Col = i_Col;
		}
	}
}
