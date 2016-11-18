#ifndef CONNA_INCLUDE
#define CONNA_INCLUDE

#include <stdio.h>

class IPPacket {
    private:
        uint32_t sec;  //開始抓封包以來所經過的秒數
        uint32_t nsec; //奈秒數
        uchar *pktdata;//pktdata是原始封包的內容(第三層開始)
};

class IPPacketInput{

    public:
        //IPPacketInput(uint32_t _sec=0,uint32_t _nsec=0)
        //    :sec(_sec),nsec(_nsec),pktdata(NULL){printf("IPPacketInput成員初始化完成!\n");}
        IPPacketInput();
        IPPacket next();//下一個封包的位址
        uint32_t n();   //取得有幾個封包
        IPPacket operator[](uint32_t index); //Exception 隨機存取用

    protected:

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
        //ConnState(int _version=0,uint32_t _state=0,uint32_t _nconn=0)
        //    :version(_version),ip(""),state(_state),nconn(_nconn){printf("ConnState成員初始化完成!\n");}
        ConnStateOutput();
        void add(ConnState output);


    protected:

};


int FB(IPPacketInput input, ConnStateOutput &output);

#endif
