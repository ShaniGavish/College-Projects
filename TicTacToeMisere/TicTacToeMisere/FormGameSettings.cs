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
	public partial class FormGameSettings : Form
	{
		private readonly Label r_LabelPlayers = new Label();
		private readonly Label r_LabelP1Name = new Label();
		private readonly Label r_LabelP2Name = new Label();

		private readonly TextBox r_TextboxP1Name = new TextBox();
		private readonly TextBox r_TextboxP2Name = new TextBox();

		private readonly CheckBox r_CheckBoxIsP2Human = new CheckBox();
		private readonly Label r_LabelBoardSize = new Label();
		private readonly Label r_LabelRows = new Label();
		private readonly Label r_LabelCols = new Label();
		private readonly int r_MaxBoardSize;
		private readonly int r_MinBoardSize;

		private readonly NumericUpDown r_NumericUdRows = new NumericUpDown();
		private readonly NumericUpDown r_NumericUdCols = new NumericUpDown();
		private readonly Button r_ButtonStart = new Button();
		private bool m_IsP2HumanChecked = false;

		public FormGameSettings(int i_MinBoardSize, int i_MaxBoardSize)
		{
			this.FormBorderStyle = FormBorderStyle.FixedDialog;
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(324, 347);
			this.StartPosition = FormStartPosition.CenterScreen;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.ShowIcon = false;
			this.Text = "Game Settings";
			this.ResumeLayout(false);
			this.r_MinBoardSize = i_MinBoardSize;
			this.r_MaxBoardSize = i_MaxBoardSize;
			initControls();
		}

		private void initControls()
		{
			// Players Label
			this.r_LabelPlayers.AutoSize = true;
			this.r_LabelPlayers.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
			this.r_LabelPlayers.Location = new System.Drawing.Point(22, 20);
			this.r_LabelPlayers.Size = new System.Drawing.Size(61, 17);
			this.r_LabelPlayers.TabIndex = 0;
			this.r_LabelPlayers.Text = "Players:";

			// P1 Label
			this.r_LabelP1Name.AutoSize = true;
			this.r_LabelP1Name.Location = new System.Drawing.Point(43, 58);
			this.r_LabelP1Name.Size = new System.Drawing.Size(64, 20);
			this.r_LabelP1Name.TabIndex = 1;
			this.r_LabelP1Name.Text = "Player 1:";
			
			// P1 Name
			this.r_TextboxP1Name.Location = new System.Drawing.Point(135, 55);
			this.r_TextboxP1Name.Size = new System.Drawing.Size(125, 27);
			this.r_TextboxP1Name.TabIndex = 2;
		 
			// Is P2 Human CheckBox
			this.r_CheckBoxIsP2Human.AutoSize = true;
			this.r_CheckBoxIsP2Human.Location = new System.Drawing.Point(43, 103);
			this.r_CheckBoxIsP2Human.Size = new System.Drawing.Size(18, 17);
			this.r_CheckBoxIsP2Human.TabIndex = 3;
			this.r_CheckBoxIsP2Human.UseVisualStyleBackColor = true;

			// P2 Label
			this.r_LabelP2Name.AutoSize = true;
			this.r_LabelP2Name.Location = new System.Drawing.Point(67, 100);
			this.r_LabelP2Name.Size = new System.Drawing.Size(60, 20);
			this.r_LabelP2Name.TabIndex = 4;
			this.r_LabelP2Name.Text = "Player2:";
			
			// P2 Name
			this.r_TextboxP2Name.Enabled = false;
			this.r_TextboxP2Name.Location = new System.Drawing.Point(135, 97);
			this.r_TextboxP2Name.Size = new System.Drawing.Size(125, 27);
			this.r_TextboxP2Name.TabIndex = 5;
			this.r_TextboxP2Name.Text = "[Computer]";
			 
			// Board Size Label
			this.r_LabelBoardSize.AutoSize = true;
			this.r_LabelBoardSize.Location = new System.Drawing.Point(28, 175);
			this.r_LabelBoardSize.Size = new System.Drawing.Size(83, 20);
			this.r_LabelBoardSize.TabIndex = 6;
			this.r_LabelBoardSize.Text = "Board Size:";

			// RowsLabel
			this.r_LabelRows.AutoSize = true;
			this.r_LabelRows.Location = new System.Drawing.Point(43, 228);
			this.r_LabelRows.Size = new System.Drawing.Size(47, 20);
			this.r_LabelRows.TabIndex = 7;
			this.r_LabelRows.Text = "Rows:";

			// NUDRows
			this.r_NumericUdRows.Location = new System.Drawing.Point(109, 221);
			this.r_NumericUdRows.Size = new System.Drawing.Size(45, 27);
			this.r_NumericUdRows.TabIndex = 8;
			this.r_NumericUdRows.Value = new decimal(new int[] { 4, 0, 0, 0 });
			this.r_NumericUdRows.Minimum = this.r_MinBoardSize;
			this.r_NumericUdRows.Maximum = this.r_MaxBoardSize;

			// ColsLabel
			this.r_LabelCols.AutoSize = true;
			this.r_LabelCols.Location = new System.Drawing.Point(185, 228);
			this.r_LabelCols.Size = new System.Drawing.Size(40, 20);
			this.r_LabelCols.TabIndex = 9;
			this.r_LabelCols.Text = "Cols:";
 
			// NUDCols
			this.r_NumericUdCols.Location = new System.Drawing.Point(247, 221);
			this.r_NumericUdCols.Size = new System.Drawing.Size(43, 27);
			this.r_NumericUdCols.TabIndex = 10;
			this.r_NumericUdCols.Value = new decimal(new int[] { 4, 0, 0, 0 });
			this.r_NumericUdCols.Minimum = this.r_MinBoardSize;
			this.r_NumericUdCols.Maximum = this.r_MaxBoardSize;

			// StartButton
			this.r_ButtonStart.Location = new System.Drawing.Point(28, 287);
			this.r_ButtonStart.Size = new System.Drawing.Size(262, 29);
			this.r_ButtonStart.TabIndex = 11;
			this.r_ButtonStart.Text = "Start!";
			this.r_ButtonStart.UseVisualStyleBackColor = true;

			this.Controls.AddRange(new Control[] { r_LabelPlayers, r_LabelP1Name, r_TextboxP1Name, r_LabelP2Name, r_TextboxP2Name, r_CheckBoxIsP2Human, r_LabelBoardSize, r_LabelRows, r_LabelCols, r_NumericUdRows, r_NumericUdCols, r_ButtonStart });

			this.r_ButtonStart.Click += new EventHandler(startButtonClicked);
			this.r_CheckBoxIsP2Human.CheckedChanged += toggleP2TextBoxName;
			this.r_NumericUdRows.ValueChanged += numericUdRowsChanged;
			this.r_NumericUdCols.ValueChanged += numericUdColsChanged;
		}

		public string P1Name
		{
			get { return r_TextboxP1Name.Text; }
		}

		public string P2Name
		{
			get { return r_TextboxP2Name.Text; }
		}

		public bool IsP2Human
		{
			get { return m_IsP2HumanChecked; }
		}

		public int Rows
		{
			get { return (int)r_NumericUdRows.Value; }
		}

		private void toggleP2TextBoxName(object i_Sender, EventArgs i_E)
		{
			m_IsP2HumanChecked = r_CheckBoxIsP2Human.Checked;
			if (m_IsP2HumanChecked)
			{
				r_TextboxP2Name.Enabled = true;
				r_TextboxP2Name.Text = string.Empty;
			}
			else
			{
				r_TextboxP2Name.Enabled = false;
				r_TextboxP2Name.Text = "[Computer]";
			}
		}

		private void numericUdRowsChanged(object i_Sender, EventArgs i_E)
		{
			if(r_NumericUdRows.Value != r_NumericUdCols.Value)
			{
				r_NumericUdCols.Value = r_NumericUdRows.Value;
			}
		}

		private void numericUdColsChanged(object i_Sender, EventArgs i_E)
		{
			if (r_NumericUdCols.Value != r_NumericUdRows.Value)
			{
				r_NumericUdRows.Value = r_NumericUdCols.Value;
			}
		}

		private void startButtonClicked(object i_Sender, EventArgs i_E)
		{
			if(!isValidSettings())
			{
				MessageBox.Show("Invalid Settings", "Error", MessageBoxButtons.OK);
			}
			else
			{
				this.DialogResult = DialogResult.OK;
				this.Close();
			}
		}

		private bool isValidSettings()
		{
			return r_TextboxP1Name.Text != string.Empty && r_TextboxP2Name.Text != string.Empty;
		}
	}
}
