#include <cstring>
#include <cstdio>

#include "localRDNS.hpp"

int LRDNS::cmpServiceName(const void *a, const void *b) { //rDNSRecord *
    rDNSRecord *c = (rDNSRecord*)a;
    rDNSRecord *d = (rDNSRecord*)b;

    if(!(c->serviceName) || !(d->serviceName)) {
        if(!c->serviceName) return -1;
        else return 1;
    }
    else return strcmp(c->serviceName, d->serviceName);
}

void LRDNS::tokenize(const char *str, int sepChr, char ***arr, size_t *size, int ignore) {
    const char *last, *sep, *end;
    char **a, *subs;
    size_t n, s;

    end = str + strlen(str);
    last = str - 1;
    n = 0;
    sep = str;
    a = (char**)malloc(0);
    while((sep = strchr(sep, sepChr))) {
        if(((size_t)sep == (size_t)(last + 1)) && ignore) {
            last = sep;
            sep += 1;
            continue;
        }
        else {
            s = (size_t)sep - (size_t)(last + 1);
            subs = (char*)malloc(s + 1);
            subs[s] = '\0';
            memcpy(subs, last + 1, s);
            a = (char**)realloc(a, sizeof(*a) * (n + 1));
            a[n] = subs;
            n += 1;
        }
        last = sep;
        sep += 1;
    }

    if(((size_t)sep != (size_t)(last + 1)) || ignore) {
        s = (size_t)end - (size_t)(last + 1);
        subs = (char*)malloc(s + 1);
        subs[s] = '\0';
        memcpy(subs, last + 1, s);
        a = (char**)realloc(a, sizeof(*a) * (n + 1));
        a[n] = subs;
        n += 1;
    }

    *size = n;
    *arr = a;
}

int LRDNS::parse(const char *str, unsigned char *ip, unsigned char *mask, char **serviceName) {
    char **line, **net, **ipstrs;
    size_t i, j, nToks, nNetParts, nIpPart, index, zeros;
    unsigned int v, ipType;
    int ret = 1;

    tokenize(str, ' ', &line, &nToks, 1);
    if(nToks != 2)goto line_fail;

    tokenize(line[0], '/', &net, &nNetParts, 1);
    if(nNetParts != 2)goto netpart_fail;

    tokenize(net[0], ':', &ipstrs, &nIpPart, 0);
    if(nIpPart == 1) {
        for(i = 0; i < nIpPart; i += 1)
            free(ipstrs[i]);
        free(ipstrs);
        tokenize(net[0], '.', &ipstrs, &nIpPart, 0);
        if(nIpPart != 4) goto ip_fail;
        ipType = 4;
    }
    else if(nIpPart > 9) goto ip_fail;
    else ipType = 6;


    switch(ipType) {
    case 4: //IPv4
        memset(ip, 0, MAX_ADDR_LEN);
        for(i = 0; i < 4; i += 1) {
            sscanf(ipstrs[i], "%u", &v);
            ip[i] = v;
        }
        break;
    case 6: //IPv6
        index = 0;
        for(i = 0; i < nIpPart; i += 1) {
            if(index >= 8) goto ip_fail;
            if(strlen(ipstrs[i])) {
                if(sscanf(ipstrs[i], "%x", &v) != 1) goto ip_fail;
                ip[(index << 1)]        = v >> 8;
                ip[(index << 1) + 1]    = v & 0xFF;
                index += 1;
            }
            else if(!i) { // ::(?)
                if(strlen(ipstrs[i + 1])) goto ip_fail;

                if(nIpPart == 3) { // ::
                    memset(ip, 0, MAX_ADDR_LEN);
                    index = 8;
                    break;
                }
                else {
                    zeros = 8 - nIpPart + 2;
                    if(zeros >= 8) goto ip_fail;
                    for(j = 0; j < zeros; j += 1) {
                        ip[(index + j) << 1]        = 0;
                        ip[((index + j) << 1) + 1]  = 0;
                    }
                    index += zeros;
                }
            }
            else if(!strlen(ipstrs[nIpPart - 1]) && i == nIpPart - 2) { // (?)::
                if(index != 7) goto ip_fail;
                ip[14] = 0;
                ip[15] = 0;
                index = 8;
                break;
            }
            else {
                zeros = 8 - nIpPart + 1;
                if(zeros >= 8) goto ip_fail;
                for(j = 0; j < zeros; j += 1) {
                    ip[(index + j) << 1]        = 0;
                    ip[((index + j) << 1) + 1]  = 0;
                }
                index += zeros;
            }
        }
        if(index != 8) goto ip_fail;
        break;
    default:
        break;
    }

    if(sscanf(net[1], "%u", &v) != 1) goto ip_fail;
    for(i = 0; i < MAX_ADDR_LEN; i += 1) {
        if(v >= 8) {
            mask[i] = 0xFF;
            v -= 8;
        }
        else if(v > 0) {
            mask[i] = ~(((0xFF) << v) >> v);
            v = 0;
        }
        else mask[i] = 0;
    }

    j = strlen(line[1]);
    *serviceName = (char*)malloc(j + 1);
    memcpy(*serviceName, line[1], j + 1);

    ret = 0;
ip_fail:
    for(i = 0; i < nIpPart; i += 1)
        free(ipstrs[i]);
    free(ipstrs);
netpart_fail:
    for(i = 0; i < nNetParts; i += 1)
        free(net[i]);
    free(net);
line_fail:
    for(i = 0; i < nToks; i += 1)
        free(line[i]);
    free(line);
    return ret;
}

void LRDNS::removecrlf(char *str) {
    char *p;
    if((p = strchr(str, 0x0A))) *p = 0;
    if((p = strchr(str, 0x0D))) *p = 0;
}

int LRDNS::match(const void *a, const void *b) { //rDNSRecord *
    unsigned char network1[MAX_ADDR_LEN], network2[MAX_ADDR_LEN];
    rDNSRecord *c = (rDNSRecord*)a;
    rDNSRecord *d = (rDNSRecord*)b;
    int i;

    for(i = 0; i < MAX_ADDR_LEN; i += 1) {
        network1[i] = (c->ip)[i] &(c->mask)[i];
        network2[i] = (d->ip)[i] &(d->mask)[i];
    }
    return memcmp(network1, network2, MAX_ADDR_LEN);
}

LRDNS::LRDNS() {
    p = (rDNSRecord*)malloc(sizeof(*p) * INITIAL_SIZE);
    n = 0;
    capacity = INITIAL_SIZE;
}

LRDNS::~LRDNS() {
    size_t i;
    for(i = 0; i < n; i += 1)
        free(p[i].serviceName);
    free(p);
}

void LRDNS::addRecord(const rDNSRecord *r) {
    if(n == capacity) {
        p = (rDNSRecord*)realloc(p, sizeof(*p) * (capacity << 1));
        capacity <<= 1;
    }
    p[n] = *r;
    n += 1;
}

int LRDNS::load(const char *filename) {
    char buf[64];
    FILE *file;
    rDNSRecord r;

    file = fopen(filename, "r");
    if(!file) return errno;

    while(fgets(buf, sizeof(buf), file)) {
        removecrlf(buf);
        if(parse(buf, r.ip, r.mask, &(r.serviceName))) {
            fclose(file);
            return 1;
        }
        addRecord(&r);;
    }

    fclose(file);
    return 0;
}

void LRDNS::clear() {
    size_t i;
    for(i = 0; i < n; i += 1)
        free(p[i].serviceName);
    memset(p, 0, sizeof(*p) * capacity);
    n = 0;
}

const rDNSRecord* LRDNS::GetService(const char *_serviceName, size_t *num) const {
    const rDNSRecord *res;
    rDNSRecord key;
    size_t start, end;
    key.serviceName = (char*)_serviceName;

    res = (const rDNSRecord*)bsearch(&key, p, n, sizeof(*p), LRDNS::cmpServiceName);

    end = start = ((size_t)res - (size_t)p) / sizeof(*p);
    while(start > 0) {
        if(cmpServiceName(&key, p + start - 1) == 0) start--;
        else break;
    }

    while(end < n - 1) {
        if(cmpServiceName(&key, p + end + 1) == 0) end++;
        else break;
    }

    if(num) *num = end - start + 1;
    return (const rDNSRecord*)(p + start);
}

rDNSRecord* LRDNS::GetService(const char *_serviceName, size_t *num) {
    rDNSRecord key, *res;
    size_t start, end;
    key.serviceName = (char*)_serviceName;

    res = (rDNSRecord*)bsearch(&key, p, n, sizeof(*p), LRDNS::cmpServiceName);

    end = start = ((size_t)res - (size_t)p) / sizeof(*p);
    while(start > 0) {
        if(cmpServiceName(&key, p + start - 1) == 0) start--;
        else break;
    }

    while(end < n - 1) {
        if(cmpServiceName(&key, p + end + 1) == 0) end++;
        else break;
    }

    if(num) *num = end - start + 1;
    return (rDNSRecord*)(p + start);
}
