#include <iostream>
#include <winsock2.h>
using namespace std;
 
int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
 
    char hostname[100];
    gethostname(hostname, sizeof(hostname));
    cout << "Hostname: " << hostname << endl;
 
    hostent* host = gethostbyname(hostname);
    unsigned char* ip = (unsigned char*)host->h_addr;
 
    cout << "IP Address: "
         << (int)ip[0] << "."
         << (int)ip[1] << "."
         << (int)ip[2] << "."
         << (int)ip[3] << endl;
 
    int first = ip[0];
    char cls;
 
    if(first <= 127) cls = 'A';
    else if(first <= 191) cls = 'B';
    else if(first <= 223) cls = 'C';
    else if(first <= 239) cls = 'D';
    else cls = 'E';
 
    cout << "Class: " << cls << endl;
 
    if(cls == 'A') {
        cout << "Network ID: " << first << endl;
        cout << "Host ID: " << ip[1] << "." << ip[2] << "." << ip[3] << endl;
    }
    else if(cls == 'B') {
        cout << "Network ID: " << first << "." << ip[1] << endl;
        cout << "Host ID: " << ip[2] << "." << ip[3] << endl;
    }
    else if(cls == 'C') {
        cout << "Network ID: " 
             << first << "." << ip[1] << "." << ip[2] << endl;
        cout << "Host ID: " << ip[3] << endl;
    }
 
    WSACleanup();
    return 0;
}