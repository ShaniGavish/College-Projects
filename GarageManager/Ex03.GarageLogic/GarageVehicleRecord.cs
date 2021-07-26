using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class GarageVehicleRecord
	{
		private string m_OwnersName;
		private string m_OwnersPhone;
		private Vehicle m_Vehicle;
		private eGarageVehicleStatus m_Status;

		public GarageVehicleRecord(string i_OwnersName, string i_OwnersPhone, Vehicle i_Vehicle)
		{
			this.m_OwnersName = i_OwnersName;
			this.m_OwnersPhone = i_OwnersPhone;
			this.m_Vehicle = i_Vehicle;
			this.m_Status = eGarageVehicleStatus.InRepair;
		}

		public Vehicle Vehicle
		{
			get { return this.m_Vehicle; }
		}

		public eGarageVehicleStatus Status
		{
			get { return this.m_Status; }
			set { this.m_Status = value; }
		}

		public Dictionary<string, object> GetInfo()
		{
			Dictionary<string, object> garageVehicleRecordInfo = m_Vehicle.GetInfo();
			garageVehicleRecordInfo.Add("Owners Name", this.m_OwnersName);
			garageVehicleRecordInfo.Add("Owners Phone", this.m_OwnersPhone);
			garageVehicleRecordInfo.Add("Status", this.m_Status);
			return garageVehicleRecordInfo;
		}
	}
}
