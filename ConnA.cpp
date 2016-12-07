#include "ConnA.hpp"


#include <QApplication>
#include <QHostInfo>

#ifdef __linux__
#include <arpa/inet.h>
#include <pcap.h>
#endif

/*

*/
//IPPacketInput




IPPacket::IPPacket() {
    pktdata = 0;
    nsec = sec = 0;
}

IPPacket::~IPPacket() {
}

void IPPacket::SetSec(uint32_t _sec) {
    sec = _sec;
}

void IPPacket::SetNsec(uint32_t _nsec) {
    nsec = _nsec;
}

void IPPacket::SetDataPtr(const unsigned char *_pktdata) {
    pktdata = _pktdata;
}

uint32_t IPPacket::GetSec() const {
    return sec;
}

uint32_t IPPacket::GetNsec() const {
    return nsec;
}

const uchar* IPPacket::GetDataPtr() const {
    return pktdata;
}

const IPPacket IPPacketInput::NULL_PACKET = IPPacket();


IPPacketInput::IPPacketInput() {
    p = (IPPacket*)malloc(0);
    n = c = 0;
}

const IPPacket& IPPacketInput::next(bool &more) {
    if(c >= n) {
        more = false;
        return NULL_PACKET;
    }
    else {
        more = true;
        return p[c++];
    }
}

void IPPacketInput::reset() {
    n = 0;
}

uint32_t IPPacketInput::cur() const {
    return c;
}

uint32_t IPPacketInput::N() const {
    return n;
}

uint32_t IPPacketInput::Count() const {
    return n;
}

uint32_t IPPacketInput::Length() const {
    return n;
}

const IPPacket& IPPacketInput::operator[](uint32_t index) const {
    if(index >= n) throw "Index out of bound";
    return p[index];
}

void IPPacketInput::add(IPPacket *pkt) {
    IPPacket *t;
    t = (IPPacket*)realloc(p, sizeof(*p) * (n + 1));

    p = t;
    p[n] = *pkt;
    n += 1;
}

int File2DS(const char *filename, IPPacketInput &pkts, void ***memPtr) {
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr ph;
    IPPacket ipp;
    pcap_t *pf;
    const unsigned char *pdata;
    unsigned char *npdata;
    unsigned int i, n;

    pf = pcap_open_offline_with_tstamp_precision(filename, PCAP_TSTAMP_PRECISION_NANO, errbuf);
    if(!pf) return 1;

    while((pdata = pcap_next(pf, &ph))) {
        npdata = (unsigned char*)malloc(sizeof(*npdata) * ph.caplen);
        ipp.SetDataPtr(npdata);
        ipp.SetSec((ph.ts).tv_sec);
        ipp.SetNsec((ph.ts).tv_usec);
        pkts.add(&ipp);
    }

    n = pkts.N();
    *memPtr = (void**)malloc(sizeof(**memPtr) * n);
    for(i = 0; i < n; i++)
        (*memPtr)[i] = (void*)pkts[i].GetDataPtr();

    return 0;
}

//ConnState
ushort ConnState::GetVer(){
    return version;
}
//init
ConnState::ConnState():version(0),ip(),dport(0),state(0){}

char* ConnState::GetIP(){
    return ip;
}

uint32_t ConnState::GetState(){
    return state;
}

//uint32_t ConnState::GetnConn(){return nconn;}

uint32_t ConnState::checkConn(char clientIP[],uint32_t clientPort){
    if(!strstr(ip,clientIP))
        if(clientPort == dport)return 1;
    return 0;

}

void ConnState::SetVer(uint32_t _ver){
    version =_ver;
}

void ConnState::SetIP(char _ip[]){
    memcpy(ip,_ip,MAX_ADDR_LEN);
}

void ConnState::SetState(uint32_t _state){
    state = _state;
}

//void ConnState::SetNConn(){nconn++;}

void ConnState::SetMember(ushort _ver,char _ip[],uint32_t _state){
    version=_ver;
    memcpy(ip,_ip,MAX_ADDR_LEN);
    state=_state;
    //nconn=_nconn;

}

ConnStateOutput::ConnStateOutput() {
    p = (ConnState*)malloc(0);
    n = 0;
}

//未完成
void ConnStateOutput::add(const ConnState &output)
{
    ConnState *t;
    t = (ConnState*)realloc(p, sizeof(*p) * (n + 1));

    p = t;
    p[n] = output;
    n += 1;
}

unsigned int ConnStateOutput::N() const {
    return n;
}



int FB(IPPacketInput input, ConnStateOutput& output,char* app) {

    ConnState state;
    sniff_ip* ip;
    sniff_tcp* tcp;
    uint32_t s,ts[3]={0},index = 0,ipHeaderLen,totalLength;
    ushort ver,serverPort,clientPort;
    uchar Proto;
    uchar* pkt;

    char serverIP[IP_ADDR_LEN],clientIP[IP_ADDR_LEN];

    while(input[index].GetDataPtr()){
        pkt=NULL;
        ip  = (sniff_ip*)pkt;
        ver = (ip->ip_vhl) >> 4;
        Proto = ip->ip_p;
        ipHeaderLen = (ip->ip_vhl & 0x0F) * 4;
        totalLength= ntohs(ip->ip_len);
        sprintf(serverIP ,"%u.%u.%u.%u" ,ip->saddr.byte1,
            ip->saddr.byte2 ,ip->saddr.byte3 ,ip->saddr.byte4);
        sprintf(clientIP ,"%u.%u.%u.%u" ,ip->daddr.byte1,
            ip->daddr.byte2 ,ip->daddr.byte3 ,ip->daddr.byte4);

        tcp = (sniff_tcp*)(pkt + (ipHeaderLen));
        serverPort = ntohs(tcp->th_sport);
        clientPort = ntohs(tcp->th_dport);

        while(ipHeaderLen >= 20){
            //if(strstr(app,"facebook") != NULL)
            if(ver == 4){
                //tcp?
                if(!(Proto == 6))break;

                //443?
                if(!(serverPort == 443))break;

                //DNS Reverse lookup
                QHostInfo HI = QHostInfo::fromName(serverIP);
                if(strstr((HI.hostName().toStdString().c_str()),app)==NULL)break;

                //checkconn
                if(state.checkConn(clientIP,clientPort))break;

                //state 簡單處理...
                if(totalLength<700){s = 1; ts[1] += 1;}
                else if(totalLength>=700){s = 2; ts[2] += 1;}
                else {s = 0; ts[0] +=1;}

                //setdata
                state.SetMember(ver,clientIP,s);
                output.add(state);
            }
            //if(strstr(app,"line") != NULL);
        }
        index++;
    }

    if(ts[2] > 0) return 2;
    else if(ts[1] > 0) return 1;
    else return 0;

}

/*
            if (tcp->th_flags & 0x08) printf("(PSH)");
            if (tcp->th_flags & 0x10) printf("(ACK)");
            if (tcp->th_flags & 0x02) printf("(SYN)");
            if (tcp->th_flags & 0x20) printf("(URG)");
            if (tcp->th_flags & 0x01) printf("(FIN)");
            if (tcp->th_flags & 0x04) printf("(RST)");
*/
