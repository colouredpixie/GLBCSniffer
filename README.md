## Linux sniffer / packet analyzer console app
**C/C++ implementation, compiled using G++ Makefile _(requires SU rights to have access to socket)_**

App uses RAW socket to capture all device packets and analyses ethernet and IP headers to get source and destination adresses.
Summary is provided real-time to the console using ANSI colours and IO manipulators.