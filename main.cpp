#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
struct AddressBook
{
    int userId;
    string name, surname, fullAddress, phoneNumber, email;
};
struct Users
{
    int id;
    string login, password;
};
void printMainMenu();
void printLogMenu();
void selectOptionFromMainMenu(vector <AddressBook> &addresses, int& numberOfAddresses);
void addNewAddressDataIntoBook(vector <AddressBook> &addresses, int& numberOfAddresses);
string readLine();
void inputAddressIntoRequiredAddresBookIndex(vector <AddressBook> &addresses, int addressBookIndex);
void printAllAdressesInBook(vector <AddressBook> &addresses, int numberOfAddresses);
void printRequiredAddress(const AddressBook &address);
void lookFor(vector <AddressBook> &addresses, int numOfAddresses);
char selectAddressSearchOption();
void displaySearchedAddresses(vector <AddressBook> &addresses, int numOfAddresses, char addressSearchOption);
void manageAddressEdit(vector <AddressBook> &addresses, int numOfAddresses);
int selectAddressPositionToEdit(vector <AddressBook> &addresses, int numOfAddresses);
void printEditMenu();
void executeAddressEdit(vector <AddressBook> &addresses, int addressArrayIndexToEdit);
void saveAddedAddressInFile(vector <AddressBook> addresses, int addressIndex);
vector <AddressBook> readAddressesToVector(vector <AddressBook> &addresses);
void selectAddressToDelete(vector <AddressBook> &addresses, int &numberOfAddresses);
void deleteAddress(vector <AddressBook> &addresses, int indexToDelete);
void clearCurrentAddressesInFile();
void saveChangesInFile(vector <AddressBook> &addresses, int numberOfAddresses);
bool isIndexExists(vector <AddressBook> &addresses, int index);
void confirmAddedData();
void selectOptionFromLogMenu(vector <Users> &users);
void registerNewUser(vector <Users> &users);
bool isLoginFree(vector <Users> users, string userLogin);

int main()
{
    vector <AddressBook> addresses;
    vector <Users> users;
    addresses = readAddressesToVector(addresses);
    int numberOfAddresses = addresses.size();

    while (true)
    {
       printLogMenu();
       selectOptionFromLogMenu(users);
    }

    while (true)
    {
        printMainMenu();
        selectOptionFromMainMenu(addresses, numberOfAddresses);
    }

    return 0;
}

void printMainMenu()
{
    system("cls");
    cout << "MENU" << endl;
    cout << "1. Dodaj nowa osobe do ksiazki adresowej" << endl;
    cout << "2. Wyszukaj osobe w ksiazce adresowej" << endl;
    cout << "3. Wyswietl wszystkie osoby w ksiazce adresowej" << endl;
    cout << "4. Edytuj osobe w ksiazce adresowej" << endl;
    cout << "5. Usun osobe" << endl;
    cout << "9. Wyjdz" << endl;
}

void printLogMenu()
{
   system("cls");
    cout << "MENU" << endl;
    cout << "1. Zaloguj sie" << endl;
    cout << "2. Zarejestruj sie" << endl;
    cout << "3. Zamknij Program" << endl;
}

void selectOptionFromMainMenu(vector <AddressBook> &addresses, int& numberOfAddresses)
{
    char menuChar;
    cin >> menuChar;

    switch(menuChar)
    {
    case '1' :
    {
        addNewAddressDataIntoBook(addresses, numberOfAddresses);
        numberOfAddresses++;
        break;
    }
    case '2' :
    {
        lookFor(addresses, numberOfAddresses);
        break;
    }
    case '3' :
    {
        system("cls");
        printAllAdressesInBook(addresses, numberOfAddresses);
        system("pause");
        break;
    }
    case '4' :
    {
        manageAddressEdit(addresses, numberOfAddresses);
        saveChangesInFile(addresses, numberOfAddresses);
        break;
    }
    case '5' :
    {
        selectAddressToDelete(addresses, numberOfAddresses);
        break;
    }
    case '9' :
    {
        exit(0);
        break;
    }
    }
}

void addNewAddressDataIntoBook(vector <AddressBook> &addresses, int& numberOfAddresses)
{
    system("cls");
    inputAddressIntoRequiredAddresBookIndex(addresses, numberOfAddresses);
    saveAddedAddressInFile(addresses, numberOfAddresses);
    confirmAddedData();
}
void inputAddressIntoRequiredAddresBookIndex(vector <AddressBook> &addresses, int addressBookIndex)
{

    AddressBook address;
    int lastIndex = addresses.size() - 1;
    if (lastIndex < 0)
    {
        address.userId = 1;
    }
    else
    {
        address.userId = addresses[lastIndex].userId + 1;

    }
    cout << "Wprowadz imie" << endl;
    address.name = readLine();
    cout << "Wprowadz nazwisko" << endl;
    address.surname = readLine();
    cout << "Wprowadz pelny adres" << endl;
    address.fullAddress = readLine();
    cout << "Wprowadz nr telefonu" << endl;
    address.phoneNumber = readLine();
    cout << "Wprowadz adres e-mail" << endl;
    address.email = readLine();

    addresses.push_back(address);
}

string readLine()
{
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

void printAllAdressesInBook(vector <AddressBook> &addresses, int numberOfAddresses)
{
    if (numberOfAddresses == 0)
    {
        cout << "Nie ma zadnych adresow w ksiazce adresowej" << endl;
    }
    else
    {
        for (auto address : addresses)
        {
            printRequiredAddress(address);
        }
    }
}
void printRequiredAddress(const AddressBook &address)
{
    cout << "ID:              " << address.userId << endl;
    cout << "Imie:            " << address.name << endl;
    cout << "Nazwisko:        " << address.surname << endl;
    cout << "Adres:           " << address.fullAddress << endl;
    cout << "Telefon:         " << address.phoneNumber << endl;
    cout << "email:           " << address.email << endl;
    cout << endl;
}

void lookFor(vector <AddressBook> &addresses, int numOfAddresses)
{
    system("cls");
    if (numOfAddresses != 0)
    {
        char addressSearchOption = selectAddressSearchOption();
        displaySearchedAddresses(addresses, numOfAddresses, addressSearchOption);
    }
    else
    {
        cout << "W ksiazce nie ma zadnych adresow" << endl;
        Sleep(2000);
    }

}
char selectAddressSearchOption()
{
    system("cls");
    char addressSearchOption;
    cout << "Wyszukaj po:" << endl;
    cout << "1. Imieniu" << endl;
    cout << "2. Nazwisku" << endl;
    while (true)
    {
        cin >> addressSearchOption;
        if ((addressSearchOption == '1') || (addressSearchOption == '2'))
        {
            break;
        }
        else
        {
            cout << "Wprowadz wartosc 1 lub 2" << endl;
        }
    }
    return addressSearchOption;
}

void displaySearchedAddresses(vector <AddressBook> &addresses, int numOfAddresses, char addressSearchOption)
{
    system("cls");
    string searchedData;
    bool addressIsFound = false;

    switch (addressSearchOption)
    {
    case '1':
    {
        cout << "Podaj szukane imie" << endl;
        searchedData = readLine();
        for (auto address : addresses)
        {
            if (address.name == searchedData)
            {
                printRequiredAddress(address);
                addressIsFound = true;
            }
        }
        break;
    }
    case '2':
    {
        cout << "Podaj szukane nazwisko" << endl;
        searchedData = readLine();
        for (auto address : addresses)
        {
            if (address.surname == searchedData)
            {
                printRequiredAddress(address);
                addressIsFound = true;
            }
        }
        break;
    }
    }
    if (!addressIsFound) cout << "Nie odnaleziono adresu" << endl;
    system("pause");
}
void manageAddressEdit(vector <AddressBook> &addresses, int numOfAddresses)
{
    system("cls");


    if (numOfAddresses != 0)
    {
        cout << "Wybierz ID adresu do edycji" << endl;
        int addressArrayIndexToEdit = selectAddressPositionToEdit(addresses, numOfAddresses);
        executeAddressEdit(addresses, addressArrayIndexToEdit);
    }
    else
    {
        cout << "W ksiazce nie ma zadnych adresow" << endl;
        Sleep(2000);
    }
}
int selectAddressPositionToEdit(vector <AddressBook> &addresses, int numOfAddresses)
{
    system("cls");
    auto it = addresses.begin();
    int indexCounter = 0;
    cout << "Wybierz numer adresu do edycji" << endl;
    int addressPosition;
    printAllAdressesInBook(addresses, numOfAddresses);

    while (true)
    {
        cin >> addressPosition;
        if (isIndexExists(addresses, addressPosition))
        {
            while (it != addresses.end())
            {
                if (it -> userId == addressPosition)
                {
                    addressPosition = indexCounter;
                    return addressPosition;
                }
                else
                {
                    indexCounter++;
                    it++;
                }
            }
        }
        else
        {
            cout << "Nie ma takiego indeksu. Wybierz Ponownie." << endl;
        }
    }
}
void executeAddressEdit(vector <AddressBook> &addresses, int addressArrayIndexToEdit)
{
    system("cls");
    char dataToChange;
    printEditMenu();
    cin >> dataToChange;
    switch (dataToChange)
    {
    case '1' :
    {
        cout << "Podaj nowe imie:" << endl;
        addresses[addressArrayIndexToEdit].name = readLine();
        break;
    }
    case '2' :
    {
        cout << "Podaj nowe nazwisko:" << endl;
        addresses[addressArrayIndexToEdit].surname = readLine();
        break;
    }
    case '3' :
    {
        cout << "Podaj nowy adres:" << endl;
        addresses[addressArrayIndexToEdit].fullAddress = readLine();
        break;
    }
    case '4' :
    {
        cout << "Podaj nowy numer telefonu:" << endl;
        addresses[addressArrayIndexToEdit].phoneNumber = readLine();
        break;
    }
    case '5' :
    {
        cout << "Podaj nowy adres email:" << endl;
        addresses[addressArrayIndexToEdit].email = readLine();
        break;
    }
    case '6' :
    {
        break;
    }
    }
    confirmAddedData();
    Sleep(2000);
}

void printEditMenu()
{
    system("cls");
    cout << "EDIT MENU" << endl;
    cout << "Wybierz dane do edycji:" << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Adres" << endl;
    cout << "4. Numer telefonu" << endl;
    cout << "5. email" << endl;
    cout << "6. Powrót do menu" << endl;
}

void saveAddedAddressInFile(vector <AddressBook> addresses, int addressIndex)
{
    fstream fileAddresses;
    fileAddresses.open("addresses.txt", ios::out | ios::app);

    fileAddresses << addresses[addressIndex].userId << "|" << addresses[addressIndex].name << "|" << addresses[addressIndex].surname << "|" << addresses[addressIndex].fullAddress << "|" << addresses[addressIndex].phoneNumber << "|" << addresses[addressIndex].email << endl;

}

vector <AddressBook> readAddressesToVector(vector <AddressBook> &addresses)
{
    fstream fileAddresses;
    string line;
    AddressBook address;

    fileAddresses.open("addresses.txt", ios::in | ios::app);
    if (fileAddresses.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku";
        exit(0);
    }
    while(getline(fileAddresses, line))
    {
        stringstream ss(line);
        string field;

        getline(ss, field, '|');
        address.userId = stoi(field);

        getline(ss, field, '|');
        address.name = field;

        getline(ss, field, '|');
        address.surname = field;

        getline(ss, field, '|');
        address.fullAddress = field;

        getline(ss, field, '|');
        address.phoneNumber = field;

        getline(ss, field, '|');
        address.email = field;

        addresses.push_back(address);

    }
    return addresses;
}
void selectAddressToDelete(vector <AddressBook> &addresses, int &numberOfAddresses)
{
    system("cls");
    int indexToDelete;
    char deleteAnswer;
    if (numberOfAddresses != 0)
    {
        cout << "Wybierz indeks adresu do usuniecia" << endl;
        printAllAdressesInBook(addresses, numberOfAddresses);
        cin >> indexToDelete;
        if (isIndexExists(addresses, indexToDelete))
        {
            cout << "Czy na pewno chcesz usunac t/n" << endl;
            cin >> deleteAnswer;

            if (deleteAnswer == 't')
            {
                deleteAddress(addresses, indexToDelete);
                numberOfAddresses--;
                saveChangesInFile(addresses, numberOfAddresses);
            }
        }
        else
        {
            cout << "Nie ma takiego indeksu" << endl;
            Sleep(2000);
        }
    }
    else
    {
        cout << "Nie ma adresow w ksiazce" << endl;
        Sleep(2000);
    }

}

void deleteAddress(vector <AddressBook> &addresses, int indexToDelete)
{
    auto it = addresses.begin();

    while (it != addresses.end())
    {
        if (it -> userId == indexToDelete)
        {
            it = addresses.erase(it);
            return;
        }
        else
        {
            it++;
        }
    }
}

void saveChangesInFile(vector <AddressBook> &addresses, int numberOfAddresses)
{
    clearCurrentAddressesInFile();
    for (int i = 0; i < numberOfAddresses; i++)
    {
        saveAddedAddressInFile(addresses, i);
    }

}

void clearCurrentAddressesInFile()
{
    ofstream fileAddresses;
    fileAddresses.open("addresses.txt", ios::trunc);
    fileAddresses.close();
}

bool isIndexExists(vector <AddressBook> &addresses, int index)
{
    bool indexExists = false;
    for (auto address : addresses)
    {
        if (address.userId == index)
        {
            indexExists = true;
        }
    }
    return indexExists;
}
void confirmAddedData()
{
    cout << "Poprawnie wprowadzone dane" << endl;
}

void selectOptionFromLogMenu(vector <Users> &users)
{
    char logMenuChoice;
    cin >> logMenuChoice;

    switch (logMenuChoice)
    {
    case '1' :
        break;
    case '2' :
        registerNewUser(users);
        break;
    case '3' :
        exit(0);
    }
}

void registerNewUser(vector <Users> &users)
{
    system("cls");
    string userLogin;
    Users user;

    user.id = users.size() + 1;

    cout << "Podaj login" << endl;
    while (true)
    {
        cin >> userLogin;
        if (isLoginFree(users, userLogin))
        {
            user.login = userLogin;
            break;
        }
        else
        {
            cout << "Login zajety. Podaj nowy login" << endl;
        }
    }

    cout << "Podaj haslo" << endl;
    user.password = readLine();

    users.push_back(user);
}

bool isLoginFree(vector <Users> users, string userLogin)
{
    bool availableLogin = true;
    for (auto user : users)
    {
        if (user.login == userLogin)
        {
            availableLogin = false;
        }
    }
    return availableLogin;
}
