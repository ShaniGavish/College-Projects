using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class Wheel
	{
		private readonly string r_ManufacturerName;
		private readonly float r_MaxAirPressure;
		private float m_CurrentAirPressure;

		public Wheel(string i_ManufacturerName, float i_MaxAirPressure, float i_CurrentAirPressure)
		{
			this.r_ManufacturerName = i_ManufacturerName;
			this.r_MaxAirPressure = i_MaxAirPressure;
			this.m_CurrentAirPressure = i_CurrentAirPressure;
		}

		public void Pump(float i_AmountToPump)
		{
			if (this.m_CurrentAirPressure + i_AmountToPump > r_MaxAirPressure)
			{
				throw new ValueOutOfRangeException(0, r_MaxAirPressure, "Invalid amount to pump for air pressure");
			}

			this.m_CurrentAirPressure += i_AmountToPump;
		}

		public void PumpFull()
		{
			this.m_CurrentAirPressure = this.r_MaxAirPressure;
		}

		public Dictionary<string, object> GetWheelInfo()
		{
			return new Dictionary<string, object>()
				       {
					       { "Manufacturer Name", this.r_ManufacturerName },
					       { "Max Air Pressure", this.r_MaxAirPressure },
					       { "Current Air Pressure", this.m_CurrentAirPressure }
				       };
		}
	}
}
