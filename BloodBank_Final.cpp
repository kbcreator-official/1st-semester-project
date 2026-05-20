/*
=============================================================
   BLOOD BANK MANAGEMENT SYSTEM
   Student   : KB 
   Roll No   : B2633051
   Subject   : Programming Fundamentals
   Instructor: Sir Sher Muhammad
   Topics    : Structures, Arrays, Functions, Loops,
               Switch, File Input and Output
=============================================================
*/

#include <iostream>
#include <fstream>    // For file input and output
#include <string>
using namespace std;

// ─── CONSTANT ─────────────────────────────────────────────
const int MAX_DONORS = 50;
const string FILE_NAME = "donors.txt";  // Data will be saved here

// ─── STRUCTURE ────────────────────────────────────────────
// All information of one donor stored together
struct Donor {
    int    id;
    string name;
    int    age;
    string bloodGroup;
    string city;
    string phone;
    int    units;
};

// ─── GLOBAL VARIABLES ─────────────────────────────────────
Donor donors[MAX_DONORS];
int totalDonors = 0;
int nextId = 1;

// ─── FUNCTION PROTOTYPES ──────────────────────────────────
void loadFromFile();    // Load saved data when program starts
void saveToFile();      // Save all data to file
void showMenu();
void addDonor();
void viewAllDonors();
void searchByBloodGroup();
void searchByName();
void deleteDonor();
void updateUnits();
void showStats();
void showLine();

// ══════════════════════════════════════════════════════════
// MAIN FUNCTION
// ══════════════════════════════════════════════════════════
int main() {
    // Load previously saved donor data from file
    loadFromFile();

    int choice;
    cout << "\n  ============================================" << endl;
    cout << "       WELCOME TO BLOOD BANK SYSTEM         " << endl;
    cout << "  ============================================" << endl;
    cout << "  " << totalDonors << " donor(s) loaded from saved data." << endl;

    do {
        showMenu();
        cout << "  Enter your choice: ";
        cin  >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addDonor();           break;
            case 2: viewAllDonors();      break;
            case 3: searchByBloodGroup(); break;
            case 4: searchByName();       break;
            case 5: deleteDonor();        break;
            case 6: updateUnits();        break;
            case 7: showStats();          break;
            case 8:
                // Save all data to file before exiting
                saveToFile();
                cout << "\n  Data saved! Goodbye." << endl;
                break;
            default:
                cout << "\n  Invalid choice! Enter 1-8." << endl;
        }

    } while (choice != 8);

    return 0;
}

// ══════════════════════════════════════════════════════════
// LOAD FROM FILE
// Reads all donors from donors.txt when program starts
// So data is never lost even after closing the program
// ══════════════════════════════════════════════════════════
void loadFromFile() {
    ifstream inFile(FILE_NAME);   // Open file for reading

    // If file does not exist yet, just return (first time running)
    if (!inFile) {
        return;
    }

    totalDonors = 0;

    // Read each donor one by one from file
    while (inFile >> donors[totalDonors].id) {
        inFile.ignore();   // Skip newline after id

        getline(inFile, donors[totalDonors].name);
        inFile >> donors[totalDonors].age;
        inFile.ignore();
        getline(inFile, donors[totalDonors].bloodGroup);
        getline(inFile, donors[totalDonors].city);
        getline(inFile, donors[totalDonors].phone);
        inFile >> donors[totalDonors].units;
        inFile.ignore();

        // Keep track of highest ID so next donor gets correct ID
        if (donors[totalDonors].id >= nextId) {
            nextId = donors[totalDonors].id + 1;
        }

        totalDonors++;

        // Stop if array is full
        if (totalDonors >= MAX_DONORS) break;
    }

    inFile.close();   // Always close file after reading
}

// ══════════════════════════════════════════════════════════
// SAVE TO FILE
// Writes all donors to donors.txt
// Called when user exits so data is permanently saved
// ══════════════════════════════════════════════════════════
void saveToFile() {
    ofstream outFile(FILE_NAME);   // Open file for writing

    if (!outFile) {
        cout << "  Error: Could not save data!" << endl;
        return;
    }

    // Write each donor to file line by line
    for (int i = 0; i < totalDonors; i++) {
        outFile << donors[i].id        << "\n";
        outFile << donors[i].name      << "\n";
        outFile << donors[i].age       << "\n";
        outFile << donors[i].bloodGroup << "\n";
        outFile << donors[i].city      << "\n";
        outFile << donors[i].phone     << "\n";
        outFile << donors[i].units     << "\n";
    }

    outFile.close();   // Always close file after writing
    cout << "  All data saved to " << FILE_NAME << endl;
}

// ══════════════════════════════════════════════════════════
// SHOW MENU
// ══════════════════════════════════════════════════════════
void showMenu() {
    cout << "\n";
    showLine();
    cout << "         BLOOD BANK MAIN MENU" << endl;
    showLine();
    cout << "  1. Add New Donor" << endl;
    cout << "  2. View All Donors" << endl;
    cout << "  3. Search by Blood Group" << endl;
    cout << "  4. Search by Name" << endl;
    cout << "  5. Delete a Donor" << endl;
    cout << "  6. Update Blood Units" << endl;
    cout << "  7. Show Statistics" << endl;
    cout << "  8. Save & Exit" << endl;
    showLine();
}

// Helper: prints a separator line
void showLine() {
    cout << "  ============================================" << endl;
}

// ══════════════════════════════════════════════════════════
// ADD DONOR
// Takes input and saves new donor — also auto-saves to file
// ══════════════════════════════════════════════════════════
void addDonor() {
    if (totalDonors >= MAX_DONORS) {
        cout << "\n  Storage full!" << endl;
        return;
    }

    cout << "\n"; showLine();
    cout << "         ADD NEW DONOR" << endl;
    showLine();

    Donor d;
    d.id = nextId;

    cout << "  Enter Name        : "; getline(cin, d.name);
    cout << "  Enter Age         : "; cin >> d.age; cin.ignore();
    cout << "  Enter Blood Group" << endl;
    cout << "  (A+/A-/B+/B-/O+/O-/AB+/AB-): "; getline(cin, d.bloodGroup);
    cout << "  Enter City        : "; getline(cin, d.city);
    cout << "  Enter Phone       : "; getline(cin, d.phone);
    cout << "  Enter Blood Units : "; cin >> d.units; cin.ignore();

    // Save donor into array
    donors[totalDonors] = d;
    totalDonors++;
    nextId++;

    // Auto-save to file after every new donor added
    saveToFile();

    cout << "\n  Donor added and saved! ID: " << d.id << endl;
}

// ══════════════════════════════════════════════════════════
// VIEW ALL DONORS
// ══════════════════════════════════════════════════════════
void viewAllDonors() {
    cout << "\n"; showLine();
    cout << "         ALL DONORS LIST" << endl;
    showLine();

    if (totalDonors == 0) {
        cout << "  No donors found!" << endl;
        return;
    }

    cout << "  ID  | Name              | Age | Blood | City         | Units" << endl;
    cout << "  ----|-------------------|-----|-------|--------------|------" << endl;

    for (int i = 0; i < totalDonors; i++) {
        cout << "  "    << donors[i].id;
        cout << "   | " << donors[i].name.substr(0, 17);
        cout << " | "   << donors[i].age;
        cout << "  | "  << donors[i].bloodGroup;
        cout << "    | " << donors[i].city.substr(0, 12);
        cout << " | "   << donors[i].units;
        cout << endl;
    }

    cout << "\n  Total Donors: " << totalDonors << endl;
}

// ══════════════════════════════════════════════════════════
// SEARCH BY BLOOD GROUP
// ══════════════════════════════════════════════════════════
void searchByBloodGroup() {
    cout << "\n"; showLine();
    cout << "       SEARCH BY BLOOD GROUP" << endl;
    showLine();

    string searchGroup;
    cout << "  Enter Blood Group: ";
    getline(cin, searchGroup);

    int found = 0;
    cout << "\n  Results for: " << searchGroup << endl;
    cout << "  -----------------------------------------" << endl;

    for (int i = 0; i < totalDonors; i++) {
        if (donors[i].bloodGroup == searchGroup) {
            cout << "  ID    : " << donors[i].id    << endl;
            cout << "  Name  : " << donors[i].name  << endl;
            cout << "  Age   : " << donors[i].age   << endl;
            cout << "  City  : " << donors[i].city  << endl;
            cout << "  Phone : " << donors[i].phone << endl;
            cout << "  Units : " << donors[i].units << endl;
            cout << "  -----------------------------------------" << endl;
            found++;
        }
    }

    if (found == 0)
        cout << "  No donors found for: " << searchGroup << endl;
    else
        cout << "  Total found: " << found << endl;
}

// ══════════════════════════════════════════════════════════
// SEARCH BY NAME
// ══════════════════════════════════════════════════════════
void searchByName() {
    cout << "\n"; showLine();
    cout << "         SEARCH BY NAME" << endl;
    showLine();

    string keyword;
    cout << "  Enter name: ";
    getline(cin, keyword);

    int found = 0;
    cout << "\n  Results for: " << keyword << endl;
    cout << "  -----------------------------------------" << endl;

    for (int i = 0; i < totalDonors; i++) {
        if (donors[i].name.find(keyword) != string::npos) {
            cout << "  ID    : " << donors[i].id         << endl;
            cout << "  Name  : " << donors[i].name       << endl;
            cout << "  Blood : " << donors[i].bloodGroup << endl;
            cout << "  Phone : " << donors[i].phone      << endl;
            cout << "  Units : " << donors[i].units      << endl;
            cout << "  -----------------------------------------" << endl;
            found++;
        }
    }

    if (found == 0)
        cout << "  Not found: " << keyword << endl;
    else
        cout << "  Total found: " << found << endl;
}

// ══════════════════════════════════════════════════════════
// DELETE DONOR
// ══════════════════════════════════════════════════════════
void deleteDonor() {
    cout << "\n"; showLine();
    cout << "         DELETE DONOR" << endl;
    showLine();

    if (totalDonors == 0) {
        cout << "  No donors to delete!" << endl;
        return;
    }

    int delId;
    cout << "  Enter Donor ID to delete: ";
    cin  >> delId;
    cin.ignore();

    int foundAt = -1;

    for (int i = 0; i < totalDonors; i++) {
        if (donors[i].id == delId) {
            foundAt = i;
            break;
        }
    }

    if (foundAt == -1) {
        cout << "  ID not found!" << endl;
        return;
    }

    cout << "  Deleting: " << donors[foundAt].name << endl;

    // Shift array to fill the gap
    for (int i = foundAt; i < totalDonors - 1; i++) {
        donors[i] = donors[i + 1];
    }

    totalDonors--;

    // Auto-save after deletion
    saveToFile();

    cout << "  Donor deleted and saved!" << endl;
}

// ══════════════════════════════════════════════════════════
// UPDATE BLOOD UNITS
// ══════════════════════════════════════════════════════════
void updateUnits() {
    cout << "\n"; showLine();
    cout << "       UPDATE BLOOD UNITS" << endl;
    showLine();

    int updateId;
    cout << "  Enter Donor ID: ";
    cin  >> updateId;
    cin.ignore();

    for (int i = 0; i < totalDonors; i++) {
        if (donors[i].id == updateId) {
            cout << "  Donor: " << donors[i].name << endl;
            cout << "  Current Units: " << donors[i].units << endl;
            cout << "  Enter New Units: ";
            cin  >> donors[i].units;
            cin.ignore();

            // Auto-save after update
            saveToFile();

            cout << "  Updated and saved!" << endl;
            return;
        }
    }

    cout << "  ID not found!" << endl;
}

// ══════════════════════════════════════════════════════════
// SHOW STATISTICS
// ══════════════════════════════════════════════════════════
void showStats() {
    cout << "\n"; showLine();
    cout << "         BLOOD BANK STATISTICS" << endl;
    showLine();

    if (totalDonors == 0) {
        cout << "  No data yet!" << endl;
        return;
    }

    string groups[8] = {"A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-"};

    cout << "  Total Donors: " << totalDonors << endl;
    cout << "\n  Blood Group  | Donors | Total Units" << endl;
    cout << "  -------------|--------|------------" << endl;

    int totalUnits = 0;

    for (int g = 0; g < 8; g++) {
        int count = 0, units = 0;

        for (int i = 0; i < totalDonors; i++) {
            if (donors[i].bloodGroup == groups[g]) {
                count++;
                units += donors[i].units;
            }
        }

        if (count > 0) {
            cout << "  " << groups[g];
            cout << "           | " << count;
            cout << "      | " << units << endl;
            totalUnits += units;
        }
    }

    cout << "  -------------|--------|------------" << endl;
    cout << "  TOTAL        | " << totalDonors;
    cout << "      | " << totalUnits << endl;
}
