using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ex03.GarageLogic;

namespace Ex03.ConsoleUI
{
	public class Program
	{
		public static void Main()
		{
			GarageManager garageManager = new GarageManager();
			VehicleCreator vehicleCreator = new VehicleCreator();
			UI ui = new UI(vehicleCreator, garageManager);
			ui.HandleMenu();
		}
	}
}
