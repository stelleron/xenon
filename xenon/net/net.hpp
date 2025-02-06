#ifndef XENON_NET
    #define XENON_NET

    #include<sys/socket.h>
    #include<netinet/in.h>
    #include<arpa/inet.h>
    #include<unistd.h>
    #include<string>

    namespace xenon {
        enum IPAddrType {IPV4, IPV6};

        class Socket {
            public:
                Socket();
                ~Socket();
        };

        class TCPSocket : Socket {

        };

        class UDPSocket : Socket {

        };

        class TCPListener : Socket {

        };

        class FTP {

        };

        class HTTP {

        };

        class IPAddress {
            int ip_addr;
            IPAddrType ip_type;

            public:
                // IPv4
                IPAddress(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3); 
                IPAddress(unsigned char bytes[4]);
                // IPv6
                IPAddress(int addr);
                ~IPAddress();

                std::string toString();
                int toInt();

        };

        class Packet {

        };
    }
#endif