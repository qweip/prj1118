#include "updater.hpp"
#include <QMessageBox>
#include "mainwindow.h"

#define UPDATE_TIME 10
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
void Updater::doWork() {
    char buf[64];
    ConnStateOutput *o;
    IPPacketInput *pkts;
    QMutex *m;
    QTreeWidgetItem *item, *subitem;
    time_t now;
    uint i, j, k;

    connect(this, &Updater::UIClear, _w, &MainWindow::UIClear, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UIAddTop, _w, &MainWindow::UIAddTop, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UIAddSubItem, _w, &MainWindow::UIAddSubItem, Qt::BlockingQueuedConnection);
    connect(this, &Updater::UISetText, _w, &MainWindow::UISetText, Qt::BlockingQueuedConnection);

    while(1) {
        if((now = time(0)) - lastUpdate > UPDATE_TIME) {
            //ui->clear();
            UIClear();

            //item = new QTreeWidgetItem(ui);
            //item->setText(0, tr("Facebook"));
            UIAddTop("Facebook", &item);
            for(i = 0; i < n; i += 1) {
                m = controls[i].GetMutex();
                m->lock();

                pkts = controls[i].GetIPPacketInput();
                o = new ConnStateOutput();

                if(FB(*pkts, *o, "facebook") > 0) {
                    k = o->N();
                    for(j = 0; j < k; j += 1) {
                        ConnState::IP2Str(buf, (*o)[j].GetIP(), (*o)[j].GetVer());

                        //subitem = new QTreeWidgetItem(item);
                        UIAddSubItem(item, &subitem);

                        //subitem->setText(1, tr(buf));
                        UISetText(subitem, 1, buf);

                        sprintf(buf, "%hu", (*o)[j].GetPort());
                        //subitem->setText(2, tr(buf));
                        UISetText(subitem, 2, buf);

                        //subitem->setText(0, tr("Facebook"));
                        UISetText(subitem, 0, "Facebook");
                    }
                }

                pkts->clear();
                m->unlock();

                delete o;
            }
            lastUpdate = now;
        }
        else QThread::msleep(900);
    }
}
