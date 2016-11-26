#include "ConnA.hpp"

#include <stdio.h>
#include <QApplication>


/*

*/
//IPPacketInput




IPPacket::IPPacket() {
    pktdata = 0;
    nsec = sec = 0;
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
    p = 0;
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

int File2DS(const char *filename, IPPacketInput &pkts) {

}
//ConnState
ushort ConnState::GetVer(){
    return version;
}

ConnState::ConnState(){

}

char* ConnState::GetIP(){
    return ip;
}

uint32_t ConnState::GetState(){
    return state;
}

uint32_t ConnState::GetnConn(){
    return nconn;
}

uint32_t ConnState::checkConn(char _ip[],uint32_t _sport,uint32_t _dport){

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

void ConnState::SetNConn(){
    nconn++;
}





int FB(IPPacketInput input, ConnStateOutput& output) {

    ConnState state;
    sniff_ip* ip;
    sniff_tcp* tcp;
    uint32_t s,n,index;
    s = 0;
    n = input.N();
    index = input.cur();

    const uchar* pkt;
    pkt = input[index].GetDataPtr();
    ip =(sniff_ip*)(pkt);
    tcp=(sniff_tcp*)(pkt+20);

    char srcIP[IP_ADDR_LEN],dstIP[IP_ADDR_LEN];

    if(n<20)return 0;
    while(index < n){
        //ipv4?
        if((ip->ip_vhl>>4) == 4){
            sprintf(srcIP,"%u.%u.%u.%u",ip->saddr.byte1,
                ip->saddr.byte2,ip->saddr.byte3,ip->saddr.byte4);
            sprintf(dstIP,"%u.%u.%u.%u",ip->daddr.byte1,
                ip->daddr.byte2,ip->daddr.byte3,ip->daddr.byte4);
            //檢查是否為連線是否為FB
            if(strcmp(srcIP,"31.13"))return 0;//字串相同回傳值為0
            //檢查連線是否存在
            if(state.checkConn(dstIP,tcp->th_sport,tcp->th_dport))return 1;

            //設定資料
            if((tcp->th_dport))
            if((tcp->th_sport==443))state.SetNConn();
            state.SetVer(4);
            state.SetIP(srcIP);
            if((ip->ip_len)<700)state.SetState(1);
            else if((ip->ip_len)>=700)state.SetState(2);

        }
    }

    return s;
}
