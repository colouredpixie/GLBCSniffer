#pragma once


#include <iostream>
#include <cstring>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>


// incoming packets
// outgoing packets

namespace printout {
    std::string baseColor = "\033[0m";
    std::string headerColor = "\033[36m";
    std::string totalColor = "\033[32m";

void printInfo(const struct ether_header *eth, const struct iphdr *ip) {
    struct sockaddr_in source, dest;
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ip->saddr;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = ip->daddr;

    std::string color = headerColor;
    std::string address = inet_ntoa(dest.sin_addr) ;
    if (address == "127.0.0.1") {
        color = "\033[35m";
        std::cout << color << "Incoming packet:" << baseColor << std::endl;
    } else {
        std::cout << color << "Outgoing packet:" << baseColor << std::endl;
    }
    std::cout << color << "Size of Packet   : " << baseColor << ntohs(ip->tot_len) << std::endl;
    std::cout << color << "Source           : " << baseColor << inet_ntoa(source.sin_addr) << std::endl;
    std::cout << color << "Destination      : " << baseColor << inet_ntoa(dest.sin_addr) << std::endl;
}

// summary
void printSum(int count, int sum)  {
    std::cout << "___________________________________" << std::endl << std::endl;
    std::cout << "Packets caught   : " <<  count << std::endl;
    std::cout << "Total bytes      : " <<  sum << std::endl;
    std::cout << "___________________________________" << std::endl << std::endl;
}
}