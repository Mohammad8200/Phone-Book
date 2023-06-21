#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;
void Menu();


class Person
{
protected:
    string Name;
    string Family;
    string PhoneNumber;
    string Address;
    string Email;
public:
    Person() {};
    void SetPerson();
    void Display();
    string GetNameAndFamily();
    string GetPhoneNumber();
    void ModifiPerson();
    friend ostream& operator<<(ostream& COUT, const Person& P)
    {
        COUT << P.Name << ' ' << P.Family << ' ' << P.Email << ' ' << P.Address << ' ';
        COUT << P.PhoneNumber << endl;
        return COUT;
    }
    friend ifstream& operator>>(ifstream& CIN, Person& P)
    {
        CIN >> P.Name >> P.Family >> P.Email;
        CIN >> P.Address >> P.PhoneNumber;
        return CIN;
    }
    
};
/////////////////////////////////////////////////
struct CompareByName {
    bool operator()(Person& a,Person& b) const {
        return (a.GetNameAndFamily() < b.GetNameAndFamily());
    }
};
/////////////////////////////////////////////////
void Person::SetPerson()
{
    Person P;
    cout << "Enter name : "; cin >> Name;
    cout << endl << "Enter Family : "; cin >> Family;
    cout << endl << "Enter Email : "; cin >> Email;
    cout << endl << "Enter Address : "; cin >> Address;
    cout << endl << "Enter Phone number : "; cin >> PhoneNumber;
    P.Name = Name; P.Email = Email; P.Address = Address;
    P.Family = Family; P.PhoneNumber = PhoneNumber;
    ofstream outfile("Phone.txt", ios::app);
    if (outfile.is_open())
    {
        cout << "ADD SUCCESSFULLY" << endl;
    }
    outfile << P;
    outfile.close();
}
/////////////////////////////////////////////////
void Person::Display()
{
    cout << "Name : " << Name << " , Family : " << Family;
    cout << " , Address : " << Address << " , Email : " << Email;
    cout << " , Phone number : " << PhoneNumber << endl;
}
/////////////////////////////////////////////////
string Person::GetNameAndFamily()
{
    string result;
    result = Name + " " + Family;
    return result;
}
/////////////////////////////////////////////////
string Person::GetPhoneNumber()
{
    return PhoneNumber;
}
/////////////////////////////////////////////////
void Person::ModifiPerson()
{

}
/////////////////////////////////////////////////
void SortContact()
{
    vector<Person> persons;
    ifstream inFile("Phone.txt");
    Person p;
    while (inFile >> p)
    {
        persons.push_back(p);
    }
    inFile.close();

    sort(persons.begin(), persons.end(), CompareByName());

    ofstream outFile("Phone.txt", ios::out);
    for (auto& W : persons)
    {
        outFile << W;
    }
    outFile.close();
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////

void Menu()
{
    while (true)
    {
        char in;
        cout << "\033[0;31m1.Save New Contact\033[0m" << endl;
        cout << "\033[0;32m2.Display All Saved Contact\033[0m" << endl;
        cout << "\033[0;33m3.Search Specific Contact\033[0m" << endl;
        cout << "\033[0;34m4.Modify Existing Contact\033[0m" << endl;
        cout << "\033[0;35m5.Delete Specific Contact\033[0m" << endl;
        cout << "\033[0;36m6.Delete All Existing Contacts\033[0m" << endl;
        cout << "\033[0m7.Exit\033[0m" << endl;
        cout << ">> ";
cin >> in;
        if (in == '1')
        {
            Person P;
            P.SetPerson();
        }
        ///////////////////new condition///////////////
        if (in == '2')
        {
            SortContact();
            Person P;
            ifstream inputfile("Phone.txt");
            while (inputfile >> P)
            {
                P.Display();
            }
            inputfile.close();
        }
        ///////////////////new condition///////////////
        if (in == '3')
        {
            bool test = false;
            Person P;
            ifstream inFile("Phone.txt");
            cout << "1.search with name and family \n2.search with phone ";
            cout << endl << ">> ";
            char inputChar;
            cin >> inputChar;
            string input;
            if (inputChar == '1')
            {
                cin.ignore();
                cout << "Enter Name and Family : ";
                getline(cin, input);
                while (inFile >> P)
                {
                    if (input.find(P.GetNameAndFamily()) != -1)
                    {
                        test = true;
                        P.Display();
                    }
                }
                ///////////////////new condition///////////////
                if (test)
                {
                    cout << "Contact not fouand ";
                }
            }
            if (inputChar == '2')
            {
                cin.ignore();
                cout << "Enter Phone number : ";
                getline(cin, input);
                while (inFile >> P)
                {
                    if (input.find(P.GetPhoneNumber()) != -1)
                    {
                        test = true;
                        P.Display();
                    }
                }
                ///////////////////new condition///////////////
                if (test)
                {
                    cout << "Contact not found ";
                }
            }
            else
            {
                cout << "INVALID INPUT(try again)" << endl;
            }
        }
        if (in == '4')
        {
            vector<Person> persons;
            ifstream inFile("Phone.txt");
            cout << "1.Modify with name and family \n2.Modify with phone number";
            cout << endl << ">> ";
            string input;
            char choice;
            cin >> choice;
            if (choice == '1')
            {
                bool test = false;
                Person P;
                cin.ignore();
                cout << "Enter Name and Family : ";
                getline(cin, input);
                while (inFile >> P)
                {
                    test = false;
                    if (input.find(P.GetNameAndFamily()) != -1)
                    {
                        Person P1;
                        P1.SetPerson();
                        // persons.push_back(P1);
                        cout << "Edit Successfully" << endl;
                    }
                    else
                    {
                        test = true;
                        persons.push_back(P);
                    }
                }
                if (test)
                {
                    cout << "Contact not found" << endl;
                }
                remove("Phone.txt");
                ofstream outFile("Phone.txt", ios::out);
                for (auto& Write : persons)
                {
                    outFile << Write;
                }
                outFile.close();
                persons.clear();
            }
            if (choice == '2')
            {
                bool test = false;
                Person P;
                cin.ignore();
                cout << "Enter Phone number : ";
                getline(cin, input);
                while (inFile >> P)
                {
                    test = false;
                    if (input.find(P.GetPhoneNumber()) != -1)
                    {
                        Person P1;
P1.SetPerson();
                        cout << "Edit Successfully" << endl;
                    }
                    else
                    {
                        test = true;
                        persons.push_back(P);
                    }
                }
                if (test)
                {
                    cout << "Contact not found" << endl;
                }
                remove("Phone.txt");
                ofstream outFile("Phone.txt", ios::out);
                for (auto& Write : persons)
                {
                    outFile << Write;
                }
                outFile.close();
                persons.clear();
            }
            else
            {
                cout << "INVALID INPUT(try again)" << endl;
            }
        }
        ///////////////////new condition///////////////
        if (in == '5')
        {
            vector<Person> persons;
            ifstream inFile("Phone.txt");
            cout << "1.Delete with name and family \n2.Delete with phone number";
            cout << endl << ">> ";
            string input;
            char choice;
            cin >> choice;
            if (choice == '1')
            {
                bool test = false;
                Person P;
                cin.ignore();
                cout << "Enter Name and Family : ";
                getline(cin, input);
                while (inFile >> P)
                {
                    test = false;
                    if (input.find(P.GetNameAndFamily()) != -1)
                    {
                        cout << "Delete successfully" << endl;
                    }
                    else
                    {
                        test = true;
                        persons.push_back(P);
                    }
                }
                if (test)
                {
                    cout << "Contact not found" << endl;
                }
                remove("Phone.txt");
                ofstream outFile("Phone.txt", ios::out);
                for (auto& Write : persons)
                {
                    outFile << Write;
                }
                outFile.close();
                persons.clear();
            }
            if (choice == '2')
            {
                Person P;
                cin.ignore();
                cout << "Enter Phone number : ";
                getline(cin, input);
                while (inFile >> P)
                {
                    if (input.find(P.GetPhoneNumber()) != -1)
                    {
                        cout << "Delete successfully" << endl;
                    }
                    else
                    {
                        persons.push_back(P);
                    }
                }
                remove("Phone,txt");
                ofstream outFile("Phone.txt", ios::out);
                for (auto& Write : persons)
                {
                    outFile << Write;
                }
                outFile.close();
                persons.clear();
            }
            else
            {
                cout << "INVALID INPUT(try again)" << endl;
            }
        }
        if (in == '6')
        {
            ifstream inFile("Phone.txt");
            remove("Phone.txt");
            cout << "Delete All Contact Successfully " << endl;
        }
        if (in == '7')
        {
            cout << "See you latter" << endl;
            exit(1);
        }

    }

}
/////////////////////////////////////////////////


int main(void)
{
    Menu();



    return 0;
}
