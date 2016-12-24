#include "updater.hpp"
#include <QMessageBox>
#include "mainwindow.h"
#include "localRDNS.hpp"

#define UPDATE_TIME 3
static time_t lastUpdate = 0;

UpdateControl::UpdateControl(ITHControl *_controls, uint _n) {
    Updater *worker = new Updater;

    controls = _controls;
    n = _n;

    worker->SetController(_controls);
    worker->SetN(_n);

    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &UpdateControl::operate, worker, &Updater::doWork);
    connect(worker, &Updater::resultReady, this, &UpdateControl::handleResults);
    workerThread.start();
}

UpdateControl::~UpdateControl() {
    if(workerThread.isRunning())
        workerThread.terminate();
}

bool UpdateControl::isRunnung() const {
    return workerThread.isRunning();
}

bool UpdateControl::isFinished() const {
    return workerThread.isFinished();
}

uint UpdateControl::GetResult() const {
    return result;
}

void UpdateControl::handleResults(uint _result) {
    result = _result;
}

void Updater::SetController(ITHControl *pkts) {
    controls = pkts;
}

void Updater::SetN(uint _n) {
    n = _n;
}

extern MainWindow *_w;
extern LRDNS rDNS;
void Updater::doWork() {
    char buf[64];
    QBrush *Brushes;
    QColor *Colors;
    const char *ipstr;
    ConnStateOutput *o;
    IPPacketInput *pkts;
    QMutex *m;
    QTreeWidgetItem *item, *subitem, *portitem, **serviceItems;
    rDNSRecord **arr, *b;
    time_t now;
    uint i;
    size_t j, k, l, u, s, nServices, w;
    ushort ver;

    connect(this, &Updater::UIClear, _w, &MainWindow::UIClear, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UIAddTop, _w, &MainWindow::UIAddTop, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UIAddIP, _w, &MainWindow::UIAddIP, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UIAddSubItem, _w, &MainWindow::UIAddSubItem, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UISetBG, _w, &MainWindow::UISetBG, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UISetTextColor, _w, &MainWindow::UISetTextColor, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UISetText, _w, &MainWindow::UISetText, Qt::BlockingQueuedConnection);

    nServices = 0;
    rDNS.ResetIndex();
    while(rDNS.nextService(s))
        nServices += 1;

    Brushes = new QBrush[nServices];
    Colors = new QColor[nServices];
    arr = new rDNSRecord*[nServices];
    serviceItems = new QTreeWidgetItem*[nServices];

    rDNS.ResetIndex();
    b = rDNS.Base();
    for(i = 0; i < nServices; i += 1) {
        rDNS.nextService(s);
        arr[i] = b + s;
        Colors[i].setRgb(rDNS[s].r, rDNS[s].g, rDNS[s].b);
        Brushes[i].setColor(Colors[i]);
        Brushes[i].setStyle(Qt::SolidPattern);
        Colors[i].setRgb(rDNS[s].tr, rDNS[s].tg, rDNS[s].tb);
    }

    while(1) {
        if((now = time(0)) - lastUpdate > UPDATE_TIME) {
            //ui->clear();
            UIClear();

            for(w = 0; w < nServices; w += 1) {
                //item = new QTreeWidgetItem(ui);
                //item->setText(0, tr("Facebook"));
                UIAddTop(arr[w]->serviceName, &item);
                UISetBG(item, 3, Brushes[w]);
                UISetTextColor(item, 3, Colors[w]);
                serviceItems[w] = item;
            }

            for(i = 0; i < n; i += 1) {
                m = controls[i].GetMutex();
                m->lock();

                for(w = 0; w < nServices; w += 1) {
                    pkts = controls[i].GetIPPacketInput();
                    o = new ConnStateOutput();

                    if(FB(*pkts, *o, arr[w]->serviceName) > 0) {
                        while(o->nextIP(j)) {
                            ConnState::IP2Str(buf, (ipstr = (*o)[j].GetIP()), (ver = (*o)[j].GetVer()));
                            UIAddIP(buf, &subitem);
                            UIAddSubItem(serviceItems[w], &subitem, false);
                            UISetText(subitem, 1, buf);
                            //UISetBG(subitem, 3, facebookBrush);
                            //UISetTextColor(subitem, 3, facebookColor);

                            o->GetIPBound(ipstr, ver, l, u);
                            for(k = l; k <= u; k += 1) {
                                UIAddSubItem(subitem, &portitem, false);
                                sprintf(buf, "%hu", (*o)[k].GetPort());
                                UISetText(portitem, 2, buf);
                                //UISetBG(portitem, 3, facebookBrush);
                                //UISetTextColor(portitem, 3, facebookColor);
                                ipstr = (*o)[k].GetIP();
                                //free((void*)ipstr);
                            }
                        }
                    }
                    delete o;
                }
                pkts->clear();
                m->unlock();
            }

            lastUpdate = now;
        }
        else QThread::msleep(900);
    }

    delete[] Brushes;
    delete[] Colors;
    delete[] arr;
    delete[] serviceItems;
}
