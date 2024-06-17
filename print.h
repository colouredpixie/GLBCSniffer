#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>

namespace print {
    #define STYLE(text) std::left << std::setfill(' ') << std::setw(30) << text << std::right 

    std::string baseColor = "\033[0m";
    std::string standardColor = "\033[92;1m";
    std::string incomingColor = "\033[36;1m";    
    std::string totalColor = "\033[93;1m";
    std::string currentColor;

    // Can be filled with local IP addresses dynamically
    std::vector<std::string> IPs{"127.0.0.1","192.168.88.255"};

    bool isIncomingPacket(std::string address) {
        for (std::string IP : IPs) {
            if (address == IP) { return true; }
        }
        return false;
    }

    // Prints packet header info
    void printInfo(const std::pair<struct ether_header *, struct iphdr *> info) {
        struct sockaddr_in source{0}, dest{0};
        source.sin_addr.s_addr = info.second->saddr;
        dest.sin_addr.s_addr = info.second->daddr;
        
        if (isIncomingPacket(inet_ntoa(dest.sin_addr))) { currentColor = incomingColor; } 
            else { currentColor = standardColor; }

        std::cout << "Packet analysis:" << std::endl;
        std::cout << currentColor << STYLE("Size") << baseColor << ntohs(info.second->tot_len) << std::endl;
        std::cout << currentColor << STYLE("Source") << baseColor << inet_ntoa(source.sin_addr) << std::endl;
        std::cout << currentColor << STYLE("Destination") << baseColor << inet_ntoa(dest.sin_addr) << std::endl;
    }

    // Prints global summary
    void printSum(int count, int sum)  {
        std::cout << std::setfill('-') << std::setw(50) << baseColor << std::endl;
        std::cout << totalColor << STYLE("Total packets caught") <<  baseColor << count << std::endl;
        std::cout << totalColor << STYLE("Total bytes") <<  baseColor << sum << std::endl;
        std::cout << totalColor << std::setfill('-') << std::setw(50) << baseColor << std::endl << std::endl;
    }
}