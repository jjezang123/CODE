#include<iostream>
#include<string>
#include<conio.h>

using namespace std;

string new_ID;
string new_p;

class Create_user {
public:
    void saveID() {
        cout << "New ID: ";
        cin >> new_ID;
    }

    void savePassword1() {
        cout << "New Password: ";
        char ch;
        while ((ch = _getch()) != 13) { // Enter key
            if (ch == 8) { // Backspace
                if (!pass1.empty()) {
                    cout << "\b \b"; // Erase the last character on the console
                    pass1.pop_back();
                }
            }
            else {
                pass1.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
    }

    void savePassword2() {
        cout << "Password confirmation: ";
        char ch;
        while ((ch = _getch()) != 13) { // Enter key
            if (ch == 8) { // Backspace
                if (!pass2.empty()) {
                    cout << "\b \b"; // Erase the last character on the console
                    pass2.pop_back();
                }
            }
            else {
                pass2.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
    }

    void savePassword3() {
        if (pass1 == pass2) {
            new_p = pass1;
            cout << "Complete setting new ID." << endl << endl;
        }
        else {
            cout << "Passwords do not match. Try again." << endl << endl;
            exit(0);
        }
    }
private:
    string pass1 = "";
    string pass2 = "";
};

class Login {
public:
    void Login_() {
        string ID;
        string password;
        cout << "Enter your ID: ";
        cin >> ID;
        cout << "Enter your password: ";
        char ch;
        while ((ch = _getch()) != 13) { // Enter key
            if (ch == 8) { // Backspace
                if (!password.empty()) {
                    cout << "\b \b"; // Erase the last character on the console
                    password.pop_back();
                }
            }
            else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl << endl;

        if (ID == new_ID && password == new_p) {
            cout << "You are logged in." << endl;
        }
        else {
            cout << "Login failed. Retry logging in." << endl;
            exit(0);
        }
    }

    void Greetings(string ID) {
        cout << endl;
        cout << "Welcome, " << ID << "." << endl << endl;
        cout << "Press Enter to continue...";
        cin.ignore(); // Ignore the newline character in the buffer
        cin.get(); // Wait for the user to press Enter
    }
};

int main() {
    Create_user Cu;
    Login LG;

    Cu.saveID();
    Cu.savePassword1();
    Cu.savePassword2();
    Cu.savePassword3();

    string ID = new_ID; // Store the new ID for greeting
    LG.Login_();
    LG.Greetings(ID);
}