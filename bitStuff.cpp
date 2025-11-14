// bit_stuffing.cpp
#include <iostream>
#include <string>

using namespace std;

string bitStuffing(string data) {
    string stuffed_data = "";
    int one_count = 0;

    for (char bit : data) {
        if (bit == '1') {
            one_count++;
        } else {
            one_count = 0;
        }
        
        stuffed_data += bit;

        if (one_count == 5) {
            stuffed_data += '0';
            one_count = 0;
        }
    }
    return stuffed_data;
}

string bitDestuffing(string stuffed_data) {
    string destuffed_data = "";
    int one_count = 0;

    for (int i = 0; i < stuffed_data.length(); i++) {
        if (stuffed_data[i] == '1') {
            one_count++;
        } else {
            one_count = 0;
        }

        destuffed_data += stuffed_data[i];

        if (one_count == 5) {
            if (i + 1 < stuffed_data.length() && stuffed_data[i + 1] == '0') {
                i++; 
            }
            one_count = 0;
        }
    }
    return destuffed_data;
}

int main() {
    string data;
    string flag = "01111110";

    cout << "Enter bit string (e.g., 0111111101): ";
    cin >> data;

    string stuffed = bitStuffing(data);
    cout << "Stuffed:   " << flag << stuffed << flag << endl;

    string destuffed = bitDestuffing(stuffed);
    cout << "Destuffed: " << destuffed << endl;

    return 0;
}