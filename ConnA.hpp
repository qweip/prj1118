#ifndef CONNA_INCLUDE
#define CONNA_INCLUDE

#include <stdio.h>
#include <sniff.hpp>
#include <pcap.h>
#ifdef __MINGW32__
#include <winsock2.h>
#endif
#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <QApplication>


class IPPacketInput;
class IPPacket {
    private:
        uint32_t sec;  //開始抓封包以來所經過的秒數
        uint32_t nsec; //奈秒數
        const uchar *pktdata;//pktdata是原始封包的內容(第三層開始)

    public:
        IPPacket();
        ~IPPacket();

        void SetSec(uint32_t _sec);
        void SetNsec(uint32_t _nsec);
        void SetDataPtr(const uchar *_pktdata);

        uint32_t GetSec() const;
        uint32_t GetNsec() const;
        const uchar* GetDataPtr() const;

    friend class IPPacketInput;
};

class IPPacketInput{
    private:
        IPPacket *p;    //Data
        uint32_t n;     //Count
        uint32_t c;     //Current Index

    public:
        const static IPPacket NULL_PACKET;

        IPPacketInput();

        const IPPacket& next(bool &more); //下一個封包的位址，輸出會放在output變數，當沒有封包的時候回傳false
        void reset(); //重設目前封包A
        uint32_t cur() const; //目前是第幾個封包(0-based)

        uint32_t N() const;   //取得有幾個封包
        uint32_t Count() const;
        uint32_t Length() const;

        const IPPacket& operator[](uint32_t index) const; //Exception(const char *) 隨機存取用

        void add(IPPacket *p);
        void clear();
};

class ConnState{
    private:
        ushort version;    //IPV4? IPV6?
        char ip[MAX_ADDR_LEN];//save dstip(Client IP)
        ushort dport;//host dport
        uint32_t state; //0?(No connected) 1?(connected) 2?(useing the app)

    public:
        ConnState();

        void SetMember(ushort _ver,char _ip[],uint32_t _state);
        void SetVer(uint32_t _ver);
        void SetIP(char _ip[]);
        void SetState(uint32_t _state);
        void SetPort(uint32_t _dport);

        ushort GetVer() const;
        const char *GetIP() const;
        ushort GetPort() const;
        uint32_t GetState() const;

        static void IP2Str(char *buf, const char *ip, ushort version);
};

class ConnStateOutput{

    private:
        ConnState *p;
        unsigned int n;

    public:
        ConnStateOutput();
        ~ConnStateOutput();
        void add(const ConnState &output); //插入輸出結果
        uint32_t checkConn(char clientIP[], uint32_t clientPort, ushort ver);
        const ConnState& operator[](uint32_t index) const;
        unsigned int N() const; //取得目前的物件總數
};

int FB(IPPacketInput input, ConnStateOutput& output, const char* app);
#endif

