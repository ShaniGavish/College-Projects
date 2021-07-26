using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class ValueOutOfRangeException : Exception
	{
		private readonly float r_MinValue;
		private readonly float r_MaxValue;

		public ValueOutOfRangeException(float i_MinValue, float i_MaxValue, string i_Message)
			: base(i_Message)
		{
			this.r_MinValue = i_MinValue;
			this.r_MaxValue = i_MaxValue;
		}

		public override string Message
		{
			get { return string.Format("{0}, range is {1}-{2}", base.Message, r_MinValue, r_MaxValue); }
		}
	}
}
