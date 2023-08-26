#include <bits/stdc++.h>
using namespace std;

#define ROW 3
#define COLUMN 10
#define USERS 60
#define CHARGE 15
/*NOTE: Charges are calculated based on hours.If vehicle is parked for 2 minutes let us say from 9:45 to 9:47 then charges will be
calculated as per one hour and the customer need to pay 15 rupees.
Admin-ID - D123
Password - 12*/

bool AdminAuthentication(string admin_name, string admin_password)
{
    string adminName = "D123";
    string adminPassword = "12";
    if (admin_name == adminName && admin_password == adminPassword)
    {
        return true;
    }
    return false;
}
string getCurrentTime()
{
    time_t currentTime = time(nullptr);
    tm *localTime = localtime(&currentTime);
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    return to_string(hour) + ":" + to_string(minute);
}

string weekDay(int num)
{
    switch (num)
    {
    case 1:
        return "Sunday";
    case 2:
        return "Monday";
    case 3:
        return "Tuesday";
    case 4:
        return "Wednesday";
    case 5:
        return "Thursday";
    case 6:
        return "Friday";
    case 7:
        return "Saturday";
    }
    return "";
}

string getCurrentDay()
{
    time_t currentTime = time(nullptr);
    tm *localTime = localtime(&currentTime);
    string str = weekDay((localTime->tm_wday) + 1) + " : " + to_string(localTime->tm_mday) + "-" + to_string((localTime->tm_mon) + 1) + "-" + to_string((localTime->tm_year) + 1900);
    return str;
}

int extractHour(string time)
{
    size_t colon = time.find(':');
    string s = time.substr(0, colon);
    return stoi(s);
}

int extractMinute(string time)
{
    size_t colon = time.find(':');
    string s = time.substr(colon + 1);
    return stoi(s);
}

int timeDifference(string entrytime)
{
    string currentTime = getCurrentTime();
    int entryhour = extractHour(entrytime);
    int entryminute = extractMinute(entrytime);
    int exithour = extractHour(currentTime);
    int exitminute = extractMinute(currentTime);

    if ((exithour - entryhour) == 0)
    {
        return 1;
    }
    else
    {
        int diff = (exithour - entryhour);
        if (exitminute > entryminute)
            diff++;
        else if (exitminute < entryminute && entryminute > 35)
            diff++;
        return diff;
    }
}

class User
{
public:
    string parking_slot, name, phone_number, vehicle_number, entry_time;
    int vehicle_type;
};

struct History
{
    string parking_slot, name, phone_number, vehicle_number, entry_time, exit_time;
    int vehicle_type;
    History *next;
    History(string parking_slot, string name, string phone_number, string vehicle_number, string entry_time, int vehicle_type)
    {
        this->parking_slot = parking_slot;
        this->name = name;
        this->phone_number = phone_number;
        this->vehicle_number = vehicle_number;
        this->entry_time = entry_time;
        if (vehicle_type == 1)
            this->vehicle_type = 2;
        else
            this->vehicle_type = 4;
        this->exit_time = getCurrentTime();
        next = NULL;
    }
};

History *Head = NULL;

History *insertAtEnd(string parking_slot, string name, string phone_number, string vehicle_number, string entry_time, int vehicle_type)
{
    History *temp = new History(parking_slot, name, phone_number, vehicle_number, entry_time, vehicle_type);
    if (Head == NULL)
    {
        return temp;
    }
    History *curr = Head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = temp;
    return Head;
}

void PrintHistory()
{
    History *curr = Head;
    cout << "HISTORY OF THE RECENTLY DEPARTED VEHICLES ARE: " << endl
         << endl;
    cout << "USER NAME\t"
         << "PHONE NUMBER\t"
         << "VEHICLE NUMBER\t"
         << "SLOT NUMBER\t"
         << "VEHICLE TYPE\t"
         << "ENTRY TIME\t"
         << "EXIT TIME\t" << endl;
    while (curr != NULL)
    {
        cout << curr->name << "\t" << curr->phone_number << "\t  " << curr->vehicle_number << "\t    " << curr->parking_slot << "\t\t  " << curr->vehicle_type << " Wheeler"
             << "\t  " << curr->entry_time << "\t\t " << curr->exit_time << endl;
        curr = curr->next;
    }
}

int two_wheeler[ROW][COLUMN];
int four_wheeler[ROW][COLUMN];
User user[USERS];
int temp;
bool checkEntry = false, checkExit = false;

void utilityFunction()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            two_wheeler[i][j] = 0;
            four_wheeler[i][j] = 0;
        }
    }
}

void utilityFunction1()
{
    for (int i = 0; i < USERS; i++)
    {
        user[i].parking_slot = "";
    }
}
// Testing Purpose
//  void utilityFunction2()
//  {
//      for(int i=0;i<ROW;i++)
//      {
//          for(int j=0;j<COLUMN;j++)
//              cout<<two_wheeler[i][j]<<" ";
//          cout<<endl;
//      }
//  }

string getAvailableSlot(int vehicle_type)
{
    if (vehicle_type == 1)
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                if (two_wheeler[i][j] == 0)
                {
                    char a = char(i + 65);
                    string str(1, a);
                    return str + to_string(j + 1);
                }
            }
        }
    }
    else if (vehicle_type == 2)
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                if (four_wheeler[i][j] == 0)
                {
                    char a = char(i + 65);
                    string str(1, a);
                    return str + to_string(j + 1);
                }
            }
        }
    }
    return "NULL";
}

void setParkingSlot(int vehicle_type, string slot)
{
    if (vehicle_type == 1)
    {
        char a = slot[0];
        int i = a - 'A';
        int j = stoi(slot.substr(1)) - 1;
        two_wheeler[i][j] = 1;
    }
    else if (vehicle_type == 2)
    {
        char a = slot[0];
        int i = a - 'A';
        int j = stoi(slot.substr(1)) - 1;
        four_wheeler[i][j] = 1;
    }
}

void freeParkingSlot(int vehicle_type, string slot)
{
    if (vehicle_type == 1)
    {
        char a = slot[0];
        int i = a - 'A';
        int j = stoi(slot.substr(1)) - 1;
        two_wheeler[i][j] = 0;
    }
    else if (vehicle_type == 2)
    {
        char a = slot[0];
        int i = a - 'A';
        int j = stoi(slot.substr(1)) - 1;
        four_wheeler[i][j] = 0;
    }
}

int getIndexValue(string slot, int type, string name, string phone_number, string vehicle_number)
{
    for (int i = 0; i < USERS; i++)
    {
        if (user[i].parking_slot == slot && user[i].vehicle_type == type && user[i].name == name && user[i].phone_number == phone_number)
            return i;
    }
    return -1;
}

void printReceiptEntry()
{
    cout << "\n-------------------------------------------------" << endl;
    cout << "                 Parking Receipt" << endl;
    cout << "Day & Date   : " << getCurrentDay() << endl;
    cout << "Name         : " << user[temp].name << endl;
    cout << "Phone No.    : " << user[temp].phone_number << endl;
    cout << "Vehicle No.  : " << user[temp].vehicle_number << endl;
    if (user[temp].vehicle_type == 1)
        cout << "Vehicle Type : "
             << "Two Wheeler" << endl;
    if (user[temp].vehicle_type == 2)
        cout << "Vehicle Type : "
             << "Four Wheeler" << endl;
    cout << "Parking Slot : " << user[temp].parking_slot << endl;
    cout << "Entry Time   : " << user[temp].entry_time << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "                 Thanks for Parking" << endl;
}

void printReceiptExit(int dif)
{
    cout << "\n------------------------------------------------------------" << endl;
    cout << "                 Parking Receipt" << endl;
    cout << "Day & Date           : " << getCurrentDay() << endl;
    cout << "Name                 : " << user[temp].name << endl;
    cout << "Phone No.            : " << user[temp].phone_number << endl;
    cout << "Vehicle No.          : " << user[temp].vehicle_number << endl;
    if (user[temp].vehicle_type == 1)
        cout << "Vehicle Type         : "
             << "Two Wheeler" << endl;
    if (user[temp].vehicle_type == 2)
        cout << "Vehicle Type         : "
             << "Four Wheeler" << endl;
    cout << "Parking Slot         : " << user[temp].parking_slot << endl;
    cout << "Entry Time           : " << user[temp].entry_time << endl;
    cout << "Exit Time            : " << getCurrentTime() << endl;
    cout << "Total Payable Amount : " << dif * CHARGE << endl;
    cout << "\n------------------------------------------------------------" << endl;
    cout << "                 Thanks for Parking" << endl;
}

int getStatus(string slot, int type)
{
    if (type == 1)
    {
        char a = slot[0];
        int i = a - 'A';
        int j = stoi(slot.substr(1)) - 1;
        if (i < ROW && j < COLUMN)
        {
            if (two_wheeler[i][j] == 1)
                return 1;
            else
                return 0;
        }
        else
        {
            return -1;
        }
    }
    else if (type == 2)
    {
        char a = slot[0];
        int i = a - 'A';
        int j = stoi(slot.substr(1)) - 1;
        if (i < ROW && j < COLUMN)
        {
            if (four_wheeler[i][j] == 1)
                return 1;
            else
                return 0;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

void printParticularSlotBySlot(string slot, int type)
{
    if (type == 1)
    {
        switch (getStatus(slot, type))
        {
        case 1:
        {
            for (int i = 0; i < USERS; i++)
            {
                if (user[i].parking_slot == slot && user[i].vehicle_type == type)
                {
                    cout << "\nHere are the Details of Slot : " << slot << endl;
                    cout << "Name         : " << user[i].name << endl;
                    cout << "Phone No.    : " << user[i].phone_number << endl;
                    cout << "Vehicle No.  : " << user[i].vehicle_number << endl;
                    cout << "Vehicle Type : "
                         << "Two Wheeler" << endl;
                    cout << "Parking Slot : " << user[i].parking_slot << endl;
                    cout << "Entry Time   : " << user[i].entry_time << endl
                         << endl;
                    break;
                }
            }
            break;
        }
        case -1:
        {
            cout << "\nNo Such Slot present in the Parking Area" << endl
                 << endl;
            break;
        }
        case 0:
        {
            cout << "\nNo Vehicle is Parked in the Slot : " << slot << endl
                 << endl;
            break;
        }
        }
    }
    else if (type == 2)
    {
        switch (getStatus(slot, type))
        {
        case 1:
        {
            for (int i = 0; i < USERS; i++)
            {
                if (user[i].parking_slot == slot && user[i].vehicle_type == type)
                {
                    cout << "\nHere are the Details of Slot : " << slot << endl;
                    cout << "Name         : " << user[i].name << endl;
                    cout << "Phone No.    : " << user[i].phone_number << endl;
                    cout << "Vehicle No.  : " << user[i].vehicle_number << endl;
                    cout << "Vehicle Type : "
                         << "Four Wheeler" << endl;
                    cout << "Parking Slot : " << user[i].parking_slot << endl;
                    cout << "Entry Time   : " << user[i].entry_time << endl
                         << endl;
                    break;
                }
            }
            break;
        }
        case -1:
        {
            cout << "\nNo Such Slot present in the Parking Area" << endl
                 << endl;
            break;
        }
        case 0:
        {
            cout << "\nNo Vehicle is Parked at the Slot : " << slot << endl
                 << endl;
            break;
        }
        }
    }
}

void entry()
{
    string name, phone_number, vehicle_number, parking_slot;
    int vehicle_type;
    cout << "Please Enter the Name           : ";
    getline(cin, name);
    cout << "Please Enter the Phone number   : ";
    getline(cin, phone_number);
    cout << "Please Enter the Vehicle Number : ";
    getline(cin, vehicle_number);
    cout << "Press 1 - Two Wheeler" << endl;
    cout << "Press 2 - Four Wheeler" << endl;
    cout << "Your Choice                     : ";
    cin >> vehicle_type;

    parking_slot = getAvailableSlot(vehicle_type);
    if (parking_slot != "NULL")
    {
        setParkingSlot(vehicle_type, parking_slot);
        for (int i = 0; i < USERS; i++)
        {
            if (user[i].parking_slot == "")
            {
                user[i].name = name;
                user[i].phone_number = phone_number;
                user[i].vehicle_number = vehicle_number;
                user[i].vehicle_type = vehicle_type;
                user[i].parking_slot = parking_slot;
                user[i].entry_time = getCurrentTime();
                temp = i;
                break;
            }
        }
    }
    else
    {
        cout << "\nNo Free Space Available Right Now" << endl;
        cout << "We are Really Sorry for Inconvenience" << endl
             << endl;
        return;
    }
    printReceiptEntry();
}

void exit()
{
    string name, vehicle_number, parking_slot, phone_number;
    int vehicle_type;
    cout << "Please Enter the Name           : ";
    getline(cin, name);
    cout << "Please Enter the Phone number   : ";
    getline(cin, phone_number);
    cout << "Please Enter the Vehicle Number : ";
    getline(cin, vehicle_number);
    cout << "Press 1 - Two Wheeler" << endl;
    cout << "Press 2 - Four Wheeler" << endl;
    cout << "Your Choice                     : ";
    cin >> vehicle_type;
    cin.ignore();
    cout << "Enter the Parking Slot          : ";
    getline(cin, parking_slot);
    switch (getStatus(parking_slot, vehicle_type))
    {
    case 1:
    {
        temp = getIndexValue(parking_slot, vehicle_type, name, phone_number, vehicle_number);
        if (temp != -1)
        {
            int dif = timeDifference(user[temp].entry_time);
            freeParkingSlot(vehicle_type, parking_slot);
            printReceiptExit(dif);
            Head = insertAtEnd(user[temp].parking_slot, user[temp].name, user[temp].phone_number, user[temp].vehicle_number, user[temp].entry_time, user[temp].vehicle_type);
            user[temp].parking_slot = "";
            break;
        }
        else
        {
            cout << "\n========Invalid Data=========" << endl
                 << endl;
            break;
        }
    }
    case -1:
    {
        cout << "\nNo Such Slot present in the Parking Area" << endl
             << endl;
        break;
    }
    case 0:
    {
        cout << "\nNo Vehicle is Parked at the Slot : " << parking_slot << endl
             << endl;
        break;
    }
    }
}

int main()
{
    utilityFunction();
    utilityFunction1();
    cout << "========================= WELCOME TO PARKING MANAGEMENT SYSTEM =========================" << endl;
    int choice = 0;
    do
    {
        cout << "\nPress 1 - Entry Vehicle" << endl;
        cout << "Press 2 - Exit Vehicle" << endl;
        cout << "Press 3 - Check Vehicle at Slot" << endl;
        cout << "Press 4 - Check the History" << endl;
        cout << "Press 0 - Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cin.ignore();
            entry();
            checkEntry = true;
            break;
        }
        case 2:
        {
            cin.ignore();
            exit();
            checkExit = true;
            break;
        }
        case 3:
        {
            int type;
            string slot, admin_name, admin_pass;
            cout << "-----------------------------ADMIN AUTHENTICATION IS REQUIRED-----------------------------" << endl;
            cout << "Admin-ID: ";
            cin >> admin_name;
            cout << "Password: ";
            cin >> admin_pass;
            if (AdminAuthentication(admin_name, admin_pass))
            {
                cout << "Successfully Logged in" << endl
                     << endl;
                cout << "Press 1 - Two Wheeler" << endl;
                cout << "Press 2 - Four Wheeler" << endl;
                cout << "Your Choice : ";
                cin >> type;
                cout << "Enter the Slot : ";
                cin.ignore();
                cin >> slot;
                printParticularSlotBySlot(slot, type);
            }
            else
            {
                cout << "------------------------------------WRONG CREDENTIALS------------------------------------" << endl;
            }
            break;
        }
        case 4:
        {
            if (checkEntry && checkExit)
            {
                string admin_name, admin_pass;
                cout << "-----------------------------ADMIN AUTHENTICATION IS REQUIRED-----------------------------" << endl;
                cout << "Admin-ID: ";
                cin >> admin_name;
                cout << "Password: ";
                cin >> admin_pass;
                if (AdminAuthentication(admin_name, admin_pass))
                {
                    cout << "Successfully Logged in" << endl;
                    PrintHistory();
                }
                else
                {
                    cout << "------------------------------------WRONG CREDENTIALS------------------------------------" << endl;
                }
            }
            else if (!checkEntry)
            {
                cout << "************************* NO VEHICLE IS PARKED IN THE PARKING AREA *************************" << endl;
            }
            else if (!checkExit)
            {
                cout << "************************* NO VEHICEL HAS DEPARTED FROM THE PARKING AREA! *************************" << endl;
            }
            break;
        }
        default:
        {
            cout << "\n========================= Exiting TO PARKING MANAGEMENT SYSTEM =========================" << endl;
            cout << "                       Thanks for Using Parking Management System" << endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
