using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToeMisere
{
	public class GameManager
	{
		private const int k_MinBoardSize = 4;
		private const int k_MaxBoardSize = 10;
		private readonly BoardLogic r_BoardLogic;
		private readonly FormGameBoard r_GameUi;
		private AiPlayer m_AiPlayer;
		private bool m_IsP2Human;
		private int m_P1Score;
		private int m_P2Score;
		private ePlayerSign m_CurrentPlayerSign = ePlayerSign.P1;

		public GameManager(BoardLogic i_BoardLogic, FormGameBoard i_GameUi)
		{
			this.r_BoardLogic = i_BoardLogic;
			this.r_GameUi = i_GameUi;
		}

		public void Play()
		{
			init();
			if(this.r_GameUi.IsInitGameSettings)
			{
				this.r_GameUi.ShowPlayerTurn();
				this.r_GameUi.ShowDialog();
			}
			else
			{
				Application.Exit();
			}
		}

		private void resetGame()
		{
			this.r_BoardLogic.ResetGameBoard();
			this.r_GameUi.ResetBoard();
		}

		private void init()
		{
			this.r_GameUi.InitGame(k_MinBoardSize, k_MaxBoardSize, turn);
			int boardSize = this.r_GameUi.BoardSize;
			this.r_BoardLogic.SetBoardBySize(boardSize);
			m_IsP2Human = this.r_GameUi.IsP2Human;

			if (!m_IsP2Human)
			{
				this.m_AiPlayer = new AiPlayer(this.r_BoardLogic, (char)ePlayerSign.P2);
			}
		}
		
		private void playAIMove()
		{
			BoardPosition bp = this.m_AiPlayer.GetMove();
			eGameStatus currentStatus = this.r_BoardLogic.PlayMove(bp, (char)m_CurrentPlayerSign);
			this.r_GameUi.UpdateBoardSlotByRowCol(m_CurrentPlayerSign, bp.m_Row, bp.m_Col);
			checkMoveStatus(currentStatus);
			togglePlayerSign();
			this.r_GameUi.IsP1Turn = this.m_CurrentPlayerSign == ePlayerSign.P1;
			this.r_GameUi.ShowPlayerTurn();
		}
		
		// Event Listener for Board Slot Click
		private void turn(object i_Sender, EventArgs i_E)
		{
			BoardSlot boardSlot = (BoardSlot)i_Sender;
			eGameStatus currentStatus = this.r_BoardLogic.PlayMove(boardSlot.BoardPosition, (char)m_CurrentPlayerSign);

			this.r_GameUi.UpdateBoardSlotByPSign(m_CurrentPlayerSign, boardSlot);
			checkMoveStatus(currentStatus);
			if (currentStatus == eGameStatus.Continue)
			{
				togglePlayerSign();
				this.r_GameUi.IsP1Turn = this.m_CurrentPlayerSign == ePlayerSign.P1;
				this.r_GameUi.ShowPlayerTurn();
				if(!m_IsP2Human)
				{
					playAIMove();
				}
			}
		}

		private void checkMoveStatus(eGameStatus i_CurrentStatus)
		{
			if (i_CurrentStatus == eGameStatus.Lose)
			{
				setScore();
				DialogResult dr = this.r_GameUi.ShowWinStatusMessage(m_CurrentPlayerSign);
				this.r_GameUi.UpdateScore(m_P1Score, m_P2Score);

				if(dr == DialogResult.Yes)
				{
					this.resetGame();
				}
				else
				{
					Application.Exit();
				}
			}
			else if (i_CurrentStatus == eGameStatus.Tie)
			{
				DialogResult dr = this.r_GameUi.ShowTieStatusMessage();
				if (dr == DialogResult.Yes)
				{
					this.resetGame();
				}
				else
				{
					Application.Exit();
				}
			}
		}
		
		private void togglePlayerSign()
		{
			m_CurrentPlayerSign = m_CurrentPlayerSign == ePlayerSign.P1 ?
				                      ePlayerSign.P2 : ePlayerSign.P1;
		}

		private void setScore()
		{
			if (m_CurrentPlayerSign == ePlayerSign.P1)
			{
				m_P2Score += 1;
			}
			else
			{
				m_P1Score += 1;
			}
		}
	}
}
