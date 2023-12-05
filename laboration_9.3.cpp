#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <fstream>
using namespace std;


union Date {
    struct {
        int day;
        int month;
        int year;
    } components;
    long long int serial;  
};

struct Note {
    string lastName;
    string firstName;
    string phoneNumber;
    Date birthdate;
};

bool Compare_By_LastName(const Note& a, const Note& b);
void Input_And_Print_Data(Note *notes, int numNotes);
void PrintSortedData(Note *notes, int numNotes);
void People_SearchFor_Month(Note *notes, int numNotes, int searchMonth);
void SaveToFile(Note* notes, int numNotes, const char* filename);
void LoadFromFile(Note* &notes, int& numNotes, const char* filename);


int main() {
    int searchMonth;
    char filename[100];

    int N;
    cout << "Input count of notes: ";
    cin >> N;
    Note* notes = new Note[N];
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Choose exercise" << endl << endl;
        cout << " [1] - Input data from keyboard and print" << endl;
        cout << " [2] - Print sorted data" << endl;
        cout << " [3] - Search from month" << endl;
        cout << " [4] - Write file" << endl;
        cout << " [5] - Print file" << endl;
        cout << " [0] - Exit" << endl << endl;
        cout << "Input value: "; cin >> menuItem;
        cout << endl << endl << endl;


        switch (menuItem) {
        case 1:
            Input_And_Print_Data(notes, N);
            break;
        case 2:
            PrintSortedData(notes, N);
            break;
        case 3:
            cout << "Input month for search: ";
            cin >> searchMonth;
            People_SearchFor_Month(notes, N, searchMonth);
            break;
        case 4:
            cin.get();
            cin.sync();

            cout << "Input name of file: "; cin.getline(filename, 99);
            SaveToFile(notes, N, filename);
            break;
        case 5:
            cin.ignore();

            cout << "Input name of file: ";  cin.getline(filename, 99);
            LoadFromFile(notes, N, filename);

            PrintSortedData(notes, N);
            break;
        case 0:
            break;
        default:
            cout <<"You wrote mistake value!" << endl;
        }
    } while (menuItem != 0);

    return 0;
}


bool Compare_By_LastName(const Note& a, const Note& b) {
    return a.lastName < b.lastName;
}

void Input_And_Print_Data(Note *notes, int numNotes) {
    for (int i = 0; i < numNotes; ++i) {
        cout << "Note #" << i + 1 << endl << endl;
        cout << "Last Name: ";
        cin >> notes[i].lastName;
        cout << "Name: ";
        cin >> notes[i].firstName;
        cout << "Phone number: ";
        cin >> notes[i].phoneNumber;
        cout << "Birthday (day, month, year): " << endl;
        cin >> notes[i].birthdate.components.day >> notes[i].birthdate.components.month >> notes[i].birthdate.components.year;
    }
}
void PrintSortedData(Note* notes, int numNotes) {
    sort(notes, notes + numNotes, Compare_By_LastName);

    cout << "Sort Data:" << endl;
    for (int i = 0; i < numNotes; ++i) {
        cout << setw(15) << left << "Last Name: " << notes[i].lastName << endl;
        cout << setw(15) << left << "Name: " << notes[i].firstName << endl;
        cout << setw(15) << left << "Phone number: " << notes[i].phoneNumber << endl;
        cout << setw(15) << left << "Date of birth: " << notes[i].birthdate.components.day << "/"
            << notes[i].birthdate.components.month << "/" << notes[i].birthdate.components.year << endl << endl;
    }
}

void People_SearchFor_Month(Note *notes, int numNotes, int searchMonth) {
    bool found = false;

    cout << "Data from people who born in this month " << searchMonth << ":" << endl;
    for (int i = 0; i < numNotes; ++i) {
        if (notes[i].birthdate.components.month == searchMonth) {
            cout << setw(15) << left << "Last Name: " << notes[i].lastName << endl;
            cout << setw(15) << left << "Name: " << notes[i].firstName << endl;
            cout << setw(15) << left << "Phone number: " << notes[i].phoneNumber << endl;
            cout << setw(15) << left << "Date of birth: " << notes[i].birthdate.components.day << "/"
                << notes[i].birthdate.components.month << "/" << notes[i].birthdate.components.year << endl << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No data for peoples in this month" << endl;
    }
}

void SaveToFile(Note* notes, const int numNotes, const char* filename) {
    ofstream fout(filename, ios::binary);
    fout.write((char*)&numNotes, sizeof(numNotes));
    for (int i = 0; i < numNotes; i++)
        fout.write((char*)&notes[i], sizeof(Note));

    fout.close();
}

void LoadFromFile(Note*& notes, int& numNotes, const char* filename)
{
    delete[] notes;
    ifstream fin(filename, ios::binary);
    fin.read((char*)&numNotes, sizeof(numNotes));
    notes = new Note[numNotes];
    for (int i = 0; i < numNotes; i++)
        fin.read((char*)&notes[i], sizeof(Note));
    fin.close();
}