#ifndef INTERFACE_THREAD_HPP
#define INTERFACE_THREAD_HPP

#include <QThread>
#include <QMutex>
#include <pcap.h>
#include "ConnA.hpp"

class Capturer : public QObject
{
    Q_OBJECT

    const char *devname; //ref
    IPPacketInput *ref_pkts; //ref
    QMutex *mutex; //ref

public:
    void SetDevName(const char *_devname);
    void SetContainer(IPPacketInput *pkts);
    void SetMutex(QMutex *m);

public slots:
    void doWork();

signals:
    void resultReady(char *result);
};

//Interface Thread Control
class ITHControl : public QObject
{
    Q_OBJECT

    QThread workerThread;
    pcap_if_t in;
    char *_result; //clean outside
    IPPacketInput *ref_pkts; //ref
    QMutex *mutex; //auto

public:
    ITHControl(const pcap_if_t dev, IPPacketInput *pkts);

    ~ITHControl();

    bool isRunnung() const;
    bool isFinished() const;
    const char* GetResult() const;
    void GetInterface(pcap_if_t *dev) const;
    QMutex* GetMutex();
    IPPacketInput* GetIPPacketInput();

public slots:
    void handleResults(char *result);

signals:
    void operate();
};

#endif // INTERFACE_THREAD_HPP
