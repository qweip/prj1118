#include "dnshandler.hpp"

void DNSHandler::SetSemaphore(QSemaphore *_s) {
    s = _s;
}

void DNSHandler::handleResult() {
    s->release();
}
