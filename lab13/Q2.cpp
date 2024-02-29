#include <iostream>
#include <vector>
using namespace std;

// Base class for entities with carbon footprint
class CarbonFootprintCal
{
public:
    virtual double getCarbonFootprint() const = 0;
    virtual void displayCarbonFootprint() const = 0;
    virtual ~CarbonFootprintCal() {}
};

// Building class
class Building : public CarbonFootprintCal
{
private:
    double energyConsumption;
    int numberOfOccupants;

public:
    Building(double energy, int occupants) : energyConsumption(energy), numberOfOccupants(occupants) {}

    double getCarbonFootprint() const override
    {
        // Example calculation using a conversion factor of 2 kg CO2 per kWh
        return energyConsumption / numberOfOccupants * 2;
    }
    void displayCarbonFootprint() const
    {
        cout << "Building Carbon Footprint: " << getCarbonFootprint() << " kg of CO2" << endl;
    }
};

// Car class
class Car : public CarbonFootprintCal
{
private:
    double fuelEfficiency; // liters per kilometer
protected:
    double distanceTraveled;

public:
    Car(double distance, double efficiency) : distanceTraveled(distance), fuelEfficiency(efficiency) {}

    void validateFuelEfficiency(double efficiency)
    {
        if (efficiency <= 0)
        {
            throw invalid_argument("Fuel efficiency cannot be negative or zero.");
        }
    }

    double getCarbonFootprint() const override
    {
        // Example calculation using a conversion factor of 8.74 kg CO2 per liter of gasoline
        return distanceTraveled / fuelEfficiency * 8.74;
    }

    void displayCarbonFootprint() const
    {
        cout << "Car Carbon Footprint: " << getCarbonFootprint() << " kg of CO2" << endl;
    }
};

// Electric Car class (inherits from Car)
class ElectricCar : public Car
{
private:
    double batteryCapacity; // kWh
    double chargeEfficiency;

public:
    ElectricCar(double distance, double efficiency, double capacity, double efficiencyFactor)
        : Car(distance, 0), batteryCapacity(capacity), chargeEfficiency(efficiencyFactor)
    {
        validateFuelEfficiency(efficiencyFactor); // Inherit validation from Car
    }

    double getCarbonFootprint() const override
    {
        // Example calculation assuming electricity generation emits 0.5 kg CO2 per kWh
        return distanceTraveled * batteryCapacity / (chargeEfficiency * 100) * 0.5;
    }

    void displayCarbonFootprint() const
    {
        cout << "Electric Car Carbon Footprint: " << getCarbonFootprint() << " kg of CO2" << endl;
    }
};

// Bicycle class
class Bicycle : public CarbonFootprintCal
{
private:
    double manufacturingEmissions; // kg CO2
public:
    Bicycle(double emissions) : manufacturingEmissions(emissions) {}

    double getCarbonFootprint() const override
    {
        return manufacturingEmissions;
    }

    void displayCarbonFootprint() const
    {
        cout << "Bicycle Carbon Footprint: " << getCarbonFootprint() << " kg of CO2" << endl;
    }
};

// Factory class
class Factory : public CarbonFootprintCal
{
private:
    int productionHours;
    double energyPerHour;
    double wastePerHour;
    double wasteConversionFactor; // kg CO2 per kg waste
public:
    Factory(int hours, double energy, double waste, double conversionFactor)
        : productionHours(hours), energyPerHour(energy), wastePerHour(waste), wasteConversionFactor(conversionFactor) {}

    double getCarbonFootprint() const override
    {
        // Example calculation including waste conversion
        return productionHours * (energyPerHour + wastePerHour * wasteConversionFactor);
    }

    void displayCarbonFootprint() const
    {
        cout << "Factory Carbon Footprint: " << getCarbonFootprint() << " kg of CO2" << endl;
    }
};

// Function to calculate total carbon footprint of an object collection
double getTotalFootprint(const vector<CarbonFootprintCal *> &objects)
{
    double total = 0;
    for (const CarbonFootprintCal *obj : objects)
    {
        total += obj->getCarbonFootprint();
    }
    return total;
}

// Function to display details of an object's carbon footprint

int main()
{
    // Create objects of different classes
    // and store them in a vector of CarbonFootprintCal pointers
    vector<CarbonFootprintCal *> objects;

    while (true)
    {
        cout << "Enter the energy consumption and number of occupants for a building: ";
        double energy;
        int occupants;

        // Check if input is valid (both non-negative)
        if (cin >> energy >> occupants && energy >= 0 && occupants >= 0)
        {
            // Valid input, break loop and create object
            objects.push_back(new Building(energy, occupants));
        }
        else
        {
            // Clear error state and input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Energy and occupants must be non-negative. Please try again." << endl;
            exit(0);
        }

        cout << "Enter the distance traveled and fuel efficiency for a car: ";
        double distance, efficiency;
        if (cin >> distance >> efficiency && distance >= 0 && efficiency > 0)
        {
            objects.push_back(new Car(distance, efficiency));
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Distance must be non-negative and fuel efficiency must be positive. Please try again." << endl;
            exit(0);
        }

        cout << "Enter the distance traveled, fuel efficiency, battery capacity, and charge efficiency for an electric car: ";
        double distanceElec, efficiencyElec, capacity, chargeEff;
        if (cin >> distanceElec >> efficiencyElec >> capacity >> chargeEff && distance >= 0 && efficiency > 0 && capacity > 0 && chargeEff > 0)
        {
            objects.push_back(new ElectricCar(distanceElec, efficiencyElec, capacity, chargeEff));
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Distance must be non-negative, fuel efficiency and battery capacity must be positive, and charge efficiency must be positive. Please try again." << endl;
            exit(0);
        }
    }

    // cout << "Enter the manufacturing emissions for a bicycle: ";
    // double emissions;
    // cin >> emissions;
    // objects.push_back(new Bicycle(emissions));

    // cout << "Enter the production hours, energy per hour, waste per hour, and waste conversion factor for a factory: ";
    // int hours;
    // double energyPerHour, wastePerHour, conversionFactor;
    // cin >> hours >> energyPerHour >> wastePerHour >> conversionFactor;
    // objects.push_back(new Factory(hours, energyPerHour, wastePerHour, conversionFactor));

    for (const auto &object : objects)
    {
        object->displayCarbonFootprint();
    }

    // Compute the cumulative carbon footprint of all objects
    double totalCarbonFootprint = getTotalFootprint(objects);

    // Display the results
    cout << "Cumulative Carbon Footprint: " << totalCarbonFootprint << " kg CO2" << endl;

    return 0;
}