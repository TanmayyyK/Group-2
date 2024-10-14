#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Flight
{
    int flightNumber;
    string source;
    string destination;
    string departureTime;
    string arrivalTime;
    int availableSeats;
};

struct Passenger
{
    string name;
    string contactInfo;
    string idProof;
    int bookedFlightNumber;
    int seatNumber;
};

class AirlineReservationSystem
{
private:
    vector<Flight> flights;
    vector<Passenger> passengers;

public:
    void addFlight(int flightNumber, string source, string destination, string departureTime, string arrivalTime, int seats)
    {
        Flight newFlight = {flightNumber, source, destination, departureTime, arrivalTime, seats};
        flights.push_back(newFlight);
        cout << "Flight added successfully!" << endl;
    }

    void viewFlights()
    {
        cout << "\nAvailable Flights:\n";
        for (const auto &flight : flights)
        {
            cout << "Flight Number: " << flight.flightNumber
                 << ", Source: " << flight.source
                 << ", Destination: " << flight.destination
                 << ", Departure: " << flight.departureTime
                 << ", Arrival: " << flight.arrivalTime
                 << ", Available Seats: " << flight.availableSeats << endl;
        }
    }

    void bookTicket(string name, string contactInfo, string idProof, int flightNumber)
    {
        for (auto &flight : flights)
        {
            if (flight.flightNumber == flightNumber && flight.availableSeats > 0)
            {
                Passenger newPassenger = {name, contactInfo, idProof, flightNumber, flight.availableSeats};
                passengers.push_back(newPassenger);
                flight.availableSeats--;
                cout << "Ticket booked successfully! Seat Number: " << newPassenger.seatNumber << endl;
                return;
            }
        }
        cout << "Sorry, no seats available on the selected flight or flight not found." << endl;
    }

    void cancelReservation(string name, int flightNumber)
    {
        for (size_t i = 0; i < passengers.size(); ++i)
        {
            if (passengers[i].name == name && passengers[i].bookedFlightNumber == flightNumber)
            {
                passengers.erase(passengers.begin() + i);
                for (auto &flight : flights)
                {
                    if (flight.flightNumber == flightNumber)
                    {
                        flight.availableSeats++;
                        cout << "Reservation canceled successfully!" << endl;
                        return;
                    }
                }
            }
        }
        cout << "Reservation not found." << endl;
    }

    void checkFlightStatus(int flightNumber)
    {
        for (const auto &flight : flights)
        {
            if (flight.flightNumber == flightNumber)
            {
                cout << "Flight Number: " << flight.flightNumber
                     << ", Available Seats: " << flight.availableSeats << endl;
                return;
            }
        }
        cout << "Flight not found." << endl;
    }
};

int main()
{
    AirlineReservationSystem system;
    int choice;

    while (true)
    {
        cout << "\nAirline Reservation System Menu:\n";
        cout << "1. Add Flight (Admin)\n";
        cout << "2. View Flights\n";
        cout << "3. Book a Ticket\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Check Flight Status (Admin)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int flightNumber, seats;
            string source, destination, departureTime, arrivalTime;
            cout << "Enter Flight Number: ";
            cin >> flightNumber;
            cout << "Enter Source: ";
            cin >> source;
            cout << "Enter Destination: ";
            cin >> destination;
            cout << "Enter Departure Time: ";
            cin >> departureTime;
            cout << "Enter Arrival Time: ";
            cin >> arrivalTime;
            cout << "Enter Number of Seats: ";
            cin >> seats;
            system.addFlight(flightNumber, source, destination, departureTime, arrivalTime, seats);
        }
        else if (choice == 2)
        {
            system.viewFlights();
        }
        else if (choice == 3)
        {
            string name, contactInfo, idProof;
            int flightNumber;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your contact info: ";
            cin >> contactInfo;
            cout << "Enter ID proof: ";
            cin >> idProof;
            cout << "Enter Flight Number: ";
            cin >> flightNumber;
            system.bookTicket(name, contactInfo, idProof, flightNumber);
        }
        else if (choice == 4)
        {
            string name;
            int flightNumber;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter Flight Number: ";
            cin >> flightNumber;
            system.cancelReservation(name, flightNumber);
        }
        else if (choice == 5)
        {
            int flightNumber;
            cout << "Enter Flight Number to check status: ";
            cin >> flightNumber;
            system.checkFlightStatus(flightNumber);
        }
        else if (choice == 6)
        {
            cout << "Exiting the system. Thank you!" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
