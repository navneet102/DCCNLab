// character_stuffing.cpp
#include <iostream>
#include <string>

using namespace std;

string characterStuffing(string data, char flag, char esc) {
    string stuffed_data = "";
    stuffed_data += flag;

    for (int i = 0; i < data.length(); i++) {
        if (data[i] == flag || data[i] == esc) {
            stuffed_data += esc;
        }
        stuffed_data += data[i];
    }

    stuffed_data += flag;
    return stuffed_data;
}

string characterDestuffing(string stuffed_data, char flag, char esc) {
    string destuffed_data = "";

    for (int i = 1; i < stuffed_data.length() - 1; i++) {
        if (stuffed_data[i] == esc) {
            i++;
            destuffed_data += stuffed_data[i];
        } else {
            destuffed_data += stuffed_data[i];
        }
    }
    return destuffed_data;
}

int main() {
    string data;
    char flag = 'F';
    char esc = 'E';

    cout << "Enter data: ";
    getline(cin, data);

    string stuffed = characterStuffing(data, flag, esc);
    cout << "Stuffed:   " << stuffed << endl;

    string destuffed = characterDestuffing(stuffed, flag, esc);
    cout << "Destuffed: " << destuffed << endl;

    return 0;
}