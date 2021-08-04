#pragma once
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
using namespace std;

addrinfo* findHost(string ip, string port);
string getPayload(string target, string cmd);
void telnet(addrinfo* addr, string target);
