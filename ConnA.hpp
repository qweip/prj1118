#ifndef CONNA_INCLUDE
#define CONNA_INCLUDE

#include <stdio.h>

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
        IPPacketInput();

        const IPPacket& next(bool &more); //下一個封包的位址，輸出會放在output變數，當沒有封包的時候回傳false
        void reset(); //重設目前封包
        uint32_t cur(); //目前是第幾個封包(0-based)

        uint32_t N() const;   //取得有幾個封包
        uint32_t Count() const;
        uint32_t Length() const;

        const IPPacket& operator[](uint32_t index) const; //Exception 隨機存取用
};

class ConnState{
    private:
        int version;    //IPV4? IPV6
        uchar ip[16];   //Record IP
        uint32_t state; //0?(No connected) 1?(connected) 2?(useing the app)
        uint32_t nconn; //number of connection
};

class ConnStateOutput{

    public:
        ConnStateOutput();

        void add(const ConnState &output); //插入輸出結果
};

#endif
