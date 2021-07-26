using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class Car : Vehicle
	{
		private int m_AmountOfDoors;
		private eCarColor m_Color;

		public Car(
			string i_ModelName, 
		           string i_LicenseNumber, 
		           eEnergyType i_EnergyType, 
		           float i_MaxAmountOfEnergy, 
		           float i_RemainingEnergyPercentage, 
		           Wheel[] i_Wheels, 
		           int i_AmountOfDoors, 
		           eCarColor i_Color) 
			: base(
				i_ModelName, 
				i_LicenseNumber, 
				i_EnergyType, 
				i_MaxAmountOfEnergy, 
				i_RemainingEnergyPercentage, 
				i_Wheels)
		{
			this.m_AmountOfDoors = i_AmountOfDoors;
			this.m_Color = i_Color;
		}

		public override Dictionary<string, object> GetInfo()
		{
			Dictionary<string, object> carInfo = base.GetInfo();
			carInfo.Add("Amount Of Doors", this.m_AmountOfDoors);
			carInfo.Add("Color", this.m_Color);
			return carInfo;
		}
	}
}
