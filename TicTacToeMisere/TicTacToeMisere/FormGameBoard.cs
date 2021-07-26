using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToeMisere
{
	public partial class FormGameBoard : Form
	{
		private const int k_Width = 120;

		private FormGameSettings m_GameSettings;
		private bool m_IsInitGameSettings = false;
		private int m_BoardSize;
		private TableLayoutPanel m_TableLayoutPanelBoard = new TableLayoutPanel();
		private Label m_Board = new Label();
		private Label m_Players = new Label();
		private Label m_P1 = new Label();
		private Label m_P1Score = new Label();
		private Label m_P2 = new Label();
		private Label m_P2Score = new Label();
		private bool m_IsP1Turn = true;

		private EventHandler m_BoardSlotEventHandler;

		public void InitGame(int i_MinBoardSize, int i_MaxBoardSize, EventHandler i_BoardSlotEventHandler)
		{
			this.m_GameSettings = new FormGameSettings(i_MinBoardSize, i_MaxBoardSize);
			this.AutoSize = false;
			this.FormBorderStyle = FormBorderStyle.FixedDialog;
			this.StartPosition = FormStartPosition.CenterScreen;
			this.Text = "TicTacToeMisere";
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.m_BoardSlotEventHandler = i_BoardSlotEventHandler;
			setGameBoard();
		}

		private void setGameBoard()
		{
			if(verifyInitGameSettings())
			{
				this.Size = new Size(m_GameSettings.Rows * k_Width, m_GameSettings.Rows * k_Width);
				this.m_BoardSize = m_GameSettings.Rows;
				setButtons();
				setPlayers();
			}
		}

		private void setButtons()
		{
			m_Board.Size = new Size(m_BoardSize * (k_Width - (k_Width / 3)), m_BoardSize * (k_Width - (k_Width / 3)));
			m_Board.Location = new Point(m_BoardSize * 19, m_BoardSize * 5);
			this.m_TableLayoutPanelBoard.ColumnCount = m_BoardSize;
			this.m_TableLayoutPanelBoard.RowCount = m_BoardSize;
			this.m_TableLayoutPanelBoard.ColumnStyles.Clear();
			this.m_TableLayoutPanelBoard.RowStyles.Clear();

			for (int i = 0; i < m_BoardSize; i++)
			{
				this.m_TableLayoutPanelBoard.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100 / m_BoardSize));
			}

			for (int i = 0; i < m_BoardSize; i++)
			{
				this.m_TableLayoutPanelBoard.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100 / m_BoardSize));
			}

			for (int i = 0; i < m_BoardSize; i++)
			{
				for (int j = 0; j < m_BoardSize; j++)
				{
					BoardSlot button = new BoardSlot(new BoardPosition(i, j));
					button.Click += this.m_BoardSlotEventHandler;
					button.Dock = DockStyle.Fill;
					this.m_TableLayoutPanelBoard.Controls.Add(button, j, i);
					button.FlatStyle = FlatStyle.Flat;
					button.TabStop = false;
				}
			}
			
			m_TableLayoutPanelBoard.Dock = DockStyle.Fill;
			m_Board.Controls.Add(m_TableLayoutPanelBoard);
			this.Controls.Add(m_Board);
		}

		private void setPlayers()
		{
			m_P1.Width = m_GameSettings.P1Name.Length * 10;
			m_P1.Text = m_GameSettings.P1Name + ":";
			this.m_Players.Controls.Add(m_P1);

			m_P1Score.Width = 15;
			m_P1Score.Text = "0";
			m_P1Score.Location = new Point(m_P1.Width, 0);
			this.m_Players.Controls.Add(m_P1Score);

			m_P2.Width = m_GameSettings.P2Name.Length * 10;
			
			m_P2.Text = m_GameSettings.P2Name + ":";
			m_P2.Location = new Point(m_P1Score.Location.X + m_P1Score.Width + 10, 0);
			this.m_Players.Controls.Add(m_P2);

			m_P2Score.Width = 15;
			m_P2Score.Text = "0";
			m_P2Score.Location = new Point(m_P2.Location.X + m_P2.Width, 0);
			this.m_Players.Controls.Add(m_P2Score);
			m_Players.Width = m_P2Score.Location.X + m_P2Score.Width;
			this.m_Players.Location = new Point(((m_BoardSize * 120) - this.m_Players.Width) / 2, m_BoardSize * 90);
			
			this.Controls.Add(this.m_Players);
		}

		public void ShowPlayerTurn()
		{
			if(m_IsP1Turn)
			{
				m_P1.Font = new Font(m_P1.Font, FontStyle.Bold);
				m_P1Score.Font = new Font(m_P1Score.Font, FontStyle.Bold);
				m_P2.Font = new Font(m_P2.Font, FontStyle.Regular);
				m_P2Score.Font = new Font(m_P2Score.Font, FontStyle.Regular);
			}
			else
			{
				m_P2.Font = new Font(m_P2.Font, FontStyle.Bold);
				m_P2Score.Font = new Font(m_P2Score.Font, FontStyle.Bold);
				m_P1.Font = new Font(m_P1.Font, FontStyle.Regular);
				m_P1Score.Font = new Font(m_P1Score.Font, FontStyle.Regular);
			}
		}

		public void UpdateBoardSlotByPSign(ePlayerSign i_PlayerSign, BoardSlot i_BoardSlot)
		{
			i_BoardSlot.Text = ((char)i_PlayerSign).ToString();
			i_BoardSlot.Font = new Font(i_BoardSlot.Font.FontFamily, 20);
			i_BoardSlot.Enabled = false;
		}

		public void UpdateBoardSlotByRowCol(ePlayerSign i_PlayerSign, int row, int col)
		{
			BoardSlot boardSlot = (BoardSlot)this.m_TableLayoutPanelBoard.GetControlFromPosition(col, row);
			UpdateBoardSlotByPSign(i_PlayerSign, boardSlot);
		}

		public void UpdateScore(int i_P1Score, int i_P2Score)
		{
			this.m_P1Score.Text = i_P1Score.ToString();
			this.m_P2Score.Text = i_P2Score.ToString();
		}

		public DialogResult ShowTieStatusMessage()
		{
			string tieMessage = string.Format("Tie!{0}Would you like to play another round?", Environment.NewLine);
			DialogResult dr = MessageBox.Show(tieMessage, "A Tie!", MessageBoxButtons.YesNo);
			return dr;
		}

		public DialogResult ShowWinStatusMessage(ePlayerSign i_WinPlayerSign)
		{
			string winnerName = i_WinPlayerSign == ePlayerSign.P2 ? m_GameSettings.P1Name : m_GameSettings.P2Name;
			string winMessage = string.Format("{0} has win! {1} Would you like to play another round?", winnerName, Environment.NewLine);
			DialogResult dr = MessageBox.Show(winMessage, "A Win!", MessageBoxButtons.YesNo);
			return dr;
		}

		private bool verifyInitGameSettings()
		{
			if (!m_IsInitGameSettings)
			{
				if (m_GameSettings.ShowDialog() == DialogResult.OK)
				{
					m_IsInitGameSettings = true;
				}
			}

			return m_IsInitGameSettings;
		}

		public void ResetBoard()
		{
			this.m_TableLayoutPanelBoard.Controls.Clear();
			setButtons();
		}

		public int BoardSize
		{
			get { return m_BoardSize; }
		}

		public bool IsP2Human
		{
			get { return m_GameSettings.IsP2Human; }
		}

		public bool IsP1Turn
		{
			set { m_IsP1Turn = value; }
		}

		public bool IsInitGameSettings
		{
			get { return this.m_IsInitGameSettings; }
		}
	}
}
