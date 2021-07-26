using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public abstract class Vehicle
	{
		private string m_ModelName;
		private string m_LicenseNumber;
		private eEnergyType m_EnergyType;
		private float m_MaxAmountOfEnergy;
		private float m_RemainingEnergyPercentage;
		private Wheel[] m_Wheels;

		public Vehicle(
			string i_ModelName,
			string i_LicenseNumber,
			eEnergyType i_EnergyType,
			float i_MaxAmountOfEnergy,
			float i_RemainingEnergyPercentage,
			Wheel[] i_Wheels)
		{
			this.m_ModelName = i_ModelName;
			this.m_LicenseNumber = i_LicenseNumber;
			this.m_EnergyType = i_EnergyType;
			this.m_MaxAmountOfEnergy = i_MaxAmountOfEnergy;
			this.m_RemainingEnergyPercentage = i_RemainingEnergyPercentage;
			this.m_Wheels = i_Wheels;
		}

		public string LicenseNumber
		{
			get { return this.m_LicenseNumber; }

			set { this.m_LicenseNumber = value; }
		}

		public eEnergyType EnergyType
		{
			get { return this.m_EnergyType; }

			set { this.m_EnergyType = value; }
		}

		public string GetEnergyUnits()
		{
			return m_EnergyType == eEnergyType.Battery ? "hours" : "liters";
		}

		public float GetRemainingEnergy()
		{
			return this.m_RemainingEnergyPercentage * this.m_MaxAmountOfEnergy / 100;
		}

		public void FillWheelsToMax()
		{
			for(int i = 0; i < m_Wheels.Length; i++)
			{
				m_Wheels[i].PumpFull();
			}
		}

		public void AddEnergy(float i_EnergyToAdd)
		{
			float percentageOfEnergyAfterAddition = (GetRemainingEnergy() + i_EnergyToAdd) / this.m_MaxAmountOfEnergy * 100;

			if (percentageOfEnergyAfterAddition > 100)
			{
				throw new ValueOutOfRangeException(0, m_MaxAmountOfEnergy, "Invalid amount to add for energy");
			}

			this.m_RemainingEnergyPercentage = percentageOfEnergyAfterAddition;
		}

		public virtual Dictionary<string, object> GetInfo()
		{
			return new Dictionary<string, object>()
				       {
					       { "Model Name", this.m_ModelName },
					       { "License Number", this.m_LicenseNumber },
					       { "Energy Type", this.m_EnergyType },
					       { "Max Amount Of Energy", string.Format("{0} {1}", this.m_MaxAmountOfEnergy, GetEnergyUnits()) },
					       { "Remaining Energy", string.Format("{0} {1}", GetRemainingEnergy(), GetEnergyUnits()) },
					       { "Remaining Energy Percentage", this.m_RemainingEnergyPercentage },
					       { "Amount Of Wheels", this.m_Wheels.Length },
					       { "Wheels Info", this.m_Wheels[0].GetWheelInfo() }
				       };
		}
	}
}
