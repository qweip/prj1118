#include <cstdlib>
#include <cstring>

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

int LRDNS::match(const void *a, const void *b) {

}

/*LRDNS::LRDNS();
LRDNS::~LRDNS();

int LRDNS::load(const char *filename);
void LRDNS::clear();
const rDNSRecord* LRDNS::GetService(const char *_serviceName, unsigned int *n) const;
*/
