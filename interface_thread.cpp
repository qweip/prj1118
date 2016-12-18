#include "interface_thread.hpp"
#include "ConnA.hpp"

void Capturer::doWork() {
    IPPacket ipp;
    char *result = new char[PCAP_ERRBUF_SIZE];
    const u_char *pdata, *npdata;
    pcap_pkthdr *phktdr;
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

    if(pcap_datalink(phandle) == DLT_EN10MB) {
        while(pcap_next_ex(phandle, &phktdr, &pdata) >= 0) {
            npdata = (unsigned char*)malloc(sizeof(*npdata) * phktdr->caplen);
            memcpy((uchar*)npdata, pdata, phktdr->caplen);

            if(
                    (npdata[12] == 0x08 && npdata[13] == 0x00) ||  //IPv4
                    (npdata[12] == 0x86 && npdata[13] == 0xDD)     //IPv6
                    )
            {
                ipp.SetDataPtr(npdata + 14);
                ipp.SetSec((phktdr->ts).tv_sec);
                ipp.SetNsec((phktdr->ts).tv_usec);

                mutex->lock();
                (*ref_pkts).add(&ipp);
                mutex->unlock();
            }
        }
    }

    pcap_close(phandle);
    memset(result, 0, PCAP_ERRBUF_SIZE);
    emit resultReady(result);
}

void Capturer::SetDevName(const char *_devname) {
    devname = _devname;
}

void Capturer::SetContainer(IPPacketInput *pkts) {
    ref_pkts = pkts;
}

void Capturer::SetMutex(QMutex *m) {
    mutex = m;
}

ITHControl::ITHControl(const pcap_if_t dev, IPPacketInput *pkts) {
    in = dev;
    in.next = 0;
    _result = 0;
    ref_pkts = pkts;
    mutex = new QMutex();

    Capturer *worker = new Capturer;

    worker->SetDevName(in.name);
    worker->SetContainer(pkts);
    worker->SetMutex(mutex);

    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &ITHControl::operate, worker, &Capturer::doWork);
    connect(worker, &Capturer::resultReady, this, &ITHControl::handleResults);
    workerThread.start();
}

ITHControl::~ITHControl() {
    if(workerThread.isRunning())
        workerThread.terminate();
    delete mutex;
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

QMutex* ITHControl::GetMutex() {
    return mutex;
}

IPPacketInput* ITHControl::GetIPPacketInput() {
    return ref_pkts;
}
