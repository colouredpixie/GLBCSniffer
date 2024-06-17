#include "socket.h"
#include "print.h"

int main() 
{
    // Create a raw socket
    raw newRawSocket;

    // Use raw socket to loop through all the trafic and get info on screen real-time
    while (true) {
        // Receive packet
        newRawSocket.receivePacket();

        // Get packet info and total traffic summary
        printout::printInfo(newRawSocket.eth, newRawSocket.ip);
        printout::printSum(newRawSocket.packetCount, newRawSocket.total);
    }

    return 0;
}
