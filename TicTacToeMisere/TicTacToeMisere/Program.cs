using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToeMisere
{
	public class Program
	{
		public static void Main()
		{
			GameManager game = new GameManager(new BoardLogic(), new FormGameBoard());
			game.Play();
		}
	}
}
