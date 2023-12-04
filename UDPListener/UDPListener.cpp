/*
// C++ UDP Transmitter

//#include "Network.h"
//#include "iostream"
//
//#pragma once
//
//int main()
//{
//    std::string IP = "127.0.0.1";
//    int PORT = 8888;
//
//    try
//    {
//        WSASession Session;
//        UDPSocket Socket;
//        std::string data = "hello world";
//        char buffer[100];
//
//        while (1)
//        {
//            std::cout << "Enter data to transmit : " << std::endl;
//            std::getline(std::cin, data);
//            Socket.SendTo(IP, PORT, data.c_str(), data.size());
//        }
//    }
//    catch (std::exception& ex)
//    {
//        std::cout << ex.what();
//    }
//}
// 
// C++ UDP Receiver
//
//#include "Network.h"
//#include "iostream"
//
//#pragma once

//int main()
//{
//    int PORT = 4210;
//
//    try
//    {
//        WSASession Session;
//        UDPSocket Socket;
//        char buffer[100];
//
//        Socket.Bind(PORT);
//        while (1)
//        {
//            sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));
//            std::string input(buffer);
//            std::cout << "Data received: " << input << std::endl;
//        }
//    }
//    catch (std::system_error& e)
//    {
//        std::cout << e.what();
//    }
//}*/

#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <Windows.h>
#include <iostream>
#include <ctime>

//enum conv { UTC, LOCAL };
//
//std::string fmt(char const* fmt, time_t p = time(NULL), conv c = LOCAL) {
//    char buffer[512];
//
//    struct tm n = c == LOCAL ? *localtime(&p) : *gmtime(&p);
//    strftime(buffer, sizeof(buffer), fmt, &n);
//    return std::string(buffer);
//}


#pragma comment (lib, "ws2_32.lib")

void main () {
    // Startup Winsock
    WSADATA wsaData;
    WORD version = MAKEWORD(2, 2);
    int wsOk = WSAStartup(version, &wsaData);
    if (wsOk != 0) {
        std::cout << "Cant start Winsock!";
        return;
    }

    //if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) { fprintf(stderr, "WSAStartup failed.\n"); exit(1); }

    /*.~~~~~~~~~~~~~.Server.~~~~~~~~~~~~~*/
    // Bind socket to ip adress and port
    SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverHint;
    serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(54000); // Convert from little to big endian
    /*.~~~~~~~~~~~~~.Server.~~~~~~~~~~~~~*/

    /*.~~~~~~~~~~~~~.Client.~~~~~~~~~~~~~*/
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);

    //inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    inet_pton(AF_INET, "192.168.1.15", &server.sin_addr); // setting up where messages should go

    // Socket creation
    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
    std::string m = "b";
    /*.~~~~~~~~~~~~~.Client.~~~~~~~~~~~~~*/


    if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
        std::cout << "Cant bind socket!" << WSAGetLastError() << std::endl;
        return;
    }
    
    std::cout << R"(
 ___  ___  ________  ________        ________  _______   ________  ___      ___ _______   ________     
|\  \|\  \|\   ___ \|\   __  \      |\   ____\|\  ___ \ |\   __  \|\  \    /  /|\  ___ \ |\   __  \    
\ \  \\\  \ \  \_|\ \ \  \|\  \     \ \  \___|\ \   __/|\ \  \|\  \ \  \  /  / \ \   __/|\ \  \|\  \   
 \ \  \\\  \ \  \ \\ \ \   ____\     \ \_____  \ \  \_|/_\ \   _  _\ \  \/  / / \ \  \_|/_\ \   _  _\  
  \ \  \\\  \ \  \_\\ \ \  \___|      \|____|\  \ \  \_|\ \ \  \\  \\ \    / /   \ \  \_|\ \ \  \\  \| 
   \ \_______\ \_______\ \__\           ____\_\  \ \_______\ \__\\ _\\ \__/ /     \ \_______\ \__\\ _\ 
    \|_______|\|_______|\|__|          |\_________\|_______|\|__|\|__|\|__|/       \|_______|\|__|\|__|
                                       \|_________|                                                    
)" << std::endl;


    std::cout << "socket: " << in << "\n\n";
    std::cout << "port: " << serverHint.sin_port << "\n\n";

    sockaddr_in client;
    int clientLength = sizeof(client);
    ZeroMemory(&client, clientLength);

    char buffer[2];

    // Enter a loop
    while (true)
    {
        time_t currentTime = time(0);
        tm localTime;

        if (localtime_s(&localTime, &currentTime) != 0) {
            std::cerr << "Error getting local time" << std::endl;
            return;
        }

        // Extract hours, minutes, and seconds
        int hours = localTime.tm_hour;
        int minutes = localTime.tm_min;
        int seconds = localTime.tm_sec;


        //std::cout << "Start\n";
        ZeroMemory(buffer, 2);
        // Wait for message
        int bytesIn = recvfrom(in, buffer, 2, 0, (sockaddr*)&client, &clientLength);
        if (bytesIn == SOCKET_ERROR) {
            std::cout << "Error receiving from client " << WSAGetLastError() << "\n";
            continue;
        }
        if (buffer[0] == 'm') { 
            std::cout << "\n\nWOW\n\n";
            /*INPUT input = { 0 };
            input.type = INPUT_KEYBOARD;
            input.ki.wVk=VkKeyScanA('arrow')*/
            //keybd_event(VK_RIGHT, 0x27, 0, 0);
            //keybd_event(VK_RIGHT, 0x27, KEYEVENTF_KEYUP, 0);
        }
        else if (buffer[0] == 'l') {
            std::cout << "\n \nb\n\n";
            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = 0x25;
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));
           /* keybd_event(VK_LEFT, 0x25, 0, 0);
            Sleep(200);
            keybd_event(VK_LEFT, 0x25, KEYEVENTF_KEYUP, 0);*/
        }
        else if (buffer[0] == 'r') {
            std::cout << "\n\nb\n\n";
            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = 0x27;
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));
            /*keybd_event(VK_RIGHT, 0x27, 0, 0);
            Sleep(200);
            keybd_event(VK_RIGHT, 0x27, KEYEVENTF_KEYUP, 0);*/
        }
        else {
            for (int x = 0; x < (sizeof(buffer) / sizeof(char)); x++) { std::cout << buffer[x] << "-"; }
            std::cout << "\n";
        }
        
        // Display message and client info
        char clientIp[256];
        ZeroMemory(clientIp, 256);

        inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
        
        if (buffer[0] == 't') {
            inet_pton(AF_INET, clientIp, &server.sin_addr);
            int sendOk = sendto(out, m.c_str(), m.size() + 1, 0, (sockaddr*)&server, sizeof(server));

            if (sendOk == SOCKET_ERROR) {
                std::cout << "That didnt work! " << WSAGetLastError() << "\n";
            }
            std::cout << "Message " << m << " sent to " << clientIp <<"\n\n";
        }

        std::cout << hours << ":" << minutes << ":" << seconds << " | Message received from " << clientIp << " : " << buffer << " \n";
        
    
    }

    // Close socket
    closesocket(in);
    /*//struct sockaddr_in si_me, si_other;
    //int s, i, blen, slen = sizeof(si_other);
    //char buf[BUFLEN];

    //s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //if (s == -1)
    //    die("socket");

    //memset((char*)&si_me, 0, sizeof(si_me));
    //si_me.sin_family = AF_INET;
    //si_me.sin_port = htons(1234);
    //si_me.sin_addr.s_addr = htonl(192.168.1.1);

    //if (bind(s, (struct sockaddr*)&si_me, sizeof(si_me)) == -1)
    //    die("bind");

    //int blen = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&si_other, &slen);
    //if (blen == -1)
    //    diep("recvfrom()");

    //printf("Data: %.*s \nReceived from %s:%d\n\n", blen, buf, inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

    ////send answer back to the client
    //if (sendto(s, buf, blen, 0, (struct sockaddr*)&si_other, slen) == -1)
    //    diep("sendto()");

    //closesocket(s);*/

    WSACleanup();
}