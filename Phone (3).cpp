#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;
using namespace std;
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
    bool operator()(Person& a, Person& b) const {
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
    cout << "Press enter to retuen  menu\n";
    system("pause");
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
void SetNewPerson()
{
    Person P;
    P.SetPerson();
    system("cls");
}
/////////////////////////////////////////////////
void SerachSpecificContact()
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
        if (!test)
        {
            cout << "Contact not fouand \n";
        }
        cout << "Press enter to retuen  menu\n";
        system("pause");
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
        if (!test)
        {
            cout << "Contact not found \n";
        }
        cout << "Press enter to retuen  menu\n";
        system("pause");
    }
    else
    {
        cout << "INVALID INPUT(try again)" << endl;
    }
    system("cls");
}
/////////////////////////////////////////////////
void Modifyexitingcontact()
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
        if (!test)
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
        system("pause");
        system("cls");
    }
    if (choice == '2')
    {
        bool test = false;
        Person P;
        cin.ignore();
        cout << "Enter Phone number : ";
        getline(cin, input);
        if (inFile.is_open())
        {
            test = true;
        }
        if (test == false)
        {
            cout << "File not found" << endl;
            return;
        }
        while (inFile >> P)
        {
            test = false;
            if (input.find(P.GetPhoneNumber()) != -1)
            {

                Person P1; P1.SetPerson();
                cout << "Edit Successfully" << endl;
            }
            else
            {
                test = true;
                persons.push_back(P);
            }
        }
        if (!test)
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
    system("pause");
    system("cls");
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void DeleteContact1()
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
       
        if (inFile.is_open())
        {
            test = true;
        }
        if (test == false)
        {
            cout << "File not found" << endl;
            return;
        }
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
        system("pause");
        system("cls");
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
        char yes;
        cout << "Are you sure about the operation? (Y/N) : ";
        cin >> yes;
        if (yes == 'n' || yes == 'N')
        {
            return;
        }
        else
        {
            remove("Phone,txt");
            ofstream outFile("Phone.txt", ios::out);
            for (auto& Write : persons)
            {
                outFile << Write;
            }
            outFile.close();
            persons.clear();
        }

    }
    else
    {
        cout << "INVALID INPUT(try again)" << endl;
    }
    system("pause");
    system("cls");
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////

void Menu()
{
    while (true)
    {
        char in;
        cout << "1.Save New Contact" << endl;
        cout << "2.Display All Saved Contact" << endl;
        cout << "3.Search Specific Contact" << endl;
        cout << "4.Modify Existing Contact" << endl;
        cout << "5.Delete Specific Contact" << endl;
        cout << "6.Delete All Existing Contacts\033[0m" << endl;
        cout << "7.Exit" << endl;
        cout << ">> "; cin >> in;
        if (in == '1')
        {
            SetNewPerson();
        }
        ///////////////////new condition///////////////
        if (in == '2')
        {
            
            SortContact();
            Person P;
            ifstream inputfile("Phone.txt");
            bool test = false;
            if (inputfile.is_open())
            {
                while (inputfile >> P)
                {
                    test = true;
                    P.Display();
                }
            }
            if(test == false)
            {
                cout << "File not found" << endl;
            }
            inputfile.close();
            cout << "Press enter to retuen  menu\n";
            system("pause");
            system("cls");
        }
        ///////////////////new condition///////////////
        if (in == '3')
        {
            SerachSpecificContact();
        }
        if (in == '4')
        {
            Modifyexitingcontact();
        }
        ///////////////////new condition///////////////
        if (in == '5')
        {
            DeleteContact1();
        }
        if (in == '6')
        {
            char yes;
            cout << "Are you sure about the operation? (Y/N) : ";
            cin >> yes;
            if (yes == 'n' || yes == 'N')
            {
                system("pause");
                system("cls");
            }
            if(yes=='Y'||yes=='y')
            {
                ifstream inFile("Phone.txt");
                inFile.close();
                remove("Phone.txt");
                cout << "Delete All Contact Successfully " << endl;
                system("pause");
                system("cls");
            }
        }
        if (in == '7')
        {
            cout << "See you latter" << endl;
            exit(1);
            system("pause");
            system("cls");
        }
        if (in < '1' || in>'7')
        {
            cout << "INVALID INPUT(try again)" << endl;
            system("pause");
            system("cls");
        }

    }

}
/////////////////////////////////////////////////


int main(void)
{
    Menu();



    return 0;
}


