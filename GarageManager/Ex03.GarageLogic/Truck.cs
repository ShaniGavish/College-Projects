using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class Truck : Vehicle
	{
		private bool m_IsCarryingDangerousSubstances;
		private float m_MaxCarryingWeight;

		public Truck(
			string i_ModelName, 
			string i_LicenseNumber, 
			eEnergyType i_EnergyType, 
			float i_MaxAmountOfEnergy, 
			float i_RemainingEnergyPercentage, 
			Wheel[] i_Wheels, 
			bool i_IsCarryingDangerousSubstances, 
			float i_MaxCarryingWeight) 
			: base(
				i_ModelName, 
				i_LicenseNumber, 
				i_EnergyType, 
				i_MaxAmountOfEnergy, 
				i_RemainingEnergyPercentage, 
				i_Wheels)
		{
			this.m_IsCarryingDangerousSubstances = i_IsCarryingDangerousSubstances;
			this.m_MaxCarryingWeight = i_MaxCarryingWeight;
		}

		public override Dictionary<string, object> GetInfo()
		{
			Dictionary<string, object> truckInfo = base.GetInfo();
			truckInfo.Add("Is Carrying Dangerous Substances", this.m_IsCarryingDangerousSubstances);
			truckInfo.Add("Max Carrying Weight", this.m_MaxCarryingWeight);
			return truckInfo;
		}
	}
}
