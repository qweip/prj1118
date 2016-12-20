#ifndef DNSHANDLER_HPP
#define DNSHANDLER_HPP

#include <QObject>
#include <QSemaphore>

class DNSHandler : public QObject {
    Q_OBJECT

    QSemaphore *s; //ref

public:

    void SetSemaphore(QSemaphore *_s) ;

public slots:
    void handleResult() ;
};

#endif // DNSHANDLER_HPP
