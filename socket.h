#pragma once

#include <iostream>
#include <sys/socket.h> // for socket
#include <cstdlib>
#include <unistd.h>
#include <netinet/if_ether.h> // for ether_header - duplicate
#include <netinet/ip.h> // for ip header - duplicate 
#include <arpa/inet.h> // duplicate

#define BUFSIZE 74 //Ethernet header + IP header // 65536 // maximum IP packet size

class raw
{
public:
    int sockfd;
    struct sockaddr saddr;
    socklen_t saddr_len = sizeof(saddr);
    unsigned char *buffer;

    struct ether_header *eth;
    struct iphdr *ip;

    int packetCount;
    int total;

    raw() : packetCount(0), total(0) {
        sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
        if (sockfd < 0) {
            std::cout << "Socket creation failed" << std::endl;
        }

        buffer = new unsigned char[BUFSIZE]{0};
    }

    void receivePacket() {
        int data_size = recvfrom(sockfd, buffer, BUFSIZE, 0, &saddr, &saddr_len);
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

    ~raw() {
        delete[] buffer;
        close(sockfd);
    }
};