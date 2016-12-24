#ifndef LOCAL_RDNS_H
#define LOCAL_RDNS_H

#include "sniff.hpp"
#include <cstdlib>

#define INITIAL_SIZE 8

typedef struct {
    unsigned char ip[MAX_ADDR_LEN];
    unsigned char mask[MAX_ADDR_LEN];
    char *serviceName;
} rDNSRecord;

class LRDNS {
    rDNSRecord *p;
    size_t n;
    size_t capacity;

    static int cmpServiceName(const void *a, const void *b); //rDNSRecord *
    static void tokenize(const char *str, int sepChr, char ***arr, size_t *size, int ignore);
    static int parse(const char *str, unsigned char *ip, unsigned char *mask, char **serviceName);
    static void removecrlf(char *str);

    void addRecord(const rDNSRecord *r);
public:
    static int match(const void *a, const void *b); //rDNSRecord *

    LRDNS();
    ~LRDNS();

    int load(const char *filename);
    void clear();
    const rDNSRecord* GetService(const char *_serviceName, size_t *num) const;
    rDNSRecord* GetService(const char *_serviceName, size_t *num);
};

#endif
