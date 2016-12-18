#include "interface_thread.hpp"

void Capturer::doWork() {
    char *result = new char[PCAP_ERRBUF_SIZE];
    const u_char *pdata;
    pcap_pkthdr phktdr;
    pcap_t *phandle;

    phandle = pcap_create(devname, result);
    if(!phandle) {
        emit resultReady(result);
        return;
    }

    if(pcap_activate(phandle) < 0) {
        pcap_close(phandle);
        pcap_perror(phandle, result);
        emit resultReady(result);
        return;
    }

    while((pdata = pcap_next(phandle, &phktdr))) {

    }

    memset(result, 0, PCAP_ERRBUF_SIZE);
    emit resultReady(result);
}

void Capturer::SetDevName(const char *_devname) {
    devname = _devname;
}

ITHControl::ITHControl(const pcap_if_t dev) {
    in = dev;
    in.next = 0;

    Capturer *worker = new Capturer;
    worker->SetDevName(in.name);
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &ITHControl::operate, worker, &Capturer::doWork);
    connect(worker, &Capturer::resultReady, this, &ITHControl::handleResults);
    workerThread.start();
}

ITHControl::~ITHControl() {
    workerThread.quit();
    workerThread.wait();
}

void ITHControl::handleResults(char *result) {
    _result = result;
}

bool ITHControl::isRunnung() const {
    return workerThread.isRunning();
}

bool ITHControl::isFinished() const {
    return workerThread.isFinished();
}

const char* ITHControl::GetResult() const {
    return _result;
}

void ITHControl::GetInterface(pcap_if_t *dev) const {
    memcpy(dev, &in, sizeof(in));
}
