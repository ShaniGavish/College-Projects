using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.GarageLogic
{
	public class VehicleCreator
	{
		private const int k_MinAmountOfDoors = 2;
		private const int k_MaxAmountOfDoors = 5;
		private readonly Dictionary<eGarageVehiclesSupportedTypes, CreateVehicleInputInfo[]> r_TypeToInputValues =
			new Dictionary<eGarageVehiclesSupportedTypes, CreateVehicleInputInfo[]>() 
				{
					{ eGarageVehiclesSupportedTypes.ElectricMotorcycle,
						new CreateVehicleInputInfo[] { new CreateVehicleInputInfo("Model Name"), new CreateVehicleInputInfo("License Number"), new CreateVehicleInputInfo("Remaining Battery Percentage", "%"), new CreateVehicleInputInfo("Wheels Manufacturer"), new CreateVehicleInputInfo("Current Air Pressure"), new CreateVehicleInputInfo("License Type", getLicenseTypeOptionStringFormat()), new CreateVehicleInputInfo("Engine Capacity", "Cc") }
					},
					{ eGarageVehiclesSupportedTypes.OrdinaryMotorcycle,
						new CreateVehicleInputInfo[] { new CreateVehicleInputInfo("Model Name"), new CreateVehicleInputInfo("License Number"), new CreateVehicleInputInfo("Remaining Fuel Percentage", "%"), new CreateVehicleInputInfo("Wheels Manufacturer"), new CreateVehicleInputInfo("Current Air Pressure"), new CreateVehicleInputInfo("License Type", getLicenseTypeOptionStringFormat()), new CreateVehicleInputInfo("Engine Capacity", "Cc") }
					},
					{ eGarageVehiclesSupportedTypes.ElectricCar,
						new CreateVehicleInputInfo[] { new CreateVehicleInputInfo("Model Name"), new CreateVehicleInputInfo("License Number"), new CreateVehicleInputInfo("Remaining Battery Percentage", "%"), new CreateVehicleInputInfo("Wheels Manufacturer"), new CreateVehicleInputInfo("Current Air Pressure"), new CreateVehicleInputInfo("Amount Of Doors"), new CreateVehicleInputInfo("Color", getColorsOptionStringFormat()) }
					},
					{ eGarageVehiclesSupportedTypes.OrdinaryCar,
						new CreateVehicleInputInfo[] { new CreateVehicleInputInfo("Model Name"), new CreateVehicleInputInfo("License Number"), new CreateVehicleInputInfo("Remaining Fuel Percentage", "%"), new CreateVehicleInputInfo("Wheels Manufacturer"), new CreateVehicleInputInfo("Current Air Pressure"), new CreateVehicleInputInfo("Amount Of Doors"), new CreateVehicleInputInfo("Color", getColorsOptionStringFormat()) }
					},
					{ eGarageVehiclesSupportedTypes.Truck,
						new CreateVehicleInputInfo[] { new CreateVehicleInputInfo("Model Name"), new CreateVehicleInputInfo("License Number"), new CreateVehicleInputInfo("Remaining Fuel Percentage", "%"), new CreateVehicleInputInfo("Wheels Manufacturer"), new CreateVehicleInputInfo("Current Air Pressure"), new CreateVehicleInputInfo("Is Carrying Dangerous Substances", "True/False"), new CreateVehicleInputInfo("Max Carrying Weight") }
					},
				};

		public eGarageVehiclesSupportedTypes[] GetSupportedVehiclesTypes()
		{
			return this.r_TypeToInputValues.Keys.ToArray();
		}

		public CreateVehicleInputInfo[] GetInputFields(eGarageVehiclesSupportedTypes i_Type)
		{
			return this.r_TypeToInputValues[i_Type];
		}

		private static string getLicenseTypeOptionStringFormat()
		{
			string[] licenseTypes = System.Enum.GetNames(typeof(eLicenseType));
			string[] licenseTypesSFormat = new string[licenseTypes.Length];
			return string.Join(" ", licenseTypes);
		}

		private static string getColorsOptionStringFormat()
		{
			string[] colors = System.Enum.GetNames(typeof(eCarColor));
			string[] licenseTypesSFormat = new string[colors.Length];
			return string.Join(" ", colors);
		}

		public Vehicle CreateVehicle(eGarageVehiclesSupportedTypes i_Type, Dictionary<string, string> i_Input)
		{
			Vehicle vehicle = null;
			switch(i_Type)
			{
				case eGarageVehiclesSupportedTypes.ElectricCar:
					vehicle = createElectricCar(i_Input);
					break;

				case eGarageVehiclesSupportedTypes.OrdinaryCar:
					vehicle = createOrdinaryCar(i_Input);
					break;

				case eGarageVehiclesSupportedTypes.ElectricMotorcycle:
					vehicle = createElectricMotorcycle(i_Input);
					break;

				case eGarageVehiclesSupportedTypes.OrdinaryMotorcycle:
					vehicle = createOrdinaryMotorcycle(i_Input);
					break;

				case eGarageVehiclesSupportedTypes.Truck:
					vehicle = createTruck(i_Input);
					break;
				default:
					throw new ArgumentException("Vehicle type is not supported");
			}

			return vehicle;
		}

		private void extractVehicleInfoFromInput(
			Dictionary<string, string> i_Input,
			out string o_ModelName,
			out string o_LicenseNumber,
			out float o_CurrentAirPressure,
			float i_MaxAirPressure)
		{
			o_ModelName = i_Input["Model Name"];
			o_LicenseNumber = i_Input["License Number"];
			if (!float.TryParse(i_Input["Current Air Pressure"], out o_CurrentAirPressure))
			{
				throw new FormatException("Invalid value for air pressure");
			}

			if(o_CurrentAirPressure > i_MaxAirPressure)
			{
				throw new ValueOutOfRangeException(0, i_MaxAirPressure, "Invalid value for air pressure");
			}
		}

		private void extractCarInfoFromInput(
			Dictionary<string, string> i_Input,
			out int o_AmountOfDoors,
			out eCarColor o_Color)
		{
			if (!int.TryParse(i_Input["Amount Of Doors"], out o_AmountOfDoors))
			{
				throw new FormatException("Invalid value for amount of doors");
			}

			if (o_AmountOfDoors < k_MinAmountOfDoors || o_AmountOfDoors > k_MaxAmountOfDoors)
			{
				throw new ValueOutOfRangeException(k_MinAmountOfDoors, k_MaxAmountOfDoors, "Invalid value for amount of doors");
			}

			if (!Enum.TryParse(i_Input["Color"], out o_Color))
			{
				throw new FormatException("Invalid value for color");
			}
		}

		private void extractMotorcycleInfoFromInput(
			Dictionary<string, string> i_Input,
			out eLicenseType o_LicenseType,
			out int o_EngineCapacity)
		{
			if (!Enum.TryParse(i_Input["License Type"], out o_LicenseType))
			{
				throw new FormatException("Invalid value for license type");
			}

			if (!int.TryParse(i_Input["Engine Capacity"], out o_EngineCapacity))
			{
				throw new FormatException("Invalid value for engine capacity");
			}

			if(o_EngineCapacity < 1)
			{
				throw new ValueOutOfRangeException(1, int.MaxValue, "Invalid value for engine capacity");
			}
		}

		private void extractTruckInfoFromInput(
			Dictionary<string, string> i_Input,
			out bool o_IsCarryingDangerousSubstances,
			out float o_MaxCarryingWeight)
		{
			if (!bool.TryParse(i_Input["Is Carrying Dangerous Substances"], out o_IsCarryingDangerousSubstances))
			{
				throw new FormatException("Invalid value for is carrying dangerous substances (true/false)");
			}

			if (!float.TryParse(i_Input["Max Carrying Weight"], out o_MaxCarryingWeight))
			{
				throw new ValueOutOfRangeException(0, float.MaxValue, "Invalid value for max carrying weight");
			}
		}

		private void extractElectricVehicleInfoFromInput(
			Dictionary<string, string> i_Input,
			out float o_RemainingBatteryPercentage)
		{
			if (!float.TryParse(i_Input["Remaining Battery Percentage"], out o_RemainingBatteryPercentage))
			{
				throw new FormatException("Invalid value for remaining battery percentage");
			}

			if(o_RemainingBatteryPercentage > 100)
			{
				throw new ValueOutOfRangeException(0, 100, "Invalid value for remaining battery percentage");
			}
		}

		private void extractOrdinaryVehicleInfoFromInput(
			Dictionary<string, string> i_Input,
			out float o_RemainingFuelPercentage)
		{
			if (!float.TryParse(i_Input["Remaining Fuel Percentage"], out o_RemainingFuelPercentage))
			{
				throw new FormatException("Invalid value for remaining fuel percentage");
			}

			if(o_RemainingFuelPercentage > 100)
			{
				throw new ValueOutOfRangeException(0, float.MaxValue, "Invalid value for remaining fuel percentage");
			}
		}

		private Vehicle createElectricCar(Dictionary<string, string> i_Input)
		{
			extractVehicleInfoFromInput(i_Input, out string modelName, out string licenseNumber, out float currentAirPressure, 32);
			extractElectricVehicleInfoFromInput(i_Input, out float remainingBatteryPercentage);
			extractCarInfoFromInput(i_Input, out int amountOfDoors, out eCarColor color);

			Wheel[] wheels = createWheels(4, i_Input["Wheels Manufacturer"], 32, currentAirPressure);
			return new Car(modelName, licenseNumber, eEnergyType.Battery, (float)3.2, remainingBatteryPercentage, wheels, amountOfDoors, color);
		}

		private Vehicle createOrdinaryCar(Dictionary<string, string> i_Input)
		{
			extractVehicleInfoFromInput(i_Input, out string modelName, out string licenseNumber, out float currentAirPressure, 32);
			extractOrdinaryVehicleInfoFromInput(i_Input, out float remainingFuelPercentage);
			extractCarInfoFromInput(i_Input, out int amountOfDoors, out eCarColor color);

			Wheel[] wheels = createWheels(4, i_Input["Wheels Manufacturer"], 32, currentAirPressure);
			return new Car(modelName, licenseNumber, eEnergyType.Octan95, 45, remainingFuelPercentage, wheels, amountOfDoors, color);
		}

		private Vehicle createElectricMotorcycle(Dictionary<string, string> i_Input)
		{
			extractVehicleInfoFromInput(i_Input, out string modelName, out string licenseNumber, out float currentAirPressure, 30);
			extractElectricVehicleInfoFromInput(i_Input, out float remainingBatteryPercentage);
			extractMotorcycleInfoFromInput(i_Input, out eLicenseType licenseType, out int engineCapacity);

			Wheel[] wheels = createWheels(2, i_Input["Wheels Manufacturer"], 30, currentAirPressure);
			return new Motorcycle(modelName, licenseNumber, eEnergyType.Battery, (float)1.8, remainingBatteryPercentage, wheels, licenseType, engineCapacity);
		}

		private Vehicle createOrdinaryMotorcycle(Dictionary<string, string> i_Input)
		{
			extractVehicleInfoFromInput(i_Input, out string modelName, out string licenseNumber, out float currentAirPressure, 30);
			extractOrdinaryVehicleInfoFromInput(i_Input, out float remainingFuelPercentage);
			extractMotorcycleInfoFromInput(i_Input, out eLicenseType licenseType, out int engineCapacity);

			Wheel[] wheels = createWheels(2, i_Input["Wheels Manufacturer"], 30, currentAirPressure);
			return new Motorcycle(modelName, licenseNumber, eEnergyType.Octan98, 6, remainingFuelPercentage, wheels, licenseType, engineCapacity);
		}

		private Vehicle createTruck(Dictionary<string, string> i_Input)
		{
			extractVehicleInfoFromInput(i_Input, out string modelName, out string licenseNumber, out float currentAirPressure, 26);
			extractOrdinaryVehicleInfoFromInput(i_Input, out float remainingFuelPercentage);
			extractTruckInfoFromInput(i_Input, out bool isCarryingDangerousSubstances, out float maxCarryingWeight);

			Wheel[] wheels = createWheels(16, i_Input["Wheels Manufacturer"], 26, currentAirPressure);
			return new Truck(modelName, licenseNumber, eEnergyType.Soler, 120, remainingFuelPercentage, wheels, isCarryingDangerousSubstances, maxCarryingWeight);
		}

		private Wheel[] createWheels(int i_AmountOfWheels, string i_ManufacturerName, float i_MaxAirPressure, float i_CurrentAirPressure)
		{
			Wheel[] wheels = new Wheel[i_AmountOfWheels];
			for(int i = 0; i < i_AmountOfWheels; i++)
			{
				wheels[i] = new Wheel(i_ManufacturerName, i_MaxAirPressure, i_CurrentAirPressure);
			}

			return wheels;
		}
	}
}
