//#include <winsock2.h>
//#include <WS2tcpip.h>
//#include <string>
//#include <iostream>
//#include <Windows.h>
//
//#pragma comment (lib, "ws2_32.lib")
//
//void main(int argc, char* argv[]) // We can pass in a command line option!!
//{
//    // Startup Winsock
//    WSADATA wsaData;
//    WORD version = MAKEWORD(2, 2);
//    int wsOk = WSAStartup(version, &wsaData);
//    if (wsOk != 0) {
//        std::cout << "Cant start Winsock!";
//        return;
//    }
//
//    // Create a hint structure for the server
//    sockaddr_in server;
//    server.sin_family = AF_INET;
//    server.sin_port = htons(54000);
//
//    char ip[] = "192.168.1.15";
//
//
//    gethostname(reinterpret_cast<char*>(malloc(20)), 20);
//
//    char localIP[20];
//    inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in*>(reinterpret_cast<addrinfo*>(malloc(sizeof(addrinfo)))->ai_addr)->sin_addr, localIP, sizeof(localIP));
//
//    std::cout << "Local IP: " << localIP << std::endl;
//
//    
//
//
//    //inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
//    inet_pton(AF_INET, "192.168.1.15", &server.sin_addr); // setting up where messages should go
//
//    // Socket creation
//    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
//   
//    
//    
//    /*  banner  */
//    std::cout << R"(
// ___  ___  ________  ________        ________  ___       ___  _______   ________   _________   
//|\  \|\  \|\   ___ \|\   __  \      |\   ____\|\  \     |\  \|\  ___ \ |\   ___  \|\___   ___\ 
//\ \  \\\  \ \  \_|\ \ \  \|\  \     \ \  \___|\ \  \    \ \  \ \   __/|\ \  \\ \  \|___ \  \_| 
// \ \  \\\  \ \  \ \\ \ \   ____\     \ \  \    \ \  \    \ \  \ \  \_|/_\ \  \\ \  \   \ \  \  
//  \ \  \\\  \ \  \_\\ \ \  \___|      \ \  \____\ \  \____\ \  \ \  \_|\ \ \  \\ \  \   \ \  \ 
//   \ \_______\ \_______\ \__\          \ \_______\ \_______\ \__\ \_______\ \__\\ \__\   \ \__\
//    \|_______|\|_______|\|__|           \|_______|\|_______|\|__|\|_______|\|__| \|__|    \|__|
//                                                                                               
//)" << std::endl;
//    /*   banner   */
//
//
//    std::cout << "out: " << out << "\n";
//    std::cout << "htons(54000): " << htons(54000) << "\n";
//    //std::cout << "server.sin_addr: " <<  << "\n\n";
//    
//    // Write out to that socket
//    std::string s(argv[1]);
//    std::string m = "m";
//    std::string mAdd = "a";
//
//    while (true) {
//        if (GetAsyncKeyState(VK_SPACE)) {
//            std::cout << "SPACE pressed\n";
//            int sendOk = sendto(out, m.c_str(), m.size() + 1, 0, (sockaddr*)&server, sizeof(server));
//
//            if (sendOk == SOCKET_ERROR) {
//                std::cout << "That didnt work! " << WSAGetLastError() << "\n";
//            }
//            std::cout << "Message "<< m << " sent\n\n";
//            Sleep(1000);
//        }
//        if (GetAsyncKeyState(VK_LSHIFT)) {
//            std::cout << "\nSPACE pressed\n";
//            int sendOk = sendto(out, mAdd.c_str(), mAdd.size() + 1, 0, (sockaddr*)&server, sizeof(server));
//
//            if (sendOk == SOCKET_ERROR) {
//                std::cout << "That didnt work! " << WSAGetLastError() << "\n";
//            }
//            std::cout << "Message " << mAdd << " sent\n\n";
//            Sleep(1000);
//        }
//    }
//
//    
//
//    // Close the socket
//
//
//    // Close down Winsock
//    WSACleanup();
//}

#include <iostream>
#include <winsock.h>

using namespace std;

int doit(int, char**)
{
    char ac[80];
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        cerr << "Error " << WSAGetLastError() <<
            " when getting local host name." << endl;
        return 1;
    }
    cout << "Host name is " << ac << "." << endl;

    struct hostent* phe = gethostbyname(ac);
    if (phe == 0) {
        cerr << "Yow! Bad host lookup." << endl;
        return 1;
    }

    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        cout << "Address " << i << ": " << inet_ntoa(addr) << endl;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        return 255;
    }

    int retval = doit(argc, argv);

    WSACleanup();

    return retval;
}