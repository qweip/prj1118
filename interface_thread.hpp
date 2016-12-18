#ifndef INTERFACE_THREAD_HPP
#define INTERFACE_THREAD_HPP

#include <QThread>
#include <pcap.h>

class Capturer : public QObject
{
    Q_OBJECT

    const char *devname;

public:
    void SetDevName(const char *_devname);

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
    char *_result;
public:
    ITHControl(const pcap_if_t dev);

    ~ITHControl();

    bool isRunnung() const;
    bool isFinished() const;
    const char* GetResult() const;
    void GetInterface(pcap_if_t *dev) const;

public slots:
    void handleResults(char *result);

signals:
    void operate();
};

#endif // INTERFACE_THREAD_HPP
