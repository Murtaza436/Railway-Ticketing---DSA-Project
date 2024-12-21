#include <iostream>  // For input/output
#include <string>    // For strings
#include <sstream>   // For stringstream (if used)
#include <fstream>   // For file operations
#include <ctime>     // For time functions
#include <vector>    // For vectors in trainRoutes
#include <map>       // For maps in trainRoutes
#include <algorithm> // For sort function (if needed)
#include <cstdlib>   // For system("cls"), rand(), and exit()
#include <Windows.h> // For Sleep()

using namespace std;
int main();

map<string, vector<string>> trainRoutes;

struct node
{
    int ticketID;
    string Name, Age, NIC, Contact, BookedClass, BookedTName, BookedTID, BookedDest, BookedSource, BookedDate, DeptTime, ArrTime, BookedSeatNum;
    float Price;
    node *next;
};

struct trains
{
    string TName, TID, TDest, TSource, TDate, arriveTime, departTime, TClasses;
    int TSeats;
};

struct TrainBST
{
    trains data;
    TrainBST *left;
    TrainBST *right;
};
TrainBST *trainRoot = NULL;

struct SeatRecord
{
    string RowA;
    string RowB;
    string RowC;
};

node *head = NULL;
node *tail = NULL;

string Name, Age, NIC, Contact, Dest, Source, SeatNum, Class, TID, Date, ATime, DTime, TName;
bool trainCheck = false;
float Price;
string BookedID;
int currentID;
trains availTrains[10];
int noOfTrains = 5;

void Payment()
{
    string cc, cvv, dob, payChoice;
    string accNum, accHolderFName, accHolderLName;
    cout << endl
         << endl;
    cout << "\n\n\t\t\t\t\t===============PAYMENT DETAILS===============" << endl;
    cout << "\t\t\t\t\tChoose Payment Method. \n";
    cout << "\t\t\t\t\t1. JazzCash. \n";
    cout << "\t\t\t\t\t2. EasyPaisa. \n";
    cout << "\t\t\t\t\t3. Credit/Debit Card. \n";
    cout << "\n\n\t\t\t\t\tEnter Choice (1-3): ";
    cin >> payChoice;

    if (payChoice == "1")
    {
        while (true)
        {
            cout << "\n\n\t\t\t\t\tEnter JazzCash Mobile Account Number: ";
            cin >> accNum;
            if (accNum.length() != 11)
            {
                cout << endl;
                cout << "\n\n\t\t\t\t\tEnter a Valid 11 Digit Mobile Phone Number!" << endl
                     << endl;
            }
            else
            {
                break; // Valid input, exit the loop
            }
        }

        cout << "\t\t\t\t\tEnter Account Holder's First Name: ";
        cin >> accHolderFName;
        cout << "\t\t\t\t\tEnter Account Holder's Last Name: ";
        cin >> accHolderLName;
    }
    else if (payChoice == "2")
    {
        cout << "\n\n\t\t\t\t\tEnter EasyPaisa Mobile Account Number: ";
        cin >> accNum;
        cout << "\n\n\t\t\t\t\tEnter Account Holder's First Name: ";
        cin >> accHolderFName;
        cout << "\n\n\t\t\t\t\tEnter Account Holder's Last Name: ";
        cin >> accHolderLName;
    }
    else if (payChoice == "3")
    {
        while (true)
        {
            cout << "\n\n\t\t\t\t\tEnter Credit/Debit Card Number (16 digits): ";
            cin >> cc;
            if (cc.length() != 16)
            {
                cout << "\n\n\t\t\t\t\tCC number must have a length of 16 only! \n";
            }
            else
            {
                break; // Valid input, exit the loop
            }
        }

        while (true)
        {
            cout << "\n\n\t\t\t\t\tEnter CVV (3 digits): ";
            cin >> cvv;
            if (cvv.length() != 3)
            {
                cout << "\n\n\t\t\t\t\tCVV number must have a length of 3 only! \n";
            }
            else
            {
                break; // Valid input, exit the loop
            }
        }

        cout << "\n\n\t\t\t\t\tEnter Date Of Expiry(DD/MM/YYYY): ";
        cin >> dob;
    }
    else
    {
        cout << "\t\t\t\t\tInvalid Choice. Please try again. \n";
    }
    cout << "\n\n\t\t\t\t\t";
}

TrainBST *insertTrain(TrainBST *root, trains t)
{
    if (!root)
    {
        TrainBST *newNode = new TrainBST();
        newNode->data = t;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (t.TName < root->data.TName)
        root->left = insertTrain(root->left, t);
    else
        root->right = insertTrain(root->right, t);
    return root;
}

void searchTrainByName(TrainBST *root, string name)
{
    if (!root)
    {
        cout << "Train not found.\n";
        return;
    }
    if (root->data.TName == name)
    {
        cout << "Train Found:\n"
             << "Name: " << root->data.TName << "\nID: " << root->data.TID << endl;
        return;
    }
    if (name < root->data.TName)
        searchTrainByName(root->left, name);
    else
        searchTrainByName(root->right, name);
}
void saveTicketToFile(node *ticket)
{
    ofstream outFile("Tickets.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << ticket->ticketID << "," << ticket->Name << "," << ticket->Age << ","
                << ticket->NIC << "," << ticket->Contact << ","
                << ticket->BookedTName << "," << ticket->BookedTID << ","
                << ticket->BookedSource << "," << ticket->BookedDest << ","
                << ticket->BookedDate << "," << ticket->DeptTime << ","
                << ticket->ArrTime << "," << ticket->BookedSeatNum << ","
                << ticket->Price << "," << ticket->BookedClass << "\n";

        outFile.close();
        cout << "Debug: Ticket saved to file.\n";
    }
    else
    {
        cout << "Error: Unable to save ticket to file.\n";
    }
}

string SeatChoose()
{
    fstream Seat;
    int count = 0;
    string line;
    SeatRecord Seats[10];
    Seat.open("Seat_Details.txt");
    while (getline(Seat, line))
    {
        count++;
    }
    Seat.close();
    Seat.open("Seat_Details.txt");
    for (int j = 0; j < count; j++)
    {
        string line1;
        getline(Seat, line1);
        size_t delimit = line1.find('-');
        Seats[j].RowA = line1.substr(0, delimit);
        size_t nextDelimit = line1.find('-', delimit + 1);
        Seats[j].RowB = line1.substr(delimit + 1, nextDelimit - delimit - 1);
        Seats[j].RowC = line1.substr(nextDelimit + 1);
    }
    Seat.close();

    string RowName, SeatNum, FinalSeatNum;
    bool Flag = false;
    cout << "\n\n\t\t\t\t\t\t\tA" << "\t" << " B" << "\t" << " C" << "\t\n";
    for (int i = 0; i < 10; i++)
    {
        cout << "\n\n\t\t\t\t\t\t\t" << Seats[i].RowA << "\t" << Seats[i].RowB << "\t" << Seats[i].RowC << "\t\n";
    }

    cout << "\n\n\t\t\t\t\t\t  ======================================\n";

    while (true)
    {
        cout << "\n\n\t\t\t\t\tEnter the row name that you chose: ";
        cin >> RowName;
        if (RowName != "A" && RowName != "B" && RowName != "C")
        {
            cout << "\n\n\t\t\t\t\tInvalid row, please try again. ";
        }
        else
            break;
    }

    while (true)
    {
        cout << "\n\n\t\t\t\t\tEnter the seat number that you chose: ";
        cin >> SeatNum;
        if (SeatNum == "XX")
        {
            cout << "\n\n\t\t\t\t\tInvalid seat, please try again! \n";
            continue;
        }

        for (int i = 0; i < 10; i++)
        {
            if (RowName == "A" && SeatNum == Seats[i].RowA)
            {
                Seats[i].RowA = "XX"; // Mark seat as reserved
                Flag = true;
                cout << "Debug: Reserved Seat A" << SeatNum << endl;
            }
            else if (RowName == "B" && SeatNum == Seats[i].RowB)
            {
                Seats[i].RowB = "XX";
                Flag = true;
                cout << "Debug: Reserved Seat B" << SeatNum << endl;
            }
            else if (RowName == "C" && SeatNum == Seats[i].RowC)
            {
                Seats[i].RowC = "XX";
                Flag = true;
                cout << "Debug: Reserved Seat C" << SeatNum << endl;
            }
        }

        if (Flag)
            break;
        else
            cout << "\n\n\t\t\t\t\tSeat number not found, please try again. \n";
    }

    FinalSeatNum = RowName + SeatNum;
    ofstream Del("Seat_Details.txt", ios::trunc);
    for (int i = 0; i < 10; i++)
    {
        Del << Seats[i].RowA << "-" << Seats[i].RowB << "-" << Seats[i].RowC << "-\n";
    }
    Del.close();
    cout << "Debug: Seat details file updated.\n";

    Del.close();
    return FinalSeatNum;
}

void iniTrain()
{
    availTrains[0].TName = "Shalimar Express";
    availTrains[0].TID = "SHE753";
    availTrains[0].TSource = "Karachi";
    availTrains[0].TDest = "Lahore";
    availTrains[0].TDate = "24-Dec-2020";
    availTrains[0].arriveTime = "20:00 (8:00 PM)";
    availTrains[0].departTime = "16:40 (4:40 PM)";
    availTrains[0].TClasses = "Economy, AC Lower, AC Business";
    availTrains[0].TSeats = 30;

    availTrains[1].TName = "Karakoram Express";
    availTrains[1].TID = "KKE694";
    availTrains[1].TSource = "Karachi";
    availTrains[1].TDest = "Faisalabad";
    availTrains[1].TDate = "26-Dec-2020";
    availTrains[1].arriveTime = "08:00 (8:00 AM)";
    availTrains[1].departTime = "04:40 (4:40 AM)";
    availTrains[1].TClasses = "Economy, AC Lower, AC Business";
    availTrains[1].TSeats = 30;

    availTrains[2].TName = "Green Line Express";
    availTrains[2].TID = "GLE400";
    availTrains[2].TSource = "Karachi";
    availTrains[2].TDest = "Islamabad";
    availTrains[2].TDate = "05-Jan-2021";
    availTrains[2].arriveTime = "12:00 (12:00 PM)";
    availTrains[2].departTime = "10:00 (10:00 AM)";
    availTrains[2].TClasses = "Economy, AC Lower, AC Business";
    availTrains[2].TSeats = 30;

    availTrains[3].TName = "Tezgam Express";
    availTrains[3].TID = "TEZ123";
    availTrains[3].TSource = "Karachi";
    availTrains[3].TDest = "Faisalabad";
    availTrains[3].TDate = "01-Jan-2021";
    availTrains[3].arriveTime = "15:00 (03:00 PM)";
    availTrains[3].departTime = "9:00 (09:00 AM)";
    availTrains[3].TClasses = "Economy, AC Lower, AC Business";
    availTrains[3].TSeats = 30;

    availTrains[4].TName = "Karachi Express";
    availTrains[4].TID = "KHE123";
    availTrains[4].TSource = "Karachi";
    availTrains[4].TDest = "Lahore";
    availTrains[4].TDate = "31-Dec-2000";
    availTrains[4].arriveTime = "12:00 (12:00 AM)";
    availTrains[4].departTime = "12:00 (09:00 PM)";
    availTrains[4].TClasses = "Economy, AC Lower, AC Business";
    availTrains[4].TSeats = 30;
}

string trainFill()
{
    bool check = false;
    bool check2 = false;
    trainCheck = true;

    // Loop until valid departure and arrival cities are entered
    while (true)
    {
        cout << "\t\t\t\t\tEnter Your Departure City: ";
        cin >> Source;
        cin.ignore();
        cout << "\t\t\t\t\tEnter Your Arrival City: ";
        cin >> Dest;
        cin.ignore();

        trainSort();

        cout << "\n\n\t\t\t\t\tAVAILABLE TRAINS ON THAT DAY IN THIS ROUTE ARE AS FOLLOWS (IF ANY): \n\n"
             << endl;

        for (int i = 0; i < noOfTrains; i++)
        {
            if (availTrains[i].TSource == Source && availTrains[i].TDest == Dest)
            {
                cout << "\t\t\t\t\tTrain Name: " << availTrains[i].TName << endl;
                cout << "\t\t\t\t\tTrain ID: " << availTrains[i].TID << endl;
                cout << "\t\t\t\t\tTrain Source: " << availTrains[i].TSource << endl;
                cout << "\t\t\t\t\tTrain Destination: " << availTrains[i].TDest << endl;
                cout << "\t\t\t\t\tTrain Departure Date: " << availTrains[i].TDate << endl;
                cout << "\t\t\t\t\tTrain Arrival Time: " << availTrains[i].arriveTime << endl;
                cout << "\t\t\t\t\tTrain Departure Time: " << availTrains[i].departTime << endl;
                cout << "\t\t\t\t\tAvailable Train Classes: " << availTrains[i].TClasses << endl;
                cout << "\t\t\t\t\tSeats Available: " << availTrains[i].TSeats << endl;
                cout << endl
                     << endl;
                check = true;
            }
        }

        if (!check)
        {
            cout << "\t\t\t\t\tNo trains available on this route. Please re-enter your details. \n";
        }
        else
        {
            break; // Exit the loop if trains are found
        }
    }

    // Loop until a valid train ID is entered
    while (true)
    {
        cout << "\t\t\t\t\tInput Train ID that you wish to book: ";
        cin >> BookedID;

        for (int i = 0; i < noOfTrains; i++)
        {
            if (BookedID == availTrains[i].TID)
            {
                TName = availTrains[i].TName;
                DTime = availTrains[i].departTime;
                ATime = availTrains[i].arriveTime;
                Date = availTrains[i].TDate;
                availTrains[i].TSeats--; // Reduce available seats

                cout << "Debug: Selected Train -> Name: " << TName
                     << ", Date: " << Date
                     << ", Departure: " << DTime
                     << ", Arrival: " << ATime << endl;

                check2 = true;
                return BookedID;
            }
        }

        if (!check2)
        {
            cout << "\t\t\t\t\tInput correct train ID! \n";
        }
    }
}

void trainPrice()
{
    int choice = 0;
    cout << "\t\t\t\t\tPrices based on classes are as follows: \n";
    cout << "\t\t\t\t\t1. Economy \t\t 2500 PKR \n";
    cout << "\t\t\t\t\t2. AC Lower \t\t 3500 PKR \n";
    cout << "\t\t\t\t\t3. AC Business \t\t 4500 PKR \n\n";
    cout << "\t\t\t\t\tInput Choice (1-3): ";
    cin >> choice;
    if (choice == 1)
    {
        Price = 2500;
        Class = "Economy [No Bed]";
    }
    else if (choice == 2)
    {
        Price = 3500;
        Class = "AC Lower [Bed Included]";
    }
    else if (choice == 3)
    {
        Price = 4500;
        Class = "AC Business [Bed Included]";
    }
}

void reserveTicket()
{
    string fName, lName;
    node *obj = new node();
    node *temp = tail;

    // Link the new node regardless of head and tail status
    if (head == NULL && tail == NULL)
    {
        head = obj;
        tail = obj;
    }
    else
    {
        tail->next = obj;
        tail = obj;
    }

    cout << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\tEnter First Name of Passenger: ";
    cin >> fName;
    cout << "\t\t\t\t\tEnter Last Name of Passenger: ";
    cin >> lName;
    Name = fName + " " + lName;

    cout << "\t\t\t\t\tEnter Age: ";
    cin >> Age;

    // Check for valid CNIC number
    do
    {
        cout << "\t\t\t\t\tEnter CNIC Number: ";
        cin >> NIC;
        if (NIC.length() != 13)
        {
            cout << "\n\t\t\t\t\tEnter a Valid 13 digit CNIC Number!" << endl;
        }
    } while (NIC.length() != 13);

    // Check for valid contact number
    do
    {
        cout << "\t\t\t\t\tEnter Contact Number: ";
        cin >> Contact;
        if (Contact.length() != 11)
        {
            cout << "\n\t\t\t\t\tEnter a Valid 11 digit Mobile Phone Number!" << endl;
        }
    } while (Contact.length() != 11);

    // Call trainFill function
    trainFill();
    // Assign train and booking details
    obj->BookedTID = BookedID;
    obj->BookedTName = TName;
    obj->DeptTime = DTime;
    obj->ArrTime = ATime;
    obj->BookedDate = Date;

    // After trainFill
    // cout << "Debug: Reservation Details -> Name: " << Name
    //      << ", Age: " << Age
    //      << ", NIC: " << NIC
    //      << ", Contact: " << Contact
    //      << ", Train Name: " << TName
    //      << ", Train ID: " << BookedID
    //      << ", Date: " << Date
    //      << ", Departure: " << DTime
    //      << ", Arrival: " << ATime << endl;

    // Call trainPrice function
    trainPrice();

    // Choose seat
    SeatNum = SeatChoose();

    // Call Payment function
    Payment();

    system("cls");

    cout << "\n\n\t\t\t\t\t Your payment is successfully processed!" << endl;
    cout << "\t\t\t\t\t PKR " << Price << " has been deducted from your Account." << endl;

    srand(time(0));

    // Randomly Generated Ticket ID:
    obj->ticketID = (rand());
    cout << endl
         << endl;
    cout << "\t\t\t\t\tTicket Generated! Your ID is: " << obj->ticketID << endl;
    currentID = obj->ticketID;

    // Assign passenger details
    obj->Name = Name;
    obj->Age = Age;
    obj->NIC = NIC;
    obj->Contact = Contact;

    // Assign train and booking details
    obj->BookedTID = BookedID;
    obj->BookedSource = Source; // Correct assignment
    obj->BookedDest = Dest;     // Correct assignment
    obj->BookedDate = Date;
    obj->BookedTName = TName;
    obj->DeptTime = DTime;
    obj->ArrTime = ATime;
    obj->BookedSeatNum = SeatNum;
    obj->Price = Price;
    obj->BookedClass = Class;

    cout << endl
         << endl;

    cout << "Ticket Reserved! ID: " << obj->ticketID
         << ", Name: " << obj->Name
         << ", Price: " << obj->Price << endl;
    cout << "Debug: Ticket Reserved -> Name: " << obj->Name
         << ", Age: " << obj->Age << ", NIC: " << obj->NIC
         << ", Contact: " << obj->Contact << endl;

    cout << "Ticket Reserved for Train: " << obj->BookedTName << endl;

    saveTicketToFile(obj);
}

void loadTicketsFromFile()
{
    ifstream inFile("Tickets.txt");
    if (!inFile.is_open())
    {
        cout << "No previously saved tickets found.\n";
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        node *ticket = new node();

        getline(ss, line, ',');
        ticket->ticketID = stoi(line);           // Ticket ID
        getline(ss, ticket->Name, ',');          // Name
        getline(ss, ticket->Age, ',');           // Age
        getline(ss, ticket->NIC, ',');           // NIC
        getline(ss, ticket->Contact, ',');       // Contact
        getline(ss, ticket->BookedTName, ',');   // Train Name
        getline(ss, ticket->BookedTID, ',');     // Train ID
        getline(ss, ticket->BookedSource, ',');  // Source
        getline(ss, ticket->BookedDest, ',');    // Destination
        getline(ss, ticket->BookedDate, ',');    // Date of Booking
        getline(ss, ticket->DeptTime, ',');      // Departure Time
        getline(ss, ticket->ArrTime, ',');       // Arrival Time
        getline(ss, ticket->BookedSeatNum, ','); // Seat Number
        getline(ss, line, ',');
        ticket->Price = stof(line);            // Price
        getline(ss, ticket->BookedClass, ','); // Train Class

        // Add the ticket to linked list
        if (head == NULL)
        {
            head = ticket;
            tail = ticket;
        }
        else
        {
            tail->next = ticket;
            tail = ticket;
        }
    }
    inFile.close();
}

void display()
{
    cout << endl
         << endl
         << endl
         << endl
         << endl;
    if (head != NULL && tail != NULL)
    {
        cout << "\t\t\t\t\tList is as follows: \n";
        node *temp = head;
        do
        {
            cout << "\t\t\t\t\tTicket ID: " << temp->ticketID << endl;
            cout << "\t\t\t\t\tName: " << temp->Name << endl;
            cout << "\t\t\t\t\tAge: " << temp->Age << endl;
            cout << "\t\t\t\t\tNIC: " << temp->NIC << endl;
            cout << "\t\t\t\t\tContact: " << temp->Contact << endl;
            cout << "\t\t\t\t\tTrain ID: " << temp->BookedTID << endl;
            cout << "\t\t\t\t\tTrain Name: " << temp->BookedTName << endl;
            cout << "\t\t\t\t\tTrain Class: " << temp->BookedClass << endl;
            cout << "\t\t\t\t\tSeat Number: " << temp->BookedSeatNum << endl;
            cout << "\t\t\t\t\tDate of Booking: " << temp->BookedDate << endl;
            cout << "\t\t\t\t\tSource: " << temp->BookedSource << endl;
            cout << "\t\t\t\t\tDestination: " << temp->BookedDest << endl;
            cout << "\t\t\t\t\tDeparture TIme: " << temp->DeptTime << endl;
            cout << "\t\t\t\t\tArrival Time: " << temp->ArrTime << endl;
            cout << endl;
            temp = temp->next;
        } while (temp);
        Sleep(1000);
    }
    else
        cout << "List is empty, nothing to display. \n";
}

void viewTicket()
{
    int search;
    string choice;
    bool found = false;
    node *temp = head;

    cout << "\n\n\t\t\t\t\tDo You Want to View Most Recent Booking? If so, Press 1\n";
    cout << "\t\t\t\t\tDo You Want to Search an Older Booking? If so, Press 2\n";
    cout << "\t\t\t\t\tEnter Choice (1-2): ";
    cin >> choice;

    if (choice == "1")
    {
        search = currentID;
    }
    else if (choice == "2")
    {
        cout << "\t\t\t\t\tEnter Your Booking ID: ";
        cin >> search;
    }
    else
    {
        cout << "\t\t\t\t\tInvalid input. Retry! \n";
        return;
    }

    while (temp != NULL)
    {
        if (temp->ticketID == search)
        {
            found = true;
            cout << "\t\t\t\t\tBooking ID: " << temp->ticketID << endl;
            cout << "\t\t\t\t\tName: " << temp->Name << endl;
            cout << "\t\t\t\t\tAge: " << temp->Age << endl;
            cout << "\t\t\t\t\tNIC: " << temp->NIC << endl;
            cout << "\t\t\t\t\tContact: " << temp->Contact << endl;
            cout << "\t\t\t\t\tTrain ID: " << temp->BookedTID << endl;
            cout << "\t\t\t\t\tTrain Name: " << temp->BookedTName << endl;
            cout << "\t\t\t\t\tTrain Class: " << temp->BookedClass << endl;
            cout << "\t\t\t\t\tSeat Number: " << temp->BookedSeatNum << endl;
            cout << "\t\t\t\t\tDate of Booking: " << temp->BookedDate << endl;
            cout << "\t\t\t\t\tSource: " << temp->BookedSource << endl;
            cout << "\t\t\t\t\tDestination: " << temp->BookedDest << endl;
            cout << "\t\t\t\t\tDeparture Time: " << temp->DeptTime << endl;
            cout << "\t\t\t\t\tArrival Time: " << temp->ArrTime << endl;
            cout << endl;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "\t\t\t\t\tNo Matching Booking Found.\n";
    }
}
void editDetails()
{
    string fName, lName;
    int search;
    bool found = false;

    cout << "\t\t\t\t\tEDIT DETAILS:" << endl
         << endl;
    cout << "\t\t\t\t\tEnter ticket ID: ";
    cin >> search;

    node *temp = head;

    while (temp != NULL)
    {
        if (temp->ticketID == search)
        {
            found = true;
            cout << "\t\t\t\t\tEnter First Name of Passenger: ";
            cin >> fName;
            cout << "\t\t\t\t\tEnter Last Name of Passenger: ";
            cin >> lName;
            temp->Name = fName + " " + lName;

            cout << "\t\t\t\t\tEnter Age: ";
            cin >> temp->Age;

            cout << "\t\t\t\t\tEnter CNIC Number: ";
            cin >> temp->NIC;

            cout << "\t\t\t\t\tEnter Contact Number: ";
            cin >> temp->Contact;

            cout << "\n\t\t\t\t\tTicket details updated successfully!" << endl;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "\n\t\t\t\t\tTicket ID not found!" << endl;
        return;
    }

    // Rewrite Tickets.txt with updated linked list
    ofstream outFile("Tickets.txt", ios::trunc);
    temp = head; // Reset temp to the head of the list

    while (temp != NULL)
    {
        outFile << temp->ticketID << "," << temp->Name << "," << temp->Age << ","
                << temp->NIC << "," << temp->Contact << ","
                << temp->BookedTName << "," << temp->BookedTID << ","
                << temp->BookedSource << "," << temp->BookedDest << ","
                << temp->BookedDate << "," << temp->DeptTime << ","
                << temp->ArrTime << "," << temp->BookedSeatNum << ","
                << temp->Price << "," << temp->BookedClass << "\n";
        temp = temp->next;
    }

    outFile.close();
    cout << "Debug: Tickets.txt updated after editing.\n";
}

void admin()
{
    string choice, user, password;
    system("cls");
    cin.clear();
    cout << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\tWELCOME TO ADMIN PORTAL!\n\n";

    cout << "\t\t\t\t\tEnter your login credentials below! \n";

    while (true)
    {
        cout << "\t\t\t\t\tEnter your Username: ";
        cin >> user;
        cout << "\t\t\t\t\tEnter your Password: ";
        cin >> password;

        if ((user == "MURTAZA" && password == "SMS123") ||
            (user == "ASHIR" && password == "ASH123") ||
            (user == "MUQEEM" && password == "MUQ123"))
        {
            cout << "\t\t\t\t\tLogged in Successfully!\n";
            cin.clear();
            system("cls");
            cout << endl
                 << endl
                 << endl
                 << endl
                 << endl;
            cout << "\t\t\t\t\tSelect 1 to View all Booked Tickets. \n";
            cout << "\t\t\t\t\tSelect 2 to add Trains. \n";
            cout << "\t\t\t\t\tSelect 3 to Exit\n";

            do
            {
                cout << "\t\t\t\t\tEnter Choice To Proceed (1-3): ";
                cin >> choice;
                if (choice == "1")
                    display();
                else if (choice == "2")
                {
                    cin.clear();
                    addTrains();
                    if (trainCheck == false)
                        trainFill();
                }
                else if (choice == "3")
                {
                    system("cls");
                    main();
                    return;
                }
                else
                    cout << "\t\t\t\t\tEnter correct choice. Try again. \n";

            } while (choice != "3");
            break;
        }
        else
        {
            cout << "\t\t\t\t\tInvalid credentials. Please login again.\n";
        }
    }
}

void addRoute(string src, string dest)
{
    trainRoutes[src].push_back(dest);
}

void suggestRoutes(string src)
{
    if (trainRoutes.count(src) == 0)
    {
        cout << "No routes available from " << src << ".\n";
        return;
    }
    cout << "Available routes from " << src << ": ";
    for (const string &dest : trainRoutes[src])
    {
        cout << dest << " ";
    }
    cout << endl;
}
