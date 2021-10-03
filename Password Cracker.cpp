#include <iostream>
#include <string> // to_string
#include <iomanip> // setprecision
#include <algorithm>

using namespace std;

bool stop = false;
long long amount = 0;
string password;
clock_t start;

const char Alphabet[72] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U','V', 'W', 'X', 'Y', 'Z', '-', '_', '.', '!', '#', '@', '%', '$', '&', '*'
};

const char AlphabetUpper[26] = {
     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U','V', 'W', 'X', 'Y', 'Z'
};

const char AlphabetLower[26] = {
     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

const char AlphabetUpperLower[52] = {
     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U','V', 'W', 'X', 'Y', 'Z'
};


const char AlphabetUpperNumber[36] = {
     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U','V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

const char AlphabetLowerNumber[36] = {
     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

const char OnlyNumeber[10] = {
     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

string separateWithCommas(long long num) {
    string s = to_string(num);
    int thousands = s.length() - 3;

    while (thousands > 0) {
        s.insert(thousands, ",");
        thousands -= 3;
    }

    return s;
}

void inline crack(unsigned int length, string current) {
    if (length == 0 && stop == false) {
        amount++;

        if (amount % 100000 == 0) {
            cout << '\r' << separateWithCommas(amount) << " - " << current << " - " << separateWithCommas(amount / ((float)(clock() - start) / CLOCKS_PER_SEC)) << " p/sec";
            cout.flush();
        }
        if (current == password) {
            stop = true;
        }
        return;
    }
    if (stop == false) {
        if (all_of(password.begin(), password.end(), isupper)) { // Check if password contains upper case
            for (unsigned int i = 0; i < 26; i++) {
                crack(length - 1, current + AlphabetUpper[i]); // Use only upper case alphabet
            }
        }
        else if (all_of(password.begin(), password.end(), islower)) { // Check if password contains lower case
            for (unsigned int i = 0; i < 26; i++) {
                crack(length - 1, current + AlphabetLower[i]); // Use only lower case alphabet
            }
        }
        else if (any_of(password.begin(), password.end(), islower) && (any_of(password.begin(), password.end(), isupper))) { // Check if password contains lower and upper case
            for (unsigned int i = 0; i < 52; i++) {
                crack(length - 1, current + AlphabetUpperLower[i]); // Use only lower case alphabet
            }
        }

        else if (all_of(password.begin(), password.end(), isdigit)) { // Check if password contains numbers
            if (all_of(password.begin(), password.end(), isupper)) { // Check if password contains upper case
                for (unsigned int i = 0; i < 36; i++) {
                    crack(length - 1, current + AlphabetUpperNumber[i]); // Use only upper case alphabet with number
                }
            }
            else if (all_of(password.begin(), password.end(), islower)) { // Check if password contains lower case
                for (unsigned int i = 0; i < 36; i++) {
                    crack(length - 1, current + AlphabetLowerNumber[i]); // Use only lower case alphabet with number
                }
            }
            else if (all_of(password.begin(), password.end(), isdigit)) { // Check if password contains only number
                for (unsigned int i = 0; i < 10; i++) {
                    crack(length - 1, current + OnlyNumeber[i]); // Use only number
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < 72; i++) {
                crack(length - 1, current + Alphabet[i]); // Else test all alphabet
            }
        }
        
    }
}

int main() {
    // Greet the user
    cout << "Welcome to Matt05's Brute Force Password Cracker!" << endl << "https://matt05.ml" << endl;
    cout << "What do you want your password to be? > ";
    cin >> password;

    cout << "\rAttempting to crack " << password << "..." << endl;

    start = clock();

    while (stop == false) {
        static unsigned int pwLength = 1;
        crack(pwLength, "");
        pwLength++;
        if (stop == true) {
            break;
        }
    }
    cout << "\rMatt05's BFPC cracked the password \"" << password << "\" in " <<
        separateWithCommas(amount) << " attempts and " << setprecision(2) << fixed <<
        (float)(clock() - start) / CLOCKS_PER_SEC << " seconds." << endl << endl <<
        "That's about " << setprecision(0) <<
        separateWithCommas(amount / ((float)(clock() - start) / CLOCKS_PER_SEC)) <<
        " passwords per second!" << endl << endl;
    system("pause"); 
    exit(0);

    return 0;
}