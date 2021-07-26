using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Text;
using System.Threading.Tasks;
using Ex03.GarageLogic;

namespace Ex03.ConsoleUI
{
	public class UI
	{
		private readonly VehicleCreator r_VehicleCreator;
		private readonly GarageManager r_GarageManager;

		public UI(VehicleCreator i_VehicleCreator, GarageManager i_GarageManager)
		{
			this.r_VehicleCreator = i_VehicleCreator;
			this.r_GarageManager = i_GarageManager;
		}

		public void DisplayStartMsg()
		{
			StringBuilder startSb = new StringBuilder("**************************");
			startSb.AppendLine();
			startSb.AppendLine("Welcome to Garage Manager");
			startSb.AppendLine("**************************");
			Console.WriteLine(startSb);
		}

		public void HandleMenu()
		{
			do
			{
				DisplayStartMsg();
				DisplayMenu();
				try
				{
					GetMenuChoiceUserInput(out int userChoice);
					eOptionMenu option = (eOptionMenu)userChoice;
					switch(option)
					{
						case eOptionMenu.RegisterNewVehicle:
							RegisterNewVehicleToGarage();
							break;
						case eOptionMenu.DisplayVehicleLicensesNumbers:
							DisplayListOfVehicleLicenseNumbers();
							break;
						case eOptionMenu.ChangeVehicleStatus:
							ChangeVehicleStatus();
							break;
						case eOptionMenu.PumpFullWheels:
							PumpWheelsToMax();
							break;
						case eOptionMenu.RefuelVehicle:
							RefuelAVehicle();
							break;
						case eOptionMenu.ChargeBattery:
							ChargeBatteryInElectricVehicle();
							break;
						case eOptionMenu.DisplayVehicleInfo:
							DisplayVehicleInfo();
							break;
						case eOptionMenu.Exit:
							{
								Console.Clear();
								Console.WriteLine("ByeBye...");
								System.Environment.Exit(0);
								return;
							}
					}
				}
				catch(Exception e)
				{
					Console.WriteLine(e.Message);
				}

				Console.WriteLine("Press enter to return to menu");
				Console.ReadLine();
				Console.Clear();
			}
			while(true);
		}

		public void DisplayMenu()
		{
			StringBuilder menuSb = new StringBuilder("Please choose an option: ");
			menuSb.AppendLine();
			menuSb.AppendLine("1. Register new vehicle");
			menuSb.AppendLine("2. Display List of vehicle license numbers");
			menuSb.AppendLine("3. Change vehicle status");
			menuSb.AppendLine("4. Pump Wheels To Max");
			menuSb.AppendLine("5. Refuel a vehicle (powered by fuel)");
			menuSb.AppendLine("6. Charge an electric vehicle");
			menuSb.AppendLine("7. Display Vehicle information");
			menuSb.AppendLine("0. Exit");
			Console.WriteLine(menuSb);
		}

		public void GetMenuChoiceUserInput(out int o_UserChoice)
		{
			string userInput = Console.ReadLine();
			ValidateChoiceMenuUserInput(userInput, out o_UserChoice);
		}

		public void ValidateChoiceMenuUserInput(string i_UserInput, out int o_UserChoice)
		{
			int totalNumberOfMenuOptions = Enum.GetNames(typeof(eOptionMenu)).Length - 1;
			if(!int.TryParse(i_UserInput, out o_UserChoice))
			{
				throw new FormatException("Invalid choice User Input");
			}

			if(o_UserChoice < 0 || o_UserChoice > totalNumberOfMenuOptions)
			{
				throw new ValueOutOfRangeException(0, totalNumberOfMenuOptions, "Invalid User Input for option");
			}
		}

		public void RegisterNewVehicleToGarage()
		{
			Console.Write("Please Enter license number:");
			string licenseNumber = Console.ReadLine();
			if(r_GarageManager.IsVehicleExist(licenseNumber))
			{
				Console.WriteLine("Vehicle is already exist, the status changed to 'Repair'");
				r_GarageManager.SetStatus(licenseNumber, eGarageVehicleStatus.InRepair);
			}
			else
			{
				Console.WriteLine("License Number is not Exist, Let's register new Vehicle:");
				Vehicle vehicle = CreateNewVehicle();
				GetOwnersInformation(out string ownersName, out string ownersPhone);
				r_GarageManager.AddVehicle(ownersName, ownersPhone, vehicle);
				Console.WriteLine("Vehicle added successfully");
			}
		}

		public void GetOwnersInformation(out string o_OwnersName, out string o_OwnersPhone)
		{
			Console.Write("Owners Name: ");
			o_OwnersName = Console.ReadLine();
			Console.Write("Owners Phone: ");
			o_OwnersPhone = Console.ReadLine();
		}

		public Vehicle CreateNewVehicle()
		{
			getUserInputForCreateNewVehicle(
				out eGarageVehiclesSupportedTypes vehicleType,
				out Dictionary<string, string> newVehicleValues);
			Vehicle newVehicle = r_VehicleCreator.CreateVehicle(vehicleType, newVehicleValues);
			return newVehicle;
		}

		private void getUserInputForCreateNewVehicle(
			out eGarageVehiclesSupportedTypes o_VehicleType,
			out Dictionary<string, string> o_NewVehicleValues)
		{
			eGarageVehiclesSupportedTypes[] supportedTypes = r_VehicleCreator.GetSupportedVehiclesTypes();
			displaySupportedVehicleTypes(supportedTypes);
			int.TryParse(Console.ReadLine(), out int userChoice);
			o_VehicleType = supportedTypes[userChoice - 1];
			CreateVehicleInputInfo[] requiredInputFields = r_VehicleCreator.GetInputFields(o_VehicleType);
			o_NewVehicleValues = new Dictionary<string, string>();
			foreach (CreateVehicleInputInfo inputField in requiredInputFields)
			{
				StringBuilder sb = new StringBuilder("Enter ");
				sb.Append(inputField.FieldName);
				if(inputField.Description != null)
				{
					sb.AppendFormat(" ({0})", inputField.Description);
				}

				sb.Append(":");
				Console.WriteLine(sb);
				string userInput = Console.ReadLine();
				o_NewVehicleValues.Add(inputField.FieldName, userInput);
			}
		}

		private void displaySupportedVehicleTypes(eGarageVehiclesSupportedTypes[] i_SupportedTypes)
		{
			StringBuilder supportedVehicleTypesSb = new StringBuilder("Choose Vehicle type:");
			supportedVehicleTypesSb.AppendLine();
			for (int i = 0; i < i_SupportedTypes.Length; i++)
			{
				supportedVehicleTypesSb.AppendLine(string.Format("{0}.{1}", i + 1, i_SupportedTypes[i]));
			}

			Console.WriteLine(supportedVehicleTypesSb);
		}

		public void DisplayListOfVehicleLicenseNumbers()
		{
			string[] filterStatusEnumArray = Enum.GetNames(typeof(eGarageVehicleStatus));
			getUserInputForFilterStatusChoice(out int filterStatusChoiceInput, filterStatusEnumArray);
			List<string> licenseNumbers = (filterStatusChoiceInput == filterStatusEnumArray.Length + 1)
				                              ? r_GarageManager.GetAllLicenseNumbers()
				                              : r_GarageManager.GetLicenseNumbersByStatusFilter(
					                              (eGarageVehicleStatus)filterStatusChoiceInput);
			if(licenseNumbers.Count == 0)
			{
				throw new ArgumentException("There are no results for the filter status requested");
			}

			printListOfVehicleLicenseNumbers(licenseNumbers);
		}

		private void getUserInputForFilterStatusChoice(
			out int o_FilterStatusChoiceInput,
			string[] i_FilterStatusEnumArray)
		{
			displayFilterStatusChoiceOptions(i_FilterStatusEnumArray);
			string userInput = Console.ReadLine();
			validateUserInputForFilterStatusChoice(userInput, out o_FilterStatusChoiceInput, i_FilterStatusEnumArray);
		}

		private void displayFilterStatusChoiceOptions(string[] i_FilterStatusEnumArray)
		{
			int i;
			StringBuilder filterStatusSb = new StringBuilder("Choose Filter Status:");
			filterStatusSb.AppendLine();
			for(i = 0; i < i_FilterStatusEnumArray.Length; i++)
			{
				filterStatusSb.AppendLine(string.Format("{0}.{1}", i + 1, i_FilterStatusEnumArray[i]));
			}

			filterStatusSb.AppendLine(string.Format("{0}.{1}", i + 1, "Any"));
			Console.WriteLine(filterStatusSb);
		}

		private void validateUserInputForFilterStatusChoice(
			string i_UserInput,
			out int o_FilterstatusChoice,
			string[] i_FilterStatusEnumArray)
		{
			if(!int.TryParse(i_UserInput, out o_FilterstatusChoice))
			{
				throw new FormatException("Invalid user Input for filter status");
			}

			if(o_FilterstatusChoice < 1 || o_FilterstatusChoice > i_FilterStatusEnumArray.Length + 1)
			{
				throw new ValueOutOfRangeException(
					1,
					i_FilterStatusEnumArray.Length + 1,
					"Invalid user Input for filter status");
			}
		}

		private void printListOfVehicleLicenseNumbers(List<string> i_LicenseNumbersArr)
		{
			StringBuilder licenseNumSb = new StringBuilder();
			foreach(string licenseNum in i_LicenseNumbersArr)
			{
				licenseNumSb.AppendLine(licenseNum);
			}

			Console.WriteLine(licenseNumSb);
		}

		public void ChangeVehicleStatus()
		{
			getUserInputForChangeVehicleStatus(out string licenseNumber, out eGarageVehicleStatus newStatus);
			r_GarageManager.SetStatus(licenseNumber, newStatus);
			Console.WriteLine("status changes successfully");
		}

		private void getUserInputForChangeVehicleStatus(
			out string o_LicenseNumber,
			out eGarageVehicleStatus o_NewStatus)
		{
			Console.Write("Please Enter License Number: ");
			o_LicenseNumber = Console.ReadLine();
			displayChangeVehicleStatusOptions();
			string statusChoiceUi = Console.ReadLine();
			validateUserInputForChangeVehicleStatus(o_LicenseNumber, statusChoiceUi, out int statusChoice);
			o_NewStatus = (eGarageVehicleStatus)statusChoice;
		}

		private void displayChangeVehicleStatusOptions()
		{
			StringBuilder vehicleStatusSb = new StringBuilder("Choose Status:");
			vehicleStatusSb.AppendLine();
			string[] vehicleStatusEnumArray = Enum.GetNames(typeof(eGarageVehicleStatus));
			for(int i = 0; i < vehicleStatusEnumArray.Length; i++)
			{
				vehicleStatusSb.AppendLine(string.Format("{0}.{1}", i + 1, vehicleStatusEnumArray[i]));
			}

			Console.WriteLine(vehicleStatusSb);
		}

		private void validateUserInputForChangeVehicleStatus(
			string i_LicenseNumber,
			string i_StatusChoiceUI,
			out int o_StatusChoice)
		{
			int totalItemsInEnumStatus = Enum.GetNames(typeof(eGarageVehicleStatus)).Length;
			if(!r_GarageManager.IsVehicleExist(i_LicenseNumber))
			{
				throw new ArgumentException("License Number is not exists");
			}

			if(!int.TryParse(i_StatusChoiceUI, out o_StatusChoice))
			{
				throw new FormatException("Invalid User Input for Status");
			}

			if(o_StatusChoice < 1 || o_StatusChoice > totalItemsInEnumStatus)
			{
				throw new ValueOutOfRangeException(1, totalItemsInEnumStatus, "Invalid User Input");
			}
		}

		public void PumpWheelsToMax()
		{
			getUserInputForPumpWheelsToMax(out string licenseNumber);
			r_GarageManager.PumpWheelsToMax(licenseNumber);
			Console.WriteLine("Wheels pumped To Max successfully");
		}

		private void getUserInputForPumpWheelsToMax(out string o_LicenseNumber)
		{
			Console.Write("Please Enter License Number: ");
			o_LicenseNumber = Console.ReadLine();
			validateUserInputForPumpWheelsToMax(o_LicenseNumber);
		}

		private void validateUserInputForPumpWheelsToMax(string i_LicenseNumber)
		{
			if(!r_GarageManager.IsVehicleExist(i_LicenseNumber))
			{
				throw new ArgumentException("License Number is not exists");
			}
		}

		public void RefuelAVehicle()
		{
			getUserInputForRefuelAVehicle(out string licenseNumber, out eEnergyType fuelType, out float amountToFuel);
			r_GarageManager.AddFuel(licenseNumber, fuelType, amountToFuel);
			Console.WriteLine("Vehicle will be Refueled successfully");
		}

		private void getUserInputForRefuelAVehicle(
			out string o_LicenseNumber,
			out eEnergyType o_FuelType,
			out float o_AmountToFuel)
		{
			Console.Write("Please Enter License Number: ");
			o_LicenseNumber = Console.ReadLine();
			displayFuelTypes();
			string fuelTypeChoiceUi = Console.ReadLine();
			Console.Write("Please Enter amount to fuel: ");
			string amountToFuelChoiceUi = Console.ReadLine();
			validateUserInputForRefuelAVehicle(
				o_LicenseNumber,
				fuelTypeChoiceUi,
				out int fuelTypeChoice,
				amountToFuelChoiceUi,
				out o_AmountToFuel);
			o_FuelType = (eEnergyType)fuelTypeChoice;
		}

		private void displayFuelTypes()
		{
			StringBuilder fuelTypesSb = new StringBuilder("Choose Fuel Type:");
			fuelTypesSb.AppendLine();
			eEnergyType[] fuelTypeEnumArray = r_GarageManager.FuelTypes;
			for(int i = 0; i < fuelTypeEnumArray.Length; i++)
			{
				fuelTypesSb.AppendLine(string.Format("{0}.{1}", i + 1, fuelTypeEnumArray[i]));
			}

			Console.WriteLine(fuelTypesSb);
		}

		private void validateUserInputForRefuelAVehicle(
			string i_LicenseNumber,
			string i_FuelTypeChoiceUI,
			out int o_FuelTypeChoice,
			string i_AmountToFuelUI,
			out float o_AmountToFuel)
		{
			int totalItemsInEnumFuelTypes = r_GarageManager.FuelTypes.Length;
			if(!r_GarageManager.IsVehicleExist(i_LicenseNumber))
			{
				throw new ArgumentException("License Number is not exists");
			}

			if(r_GarageManager.VehiclesRecords[i_LicenseNumber].Vehicle.EnergyType == eEnergyType.Battery)
			{
				throw new ArgumentException("Invalid refueling operation (Electric vehicle)");
			}

			if(!int.TryParse(i_FuelTypeChoiceUI, out o_FuelTypeChoice))
			{
				throw new FormatException("Invalid User Input for fuel type");
			}

			if(o_FuelTypeChoice < 1 || o_FuelTypeChoice > totalItemsInEnumFuelTypes)
			{
				throw new ValueOutOfRangeException(1, totalItemsInEnumFuelTypes, "Invalid User Input for fuel type");
			}

			if(!float.TryParse(i_AmountToFuelUI, out o_AmountToFuel))
			{
				throw new FormatException("Invalid User Input for amount to fuel");
			}
		}

		public void ChargeBatteryInElectricVehicle()
		{
			getUserInputForChargeBattery(out string licenseNumber, out float amountOfMinutesToCharge);
			r_GarageManager.ChargeBattery(licenseNumber, amountOfMinutesToCharge);
			Console.WriteLine("Battery will be charged successfully");
		}

		private void getUserInputForChargeBattery(out string o_LicenseNumber, out float o_AmountOfMinutesToCharge)
		{
			Console.Write("Please Enter License Number: ");
			o_LicenseNumber = Console.ReadLine();
			Console.Write("Please Enter amount of minutes to charge: ");
			string amountOfMinutesToChargeUi = Console.ReadLine();
			validateUserInputForChargeBattery(o_LicenseNumber, amountOfMinutesToChargeUi, out o_AmountOfMinutesToCharge);
		}

		private void validateUserInputForChargeBattery(
			string i_LicenseNumber,
			string i_AmountOfMinutesToChargeUi,
			out float o_AmountOfMinutesToCharge)
		{
			if(!r_GarageManager.IsVehicleExist(i_LicenseNumber))
			{
				throw new ArgumentException("License Number is not exists");
			}

			if(r_GarageManager.VehiclesRecords[i_LicenseNumber].Vehicle.EnergyType != eEnergyType.Battery)
			{
				throw new ArgumentException("Invalid charge battery operation (vehicle powered by fuel)");
			}

			if(!float.TryParse(i_AmountOfMinutesToChargeUi, out o_AmountOfMinutesToCharge))
			{
				throw new FormatException("Invalid User Input for amount to charge");
			}
		}

		public void DisplayVehicleInfo()
		{
			StringBuilder vehicleInfoSb = new StringBuilder();
			getUserInputForDisplayVehicleInfo(out string licenseNumber);
			Dictionary<string, object> vehicleRecordInfo = r_GarageManager.GetVehicleInfo(licenseNumber);
			foreach (KeyValuePair<string, object> kvp in vehicleRecordInfo)
			{
				if(kvp.Key == "Wheels Info")
				{
					vehicleInfoSb.AppendLine("Wheels info:");
					foreach(KeyValuePair<string, object> wheelsKvp in (Dictionary<string, object>)kvp.Value)
					{
						vehicleInfoSb.AppendLine(string.Format("	{0}: {1}", wheelsKvp.Key, wheelsKvp.Value));
					}
				}
				else
				{
					vehicleInfoSb.AppendLine(string.Format("{0}: {1}", kvp.Key, kvp.Value));
				}
			}

			Console.WriteLine(vehicleInfoSb);
		}

		private void getUserInputForDisplayVehicleInfo(out string o_LicenseNumber)
		{
			Console.Write("Please Enter License Number: ");
			o_LicenseNumber = Console.ReadLine();
			if (!r_GarageManager.IsVehicleExist(o_LicenseNumber))
			{
				throw new ArgumentException("License Number is not exists");
			}
		}
	}
}
