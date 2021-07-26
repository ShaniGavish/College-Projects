using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class GarageManager
	{
		private Dictionary<string, GarageVehicleRecord> m_VehiclesRecords;

		private readonly eEnergyType[] r_FuelTypes =
			{
				eEnergyType.Octan95, eEnergyType.Octan96, eEnergyType.Octan98, eEnergyType.Soler
			};

		
		
		public GarageManager()
		{
			this.m_VehiclesRecords = new Dictionary<string, GarageVehicleRecord>();
		}

		public eEnergyType[] FuelTypes
		{
			get { return this.r_FuelTypes; }
		}

		public Dictionary<string, GarageVehicleRecord> VehiclesRecords
		{
			get { return this.m_VehiclesRecords; }
		}

		public void AddVehicle(string i_OwnersName, string i_OwnersPhone, Vehicle i_Vehicle)
		{
			GarageVehicleRecord newVehicleRecord = new GarageVehicleRecord(i_OwnersName, i_OwnersPhone, i_Vehicle);
			this.m_VehiclesRecords.Add(i_Vehicle.LicenseNumber, newVehicleRecord);
		}

		public bool IsVehicleExist(string i_LicenseNumber)
		{
			return m_VehiclesRecords.ContainsKey(i_LicenseNumber);
		}

		public void SetStatus(string i_LicenseNumber, eGarageVehicleStatus i_NewStatus)
		{
			m_VehiclesRecords[i_LicenseNumber].Status = i_NewStatus;
		}

		public List<string> GetLicenseNumbersByStatusFilter(eGarageVehicleStatus i_Status)
		{
			List<string> licenseNumbersArr = new List<string>();
			foreach (KeyValuePair<string, GarageVehicleRecord> vehiclesRecord in m_VehiclesRecords)
			{
				if(vehiclesRecord.Value.Status == i_Status)
				{
					licenseNumbersArr.Add(vehiclesRecord.Key);
				}
			}

			return licenseNumbersArr;
		}

		public List<string> GetAllLicenseNumbers()
		{
			return m_VehiclesRecords.Keys.ToList();
		}

		public void PumpWheelsToMax(string i_LicenseNumber)
		{
			m_VehiclesRecords[i_LicenseNumber].Vehicle.FillWheelsToMax();
		}

		public void ChargeBattery(string i_LicenseNumber, float i_AmountOfMinutesToCharge)
		{
			float amountOfHoursToCharge = i_AmountOfMinutesToCharge / 60;
			m_VehiclesRecords[i_LicenseNumber].Vehicle.AddEnergy(amountOfHoursToCharge);
		}

		public void AddFuel(string i_LicenseNumber, eEnergyType i_FuelType, float i_Amount)
		{
			if(m_VehiclesRecords[i_LicenseNumber].Vehicle.EnergyType != i_FuelType)
			{
				throw new ArgumentException("Invalid energy type");
			}

			m_VehiclesRecords[i_LicenseNumber].Vehicle.AddEnergy(i_Amount);
		}

		public virtual Dictionary<string, object> GetVehicleInfo(string i_LicenseNumber)
		{
			return m_VehiclesRecords[i_LicenseNumber].GetInfo();
		}
	}
}
