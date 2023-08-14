#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
struct AddressBook
{
    int addressId, loggedInUsersId;
    string name, surname, fullAddress, phoneNumber, email;
};
struct Users
{
    int id;
    string login, password;
};
void printMainMenu();
void printLogMenu();
void selectOptionFromMainMenu(vector <AddressBook> &addresses, int& loggedInUsersId);
void addNewAddressDataIntoBook(vector <AddressBook> &addresses, int loggedInUsersId);
string readLine();
void inputAddressIntoRequiredAddresBookIndex(vector <AddressBook> &addresses, int loggedInUsersId);
void printAllAdressesInBook(vector <AddressBook> &addresses);
void printRequiredAddress(const AddressBook &address);
void lookFor(vector <AddressBook> &addresses);
char selectAddressSearchOption();
void displaySearchedAddresses(vector <AddressBook> &addresses, char addressSearchOption);
void manageAddressEdit(vector <AddressBook> &addresses);
int selectAddressPositionToEdit(vector <AddressBook> &addresses);
void printEditMenu();
void executeAddressEdit(vector <AddressBook> &addresses, int addressArrayIndexToEdit);
void saveAddedAddressInFile(vector <AddressBook> addresses);
vector <AddressBook> readAddressesToVector(vector <AddressBook> &addresses, int loggedInUsersId);
void selectAddressToDelete(vector <AddressBook> &addresses);
void deleteAddress(vector <AddressBook> &addresses, int indexToDelete);
void saveChangesInFileAfterEdit(vector <AddressBook> &addresses, int addressArrayIndexToEdit);
bool isIndexExists(vector <AddressBook> &addresses, int index);
void confirmAddedData();
void selectOptionFromLogMenu(vector <Users> &users, vector <AddressBook> &addresses);
void registerNewUser(vector <Users> &users);
bool isLoginFree(vector <Users> &users, string userLogin);
int login(vector <Users> &users);
void saveRegisteredUserInFile(const Users &user);
void pasteUserDataInFile(ofstream &file, const Users &user);
void readUsersInVector(vector <Users> &users);
void saveChangesInFileAfterDelete(vector <AddressBook> &addresses, int indexToDelete);

int main()
{
    vector <AddressBook> addresses;
    vector <Users> users;
    readUsersInVector(users);

    while (true)
    {
        printLogMenu();
        selectOptionFromLogMenu(users, addresses);
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
    cout << "9. Wyloguj" << endl;
}

void printLogMenu()
{
    system("cls");
    cout << "MENU" << endl;
    cout << "1. Zaloguj sie" << endl;
    cout << "2. Zarejestruj sie" << endl;
    cout << "3. Zamknij Program" << endl;
}

void selectOptionFromMainMenu(vector <AddressBook> &addresses, int& loggedInUsersId)
{
    char menuChar;
    cin >> menuChar;

    switch(menuChar)
    {
    case '1' :
    {
        addNewAddressDataIntoBook(addresses, loggedInUsersId);
        break;
    }
    case '2' :
    {
        lookFor(addresses);
        break;
    }
    case '3' :
    {
        system("cls");
        printAllAdressesInBook(addresses);
        system("pause");
        break;
    }
    case '4' :
    {
        manageAddressEdit(addresses);
        break;
    }
    case '5' :
    {
        selectAddressToDelete(addresses);
        break;
    }
    case '9' :
    {
        loggedInUsersId = -1;
        addresses.clear();
        break;
    }
    }
}

void addNewAddressDataIntoBook(vector <AddressBook> &addresses, int loggedInUsersId)
{
    system("cls");
    inputAddressIntoRequiredAddresBookIndex(addresses, loggedInUsersId);
    saveAddedAddressInFile(addresses);
    confirmAddedData();
}
void inputAddressIntoRequiredAddresBookIndex(vector <AddressBook> &addresses, int loggedInUsersId)
{

    AddressBook address;

    address.addressId = addresses.empty() ? 1 : addresses.back().addressId + 1;

    address.loggedInUsersId = loggedInUsersId;

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

void printAllAdressesInBook(vector <AddressBook> &addresses)
{
    if (addresses.empty())
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
    cout << "ID:              " << address.addressId << endl;
    cout << "Imie:            " << address.name << endl;
    cout << "Nazwisko:        " << address.surname << endl;
    cout << "Adres:           " << address.fullAddress << endl;
    cout << "Telefon:         " << address.phoneNumber << endl;
    cout << "email:           " << address.email << endl;
    cout << endl;
}

void lookFor(vector <AddressBook> &addresses)
{
    system("cls");
    if (!addresses.empty())
    {
        char addressSearchOption = selectAddressSearchOption();
        displaySearchedAddresses(addresses, addressSearchOption);
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

void displaySearchedAddresses(vector <AddressBook> &addresses, char addressSearchOption)
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
void manageAddressEdit(vector <AddressBook> &addresses)
{
    system("cls");


    if (!addresses.empty())
    {
        cout << "Wybierz ID adresu do edycji" << endl;
        int addressArrayIndexToEdit = selectAddressPositionToEdit(addresses);
        executeAddressEdit(addresses, addressArrayIndexToEdit);
    }
    else
    {
        cout << "W ksiazce nie ma zadnych adresow" << endl;
        Sleep(2000);
    }
}
int selectAddressPositionToEdit(vector <AddressBook> &addresses)
{
    system("cls");
    auto it = addresses.begin();
    int indexCounter = 0;
    cout << "Wybierz numer adresu do edycji" << endl;
    int addressPosition;
    printAllAdressesInBook(addresses);

    while (true)
    {
        cin >> addressPosition;
        if (isIndexExists(addresses, addressPosition))
        {
            while (it != addresses.end())
            {
                if (it -> addressId == addressPosition)
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
    saveChangesInFileAfterEdit(addresses, addressArrayIndexToEdit);
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

void saveAddedAddressInFile(vector <AddressBook> addresses)
{
    int addressIndex = addresses.size() - 1;
    ofstream fileAddresses("addresses.txt", ios::app);

    fileAddresses << addresses[addressIndex].addressId << "|" << addresses[addressIndex].loggedInUsersId << "|" << addresses[addressIndex].name << "|";
    fileAddresses << addresses[addressIndex].surname << "|" << addresses[addressIndex].fullAddress << "|";
    fileAddresses << addresses[addressIndex].phoneNumber << "|" << addresses[addressIndex].email << endl;

    fileAddresses.close();
}

vector <AddressBook> readAddressesToVector(vector <AddressBook> &addresses, int loggedInUsersId)
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
        address.addressId = stoi(field);

        getline(ss, field, '|');
        address.loggedInUsersId = stoi(field);

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

        if (address.loggedInUsersId == loggedInUsersId)
        {
            addresses.push_back(address);
        }


    }
    return addresses;
}
void selectAddressToDelete(vector <AddressBook> &addresses)
{
    system("cls");
    int indexToDelete;
    char deleteAnswer;
    if (!addresses.empty())
    {
        cout << "Wybierz indeks adresu do usuniecia" << endl;
        printAllAdressesInBook(addresses);
        cin >> indexToDelete;
        if (isIndexExists(addresses, indexToDelete))
        {
            cout << "Czy na pewno chcesz usunac t/n" << endl;
            cin >> deleteAnswer;

            if (deleteAnswer == 't')
            {
                deleteAddress(addresses, indexToDelete);
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
    int index = 0;
    auto it = addresses.begin();

    while (it != addresses.end())
    {
        if (it -> addressId == indexToDelete)
        {
            saveChangesInFileAfterDelete(addresses, index);
            it = addresses.erase(it);

            return;
        }
        else
        {
            it++;
            index++;
        }

    }
}

void saveChangesInFileAfterDelete(vector <AddressBook> &addresses, int indexToDelete)
{
    vector <AddressBook> temporaryAddresses;
    AddressBook temporaryAddress;

    ifstream mainFile;

    mainFile.open("addresses.txt", ios::in);
    ofstream temporaryFile("temporaryAddresses.txt", ios::out | ios::app);

    string line;

    while(getline(mainFile, line))
    {
        stringstream ss(line);
        string field;

        getline(ss, field, '|');
        temporaryAddress.addressId = stoi(field);

        getline(ss, field, '|');
        temporaryAddress.loggedInUsersId = stoi(field);

        getline(ss, field, '|');
        temporaryAddress.name = field;

        getline(ss, field, '|');
        temporaryAddress.surname = field;

        getline(ss, field, '|');
        temporaryAddress.fullAddress = field;

        getline(ss, field, '|');
        temporaryAddress.phoneNumber = field;

        getline(ss, field, '|');
        temporaryAddress.email = field;

        if ((temporaryAddress.addressId == addresses[indexToDelete].addressId) && (temporaryAddress.loggedInUsersId == addresses[indexToDelete].loggedInUsersId))
        {
            cout << temporaryAddress.addressId << endl;
            cout << addresses[indexToDelete].addressId << endl;
            cout << temporaryAddress.loggedInUsersId << endl;
            cout << addresses[indexToDelete].loggedInUsersId << endl;
            system("pause");
            continue;
        }
        else
        {
            temporaryFile << temporaryAddress.addressId << "|" << to_string(temporaryAddress.loggedInUsersId) << "|" << temporaryAddress.name << "|";
            temporaryFile << temporaryAddress.surname << "|" << temporaryAddress.fullAddress << "|" << temporaryAddress.phoneNumber << "|" << temporaryAddress.email << endl;
        }
    }

        mainFile.close();
        temporaryFile.close();

        remove("addresses.txt");
        rename("temporaryAddresses.txt", "addresses.txt");

}

void saveChangesInFileAfterEdit(vector <AddressBook> &addresses, int addressArrayIndexToEdit)
{
    vector <AddressBook> temporaryAddresses;
    AddressBook temporaryAddress;

    ifstream mainFile;

    mainFile.open("addresses.txt", ios::in);
    ofstream temporaryFile("temporaryAddresses.txt", ios::out | ios::app);

    string line;

    while(getline(mainFile, line))
    {
        stringstream ss(line);
        string field;

        getline(ss, field, '|');
        temporaryAddress.addressId = stoi(field);

        getline(ss, field, '|');
        temporaryAddress.loggedInUsersId = stoi(field);

        getline(ss, field, '|');
        temporaryAddress.name = field;

        getline(ss, field, '|');
        temporaryAddress.surname = field;

        getline(ss, field, '|');
        temporaryAddress.fullAddress = field;

        getline(ss, field, '|');
        temporaryAddress.phoneNumber = field;

        getline(ss, field, '|');
        temporaryAddress.email = field;

        if ((temporaryAddress.addressId != addresses[addressArrayIndexToEdit].addressId) || (temporaryAddress.loggedInUsersId != addresses[addressArrayIndexToEdit].loggedInUsersId))
        {
            temporaryFile << temporaryAddress.addressId << "|" << to_string(temporaryAddress.loggedInUsersId) << "|" << temporaryAddress.name << "|";
            temporaryFile << temporaryAddress.surname << "|" << temporaryAddress.fullAddress << "|" << temporaryAddress.phoneNumber << "|" << temporaryAddress.email << endl;
        }
        else
        {
            temporaryFile << addresses[addressArrayIndexToEdit].addressId << "|" << addresses[addressArrayIndexToEdit].loggedInUsersId << "|" << addresses[addressArrayIndexToEdit].name << "|";
            temporaryFile << addresses[addressArrayIndexToEdit].surname << "|" << addresses[addressArrayIndexToEdit].fullAddress << "|" << addresses[addressArrayIndexToEdit].phoneNumber << "|" << addresses[addressArrayIndexToEdit].email << endl;
        }
    }

        mainFile.close();
        temporaryFile.close();

        remove("addresses.txt");
        rename("temporaryAddresses.txt", "addresses.txt");

}


bool isIndexExists(vector <AddressBook> &addresses, int index)
{
    bool indexExists = false;
    for (auto address : addresses)
    {
        if (address.addressId == index)
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

void selectOptionFromLogMenu(vector <Users> &users, vector <AddressBook> &addresses)
{
    char logMenuChoice;
    int loggedInUsersId = (-1);
    cin >> logMenuChoice;

    switch (logMenuChoice)
    {
    case '1' :
        if (users.empty())
        {
            break;
        }
        loggedInUsersId = login(users);
        if (loggedInUsersId != -1)
        {
            readAddressesToVector(addresses, loggedInUsersId);
            int numberOfAddresses = addresses.size();

            while (loggedInUsersId != -1)
            {
                printMainMenu();
                selectOptionFromMainMenu(addresses, loggedInUsersId);
            }
        }
        else
        {
            cout << "Bledne haslo lub login" << endl;
            Sleep(1000);
        }
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
    saveRegisteredUserInFile(user);
}

bool isLoginFree(vector <Users> &users, string userLogin)
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

int login(vector <Users> &users)
{
    int loggedInUsersId = (-1);
    string login, password;

    cout << "Podaj login" << endl;
         cin >> login;
    cout << "Podaj haslo" << endl;
         cin >> password;

    for (auto user : users)
    {
        if ((user.login == login) && (user.password == password))
        {
            loggedInUsersId = user.id;
        }
    }
    return loggedInUsersId;
}

void saveRegisteredUserInFile(const Users &user)
{
    ofstream file("users.txt", ios::app);
    pasteUserDataInFile(file, user);
    file.close()
;}

void pasteUserDataInFile(ofstream &file, const Users &user)
{
    file << user.id << "|" << user.login << "|" << user.password << endl;
}

void readUsersInVector(vector <Users> &users)
{
    Users user;
    string line;
    ifstream file("users.txt", ios::in | ios::app);
    while (getline(file, line))
    {
        stringstream ss(line);
        string field;

        getline (ss, field, '|');
        user.id = stoi(field);

        getline (ss, field, '|');
        user.login = field;

        getline (ss, field, '|');
        user.password = field;

        users.push_back(user);
    }

    file.close();

}
