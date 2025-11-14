#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int calculateParity(const vector<int>& hammingCode, int p_n) {
    int parity = 0;
    int k = p_n - 1;
    for (int i = k; i < hammingCode.size(); i += (2 * p_n)) {
        for (int j = i; j < i + p_n && j < hammingCode.size(); j++) {
            parity ^= hammingCode[j];
        }
    }
    return parity;
}

int main() {
    string data_bits;
    cout << "Enter the data bits (e.g., 1011): ";
    cin >> data_bits;

    int m = data_bits.length();
    int r = 0;
    while (pow(2, r) < m + r + 1) {
        r++;
    }

    int n = m + r;
    vector<int> hammingCode(n, 0);
    int data_idx = m - 1;

    for (int i = n - 1; i >= 0; i--) {
        int pos = i + 1;
        bool isParityPos = false;
        for (int j = 0; j < r; j++) {
            if (pos == pow(2, j)) {
                isParityPos = true;
                break;
            }
        }

        if (!isParityPos) {
            if (data_idx >= 0) {
                hammingCode[i] = data_bits[data_idx] - '0';
                data_idx--;
            }
        }
    }

    for (int j = 0; j < r; j++) {
        int p_pos_power = pow(2, j);
        int p_index = p_pos_power - 1;
        hammingCode[p_index] = 0; 
        
        int p_val = calculateParity(hammingCode, p_pos_power);
        hammingCode[p_index] = p_val;
    }

    reverse(hammingCode.begin(), hammingCode.end());

    cout << "Data bits: " << data_bits << endl;
    cout << "Redundant bits (r): " << r << endl;
    cout << "Total bits (n): " << n << endl;
    cout << "Hamming Code: ";
    for (int bit : hammingCode) {
        cout << bit;
    }
    cout << endl;

    return 0;
}