#ifndef LOCAL_RDNS_H
#define LOCAL_RDNS_H

#include "sniff.hpp"

typedef struct {
    unsigned char ip[MAX_ADDR_LEN];
    unsigned char mask[MAX_ADDR_LEN];
    char *serviceName;
} rDNSRecord;

class LRDNS {
    rDNSRecord *p;
    unsigned int n;
    unsigned int capacity;

    static int cmpServiceName(const void *a, const void *b); //rDNSRecord *

public:
    static int match(const void *a, const void *b); //rDNSRecord *

    LRDNS();
    ~LRDNS();

    int load(const char *filename);
    void clear();
    const rDNSRecord* GetService(const char *_serviceName, unsigned int *n) const;
};

#endif
