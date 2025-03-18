#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DigitalDiary {
private:
    string username, password;
    string filename;

public:
    void registerUser() {
        cout << "\n===============================";
        cout << "\n        REGISTER HERE           ";
        cout << "\n===============================\n";
        cout << "\nEnter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;

        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << endl;
            file.close();
            cout << "\n✅ Registration successful! Please login to continue.\n";
        }
        else {
            cout << "\n❌ Error: Unable to open file for registration.\n";
        }
    }

    bool loginUser() {
        string user, pass;
        cout << "\n===============================";
        cout << "\n          LOGIN HERE           ";
        cout << "\n===============================\n";
        cout << "\nEnter username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;

        ifstream file("users.txt");
        if (!file.is_open()) {
            cout << "\n❌ Error: Unable to open file for login.\n";
            return false;
        }

        string u, p;
        while (file >> u >> p) {
            if (u == user && p == pass) {
                username = user;
                filename = username + "_diary.txt";
                cout << "\n✅ Login successful! Welcome, " << username << "!\n";
                file.close();
                return true;
            }
        }
        file.close();
        cout << "\n❌ Invalid credentials! Please try again.\n";
        return false;
    }

    void addEntry() {
        string entry;
        cout << "\n===============================";
        cout << "\n       ADD DIARY ENTRY         ";
        cout << "\n===============================\n";
        cout << "\nWrite your diary entry: ";
        cin.ignore();
        getline(cin, entry);

        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "-----------------------------\n";
            file << entry << endl;
            file << "-----------------------------\n";
            file.close();
            cout << "\n✅ Entry added successfully!\n";
        }
        else {
            cout << "\n❌ Error: Unable to open diary file.\n";
        }
    }

    void viewEntries() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "\n❌ No diary entries found.\n";
            return;
        }

        string line;
        cout << "\n===============================";
        cout << "\n       YOUR DIARY ENTRIES      ";
        cout << "\n===============================\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << "\n================================\n";
        file.close();
    }

    void deleteEntries() {
        ofstream file(filename, ios::trunc);
        if (file.is_open()) {
            file.close();
            cout << "\n✅ All diary entries deleted!\n";
        }
        else {
            cout << "\n❌ Error: Unable to clear diary file.\n";
        }
    }
};

int main() {
    DigitalDiary diary;
    int choice;
    bool loggedIn = false;

    cout << "\n*************************************";
    cout << "\n   WELCOME TO YOUR DIGITAL DIARY    ";
    cout << "\n*************************************\n";

    while (!loggedIn) {
        cout << "\n1️⃣  Register\n2️⃣  Login\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            diary.registerUser();
        }
        else if (choice == 2) {
            loggedIn = diary.loginUser();
        }
        else {
            cout << "\n❌ Invalid choice, try again.\n";
        }
    }

    do {
        cout << "\n1️⃣  Add Entry\n2️⃣  View Entries\n3️⃣  Delete Entries\n4️⃣  Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: diary.addEntry(); break;
        case 2: diary.viewEntries(); break;
        case 3: diary.deleteEntries(); break;
        case 4: cout << "\n👋 Goodbye! See you next time.\n"; break;
        default: cout << "\n❌ Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}