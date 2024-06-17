#pragma once

#include <iostream>
#include <sys/socket.h>         
#include <unistd.h>             
#include <netinet/if_ether.h>   
#include <netinet/ip.h>         

#define BUFSIZE 74 // max ethernet header + IP header size

class raw
{
    int sockfd;
    struct sockaddr saddr;
    socklen_t saddrLen = sizeof(saddr);
    unsigned char *buffer;

    struct ether_header *eth;
    struct iphdr *ip;

    int packetCount;
    int total;

public:
    raw() : packetCount(0), total(0) {
        sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));                     
        if (sockfd < 0) {
            std::cout << "Socket creation failed" << std::endl;
        }

        buffer = new unsigned char[BUFSIZE]{0};
    }

    // Places the received message into the buffer
    void receivePacket() {
        int data_size = recvfrom(sockfd, buffer, BUFSIZE, 0, &saddr, &saddrLen);    
        if (data_size < 0) {
            std::cout << "Receive header data failed" << std::endl;
            return;
        }

        // Get Ethernet and IP headers
        eth = (struct ether_header *)buffer;
        ip = (struct iphdr *)(buffer + sizeof(struct ether_header));

        // Update counter and total traffic
        packetCount++;
        total += ntohs(ip->tot_len);
    }

    std::pair<struct ether_header *, struct iphdr *> getInfo() { return std::make_pair(eth, ip); }

    int getCount() { return packetCount; }

    int getTotal() { return total; }

    ~raw() {
        delete[] buffer;
        close(sockfd);
    }
};