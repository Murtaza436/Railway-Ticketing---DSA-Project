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