#ifndef CONNA_INCLUDE
#define CONNA_INCLUDE

#include <stdio.h>
#include <sniff.hpp>
#include <pcap.h>
#include <winsock2.h>
#include <QApplication>


class IPPacket {
    private:
        uint32_t sec;  //開始抓封包以來所經過的秒數
        uint32_t nsec; //奈秒數
        const uchar *pktdata;//pktdata是原始封包的內容(第三層開始)

    public:
        IPPacket();

        void SetSec(uint32_t _sec);
        void SetNsec(uint32_t _nsec);
        void SetDataPtr(const uchar *_pktdata);

        uint32_t GetSec() const;
        uint32_t GetNsec() const;
        const uchar* GetDataPtr() const;
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
};
/*
 * 伺服器  src ip
 * 檢查連線 dst IP
 */
class ConnState{
    private:
        ushort version;    //IPV4? IPV6?
        char ip[MAX_ADDR_LEN];//save dstip(Client IP)
        ushort dport;//dport
        uint32_t state; //0?(No connected) 1?(connected) 2?(useing the app)
        //uint32_t nconn; //number of connection
    public:
        ConnState();

        void SetMember(ushort _ver,char _ip[],uint32_t _state);
        void SetVer(uint32_t _ver);
        void SetIP(char _ip[]);
        void SetState(uint32_t _state);
        //void SetNConn();


        ushort GetVer();
        char* GetIP();
        uint32_t GetState();
        //uint32_t GetnConn();
        uint32_t checkConn(char clientIP[],uint32_t clientPort);

};

class ConnStateOutput{

    private:

    public:
        ConnStateOutput();
        void add(const ConnState &output); //插入輸出結果

};

int FB();

#endif

