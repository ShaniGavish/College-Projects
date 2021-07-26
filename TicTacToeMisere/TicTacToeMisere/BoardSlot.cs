using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToeMisere
{
	public class BoardSlot : Button
	{
		private readonly BoardPosition r_BoardPosition;

		public BoardSlot(BoardPosition i_BoardPosition)
		{
			this.r_BoardPosition = i_BoardPosition;
		}

		public BoardPosition BoardPosition
		{
			get { return this.r_BoardPosition; }
		}
	}
}
