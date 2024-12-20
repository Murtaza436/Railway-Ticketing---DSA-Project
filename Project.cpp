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
void removeTicket(int remTicket)
{
    node *prev = head;
    node *delNode = head;
    bool found = false;

    // Find and remove the ticket
    while (delNode != NULL)
    {
        if (delNode->ticketID == remTicket)
        {
            found = true;
            break;
        }
        prev = delNode;
        delNode = delNode->next;
    }

    if (!found)
    {
        cout << "Ticket ID Not Found!\n";
        return;
    }

    // Unlink the node
    if (delNode == head)
    {
        head = head->next;
    }
    else
    {
        prev->next = delNode->next;
    }
    if (delNode == tail)
    {
        tail = prev;
    }

    cout << "\t\t\t\t\tDeleted Ticket ID: " << remTicket << "\n";

    // Update Seat_Details.txt
    fstream Seat("Seat_Details.txt");
    SeatRecord Seats[10];
    string line;
    int i = 0;

    while (getline(Seat, line))
    {
        size_t delimit = line.find('-');
        Seats[i].RowA = line.substr(0, delimit);
        size_t nextDelimit = line.find('-', delimit + 1);
        Seats[i].RowB = line.substr(delimit + 1, nextDelimit - delimit - 1);
        Seats[i].RowC = line.substr(nextDelimit + 1);
        i++;
    }
    Seat.close();

    // Restore the seat
    // Extract seat row and number, converting row to uppercase
    string seatRow = delNode->BookedSeatNum.substr(0);
    string seatNum = delNode->BookedSeatNum.substr(1);

    // Restore seat in Seat_Details.txt
    for (int j = 0; j < 10; j++)
    {
        if (seatRow == "A" && Seats[j].RowA == "XX")
        {
            Seats[j].RowA = seatNum;
        }
        if (seatRow == "B" && Seats[j].RowB == "XX")
        {
            Seats[j].RowB = seatNum;
        }
        if (seatRow == "C" && Seats[j].RowC == "XX")
        {
            Seats[j].RowC = seatNum;
        }
    }

    // Save back to Seat_Details.txt
    ofstream Del("Seat_Details.txt", ios::trunc);
    for (int j = 0; j < 10; j++)
    {
        Del << Seats[j].RowA << "-" << Seats[j].RowB << "-" << Seats[j].RowC << "-\n";
    }
    Del.close();

    // Update Tickets.txt
    ofstream outFile("Tickets.txt", ios::trunc);
    node *temp = head;

    while (temp != NULL)
    {
        outFile << temp->ticketID << "," << temp->Name << "," << temp->Age << ","
                << temp->NIC << "," << temp->Contact << ","
                << temp->BookedTName << "," << temp->BookedTID << ","
                << temp->BookedDest << "," << temp->BookedSource << ","
                << temp->BookedDate << "," << temp->DeptTime << ","
                << temp->ArrTime << "," << temp->BookedSeatNum << ","
                << temp->Price << "," << temp->BookedClass << "\n";
        temp = temp->next;
    }
    outFile.close();

    delete delNode;
    cout << "Debug: Tickets and seat details updated after deletion.\n";
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

