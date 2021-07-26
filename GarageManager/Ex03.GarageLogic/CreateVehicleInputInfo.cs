using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class CreateVehicleInputInfo
	{
		private string m_FieldName;
		private string m_Description;
		
		public CreateVehicleInputInfo(string i_FieldName, string i_Description = null)
		{
			this.m_FieldName = i_FieldName;
			this.m_Description = i_Description;
		}

		public string FieldName
		{
			get { return this.m_FieldName; }
		}

		public string Description
		{
			get { return this.m_Description; }
		}
	}
}
