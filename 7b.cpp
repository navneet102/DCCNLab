#include <iostream>
#include <sstream>
using namespace std;
 
int main(){
    string ip;
    cin >> ip;
    stringstream ss(ip);
    int a,b,c,d;
    char ch;
    ss >> a >> ch >> b >> ch >> c >> ch >> d;
 
    unsigned long addr = (a<<24) | (b<<16) | (c<<8) | d;
 
    cout << "32-bit address: " << addr << endl;
}