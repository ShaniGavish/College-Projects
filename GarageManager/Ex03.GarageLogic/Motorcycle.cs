using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class Motorcycle : Vehicle
	{
		private eLicenseType m_LicenseType;
		private int m_EngineCapacity;

		public Motorcycle(
			string i_ModelName, 
			string i_LicenseNumber, 
			eEnergyType i_EnergyType, 
			float i_MaxAmountOfEnergy, 
			float i_RemainingEnergyPercentage, 
			Wheel[] i_Wheels, 
			eLicenseType i_LicenseType, 
			int i_EngineCapacity) 
			: base(
				i_ModelName, 
				i_LicenseNumber, 
				i_EnergyType, 
				i_MaxAmountOfEnergy, 
				i_RemainingEnergyPercentage, 
				i_Wheels)
		{
			this.m_LicenseType = i_LicenseType;
			this.m_EngineCapacity = i_EngineCapacity;
		}

		public override Dictionary<string, object> GetInfo()
		{
			Dictionary<string, object> motorcycleInfo = base.GetInfo();
			motorcycleInfo.Add("License Type", this.m_LicenseType);
			motorcycleInfo.Add("Engine Capacity", string.Format("{0} {1}", this.m_EngineCapacity, "Cc"));
			return motorcycleInfo;
		}
	}
}
