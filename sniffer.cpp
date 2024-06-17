#include "socket.h"
#include "print.h"

int main() 
{
    // Create a raw socket
    raw newRawSocket;

    // Use raw socket to loop through all the trafic and get info on screen real-time
    while (true) {
        // Receive each packet
        newRawSocket.receivePacket();

        // Print packet info and total traffic summary 
        print::printInfo(newRawSocket.getInfo());
        print::printSum(newRawSocket.getCount(), newRawSocket.getTotal());
    }

    return 0;
}
