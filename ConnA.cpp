#include "ConnA.hpp"


#include <QApplication>
#include <QHostInfo>
#include <QMessageBox>
#include "mainwindow.h"

#include <pcap.h>

#ifdef __linux__
#include <arpa/inet.h>
#endif

#ifdef __MINGW32__
#include <winsock.h>
#include <ws2tcpip.h>
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

void IPPacketInput::clear() {
    free(p);
    p = (IPPacket*)malloc(0);
    n = c = 0;
}

int File2DS(const char *filename, IPPacketInput &pkts, void ***memPtr) {
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr ph;
    IPPacket ipp;
    pcap_t *pf;
    const unsigned char *pdata;
    unsigned char *npdata;
    unsigned int i, n;

    pf = pcap_open_offline(filename,errbuf);//pcap_open_offline_with_tstamp_precision(filename, PCAP_TSTAMP_PRECISION_NANO, errbuf);
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
ushort ConnState::GetVer() const{
    return version;
}
//init
ConnState::ConnState():version(0),ip(),dport(0),state(0){}

const char* ConnState::GetIP() const{
    return ip;
}

ushort ConnState::GetPort() const {
    return dport;
}

uint32_t ConnState::GetState() const{
    return state;
}

uint32_t ConnState::GetnConBig() const{
    return nConBig;
}

void ConnState::IP2Str(char *buf, const char *ip, ushort version) {
    switch(version) {
    case 4:
        sprintf(buf, "%hu.%hu.%hu.%hu", (ushort)((const uchar *)ip)[0], (ushort)((const uchar *)ip)[1], (ushort)((const uchar *)ip)[2], (ushort)((const uchar *)ip)[3]);
        break;
    case 6:
        struct in6_addr v6addr;
        memcpy(&v6addr, ip, 16);
        /*sprintf(buf, "%hu%hu:%hu%hu:%hu%hu:%hu%hu:%hu%hu:%hu%hu:%hu%hu:%hu%hu",
                (ushort)((const uchar *)ip)[0], (ushort)((const uchar *)ip)[1], (ushort)((const uchar *)ip)[2], (ushort)((const uchar *)ip)[3],
                (ushort)((const uchar *)ip)[4], (ushort)((const uchar *)ip)[5], (ushort)((const uchar *)ip)[6], (ushort)((const uchar *)ip)[7],
                (ushort)((const uchar *)ip)[8], (ushort)((const uchar *)ip)[8], (ushort)((const uchar *)ip)[10], (ushort)((const uchar *)ip)[11],
                (ushort)((const uchar *)ip)[12], (ushort)((const uchar *)ip)[14], (ushort)((const uchar *)ip)[14], (ushort)((const uchar *)ip)[15]);*/
        inet6_ntoa(v6addr, buf, 255);
        break;
    default:
        break;
    }
}


/*uint32_t ConnState::checkConn(char clientIP[],uint32_t clientPort){
    if(!strstr(ip,clientIP))
        if(clientPort == dport)return 1;
    return 0;

}*/

void ConnState::SetVer(uint32_t _ver){
    version =_ver;
}

void ConnState::SetIP(char _ip[]){
    memcpy(ip,_ip,MAX_ADDR_LEN);
}

void ConnState::SetPort(uint32_t _dport){
    dport = _dport;
}


void ConnState::SetState(uint32_t _state){
    state = _state;
}

void ConnState::SetnConBig(uint32_t _nConBig){
    nConBig = _nConBig;
}

void ConnState::SetMember(ushort _ver,char _ip[],uint32_t _state){
    version=_ver;
    memcpy(ip,_ip,MAX_ADDR_LEN);
    state=_state;
}

ConnStateOutput::ConnStateOutput() {
    p = (ConnState*)malloc(0);
    n = 0;
}

static int CScmp(const void *a, const void *b) {
    ConnState *c= (ConnState*)a;
    ConnState *d= (ConnState*)b;
    int r;

    if(c->GetVer() > d->GetVer()) return 1;
    else if(c->GetVer() < d->GetVer()) return -1;
    else if((r = memcmp(c->GetIP(), d->GetIP(), MAX_ADDR_LEN) != 0)) return r;
    else if(c->GetPort() > d->GetPort()) return 1;
    else if(c->GetPort() < d->GetPort()) return -1;
    else return 0;
}

ConnStateOutput::~ConnStateOutput() {
    free(p);
}

void ConnStateOutput::add(const ConnState &output)
{
    ConnState *t;
    t = (ConnState*)realloc(p, sizeof(*p) * (n + 1));

    p = t;
    p[n] = output;
    n += 1;

    qsort(p, n, sizeof(*p), CScmp);
}

uint32_t ConnStateOutput::checkConn(char clientIP[], uint32_t clientPort, ushort ver){
    return (find(clientIP, clientPort, ver) ? 1 : 0);
}

 ConnState * ConnStateOutput::find(char clientIP[], uint32_t clientPort, ushort ver){
    ConnState *res;
    ConnState key;

    key.SetVer(ver);
    key.SetIP(clientIP);
    key.SetPort(clientPort);
    res = (ConnState*)bsearch(&key,p, n, sizeof(*p), CScmp);

    return res;
}

const ConnState& ConnStateOutput::operator[](uint32_t index) const {
    if(index >= n) throw "Index out of bound";
    return p[index];
}

unsigned int ConnStateOutput::N() const {
    return n;
}

int FB(IPPacketInput input, ConnStateOutput& output, const char *app) {
    ConnState state;
    sniff_ip* ip;
    sniff_tcp* tcp;
    uint32_t ts[3]={0},index = 0,ipHeaderLen,totalLength, lastSeen=0, nConBig = 0, n;
    ushort ver,serverPort,clientPort;
    uchar Proto;
    const uchar* pkt;

    char serverIP[256],clientIP[MAX_ADDR_LEN];

    n = input.N();
    for(index = 0; index < n; index += 1) {
        pkt = input[index].GetDataPtr();
        ip  = (sniff_ip*)pkt;
        ver = (ip->ip_vhl) >> 4;
        Proto = ip->ip_p;
        ipHeaderLen = (ip->ip_vhl & 0x0F) * 4;
        totalLength= ntohs(ip->ip_len);
        sprintf(serverIP ,"%u.%u.%u.%u" ,ip->saddr.byte1,
            ip->saddr.byte2 ,ip->saddr.byte3 ,ip->saddr.byte4);
        //sprintf(clientIP ,"%u.%u.%u.%u" ,ip->daddr.byte1,
        //    ip->daddr.byte2 ,ip->daddr.byte3 ,ip->daddr.byte4);
        memset(clientIP, 0, MAX_ADDR_LEN);
        clientIP[0] = ip->daddr.byte1;
        clientIP[1] = ip->daddr.byte2;
        clientIP[2] = ip->daddr.byte3;
        clientIP[3] = ip->daddr.byte4;

        tcp = (sniff_tcp*)(pkt + (ipHeaderLen));
        serverPort = ntohs(tcp->th_sport);
        clientPort = ntohs(tcp->th_dport);

        while(ipHeaderLen >= 20 && ipHeaderLen <= 60){
            //if(strstr(app,"facebook") != NULL)
            if(ver == 4){
                //tcp?
                if(!(Proto == 6)) { break; }

                //443?
                if(!(serverPort == 443)) { break; }

                //DNS Reverse lookup
                /*QHostInfo HI = QHostInfo::fromName(serverIP);
                if(HI.error() == QHostInfo::NoError) {
                    if(strstr((HI.hostName().toStdString().c_str()), app) == NULL)
                        break;
                }
                else break;*/

                if((size_t)strstr(serverIP, "31.13.") != (size_t)serverIP) break;


                //checkconn
                ConnState *res;
                if((res = output.find(clientIP,clientPort,ver))) {
                    state = *res;
                    if(totalLength<700)state.SetnConBig(0);
                    else if(totalLength >= 700){

                        state.SetnConBig(state.GetnConBig() + 1);
                        if(state.GetnConBig()>=10)state.SetnConBig(2);
                    }

                    break;
                }


                //state 簡單處理...
                if(totalLength >= 700) {
                    state.SetnConBig(1);
                }
                else {
                    state.SetnConBig(0);
                }

                if(input[index].GetSec() - lastSeen) {
                    if (nConBig <= 5) {
                        //background
                        state.SetnConBig(1);
                        state.SetState(1);
                        ts[1] += 1;
                    }
                }
                state.SetVer(ver);
                state.SetIP(clientIP);
                state.SetPort(clientPort);


                //setdata
                output.add(state);

                lastSeen = input[index].GetSec();

            }
            //if(strstr(app,"line") != NULL);
             break;
        }
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

void inet6_ntoa(struct in6_addr addr, char *buf, size_t maxLength) {
    char tmp[8];

    size_t curSize = 0, len;
    uint i;

    uint zeroStartMax = 8;
    uint zeroCountMax = 0;
    uint zeroStart = 8;
    uint zeroCount = 0;

    ushort v;

    for(i = 0; i < 8; i += 1) {
#ifdef __MINGW32_MAJOR_VERSION
        v = (addr.u.Byte[i << 1] << 8) | (addr.u.Byte[(i << 1) + 1]);
#else
        v = (addr.__in6_u.__u6_addr8[i << 1] << 8) | (addr.__in6_u.__u6_addr8[(i << 1) + 1]);
#endif
        if(!v) {
            if(zeroStart + zeroCount == i) {
                zeroCount += 1;
            }
            else {
                zeroStart = i;
                zeroCount = 1;
            }

            if(zeroCount > zeroCountMax) {
                zeroStartMax = zeroStart;
                zeroCountMax = zeroCount;
            }
        }
        else zeroCount = 0;
    }

    memset(buf, 0, maxLength);
    for(i = 0; i < 8; i += 1) {
        if(i == zeroStartMax) {
            if(zeroCountMax + i == 8) {
                tmp[0] = ':'; tmp[1] = ':'; tmp[2] = '\0';
                curSize += 2;
            }
            else {
                tmp[0] = ':'; tmp[1] = '\0';
                curSize += 1;
            }
            strncat(buf, tmp, maxLength - curSize);

            i += zeroCountMax - 1;
        }
        else {
#ifdef __MINGW32_MAJOR_VERSION
            v = (addr.u.Byte[i << 1] << 8) | (addr.u.Byte[(i << 1) + 1]);
#else
            v = (addr.__in6_u.__u6_addr8[i << 1] << 8) | (addr.__in6_u.__u6_addr8[(i << 1) + 1]);
#endif
            if(i == 0) len = sprintf(tmp, "%hx", v);
            else len = sprintf(tmp, ":%hx", v);
            strncat(buf, tmp, maxLength - curSize);
            curSize += len;
        }
    }
}
