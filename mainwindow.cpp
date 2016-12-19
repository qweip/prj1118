#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConnA.hpp"
#include "interface_thread.hpp"
#include "updater.hpp"

#define MAX_DEV_NAME 256

char pcapErrBuf[PCAP_ERRBUF_SIZE];

pcap_if_t *head = 0;

pcap_if_t *devs;
char **devNames = 0;
uint nDevs = 0;

UpdateControl *_update = 0;
ITHControl *monDevs = 0;
IPPacketInput *pkts = 0;
uint nMonDevs = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

static void ShowNormalMsgBox(const char *msg) {
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void MainWindow::on_pushButton_clicked()
{
    ShowNormalMsgBox("Button1 clicked");
}

static void FindAllInterfaces(QListWidget *qlw) {
    char devName[MAX_DEV_NAME], addrStr[64], netmaskStr[64], buf[32], *_addr, *interfaceInfo;
    sockaddr_in addrIn;
    QString *qs;
    QListWidgetItem *litem;
    size_t totalStrLen;
    pcap_if_t *cur;
    uint count, i;

    if(head) pcap_freealldevs(head);
    if(pcap_findalldevs(&head, pcapErrBuf) != 0) {
        ShowNormalMsgBox(pcapErrBuf);
        return;
    }

    qlw->clear();
    cur = head;
    count = 0;
    while(cur) {
        memcpy(&addrIn, cur->addresses->addr, sizeof(addrIn));
        _addr = inet_ntoa(addrIn.sin_addr);
        strncpy(addrStr, _addr, sizeof(addrStr) - 1);

        memcpy(&addrIn, cur->addresses->netmask, sizeof(addrIn));
        _addr = inet_ntoa(addrIn.sin_addr);
        strncpy(netmaskStr, _addr, sizeof(netmaskStr) - 1);

        totalStrLen = strlen(cur->description) + strlen(addrStr) + strlen(netmaskStr);
        interfaceInfo = new char[totalStrLen + 1 + 4];
        sprintf(interfaceInfo, "%s (%s/%s)", cur->description, addrStr, netmaskStr);
        qs = new QString(interfaceInfo);

        qlw->addItem(*qs);
        delete[] interfaceInfo;
        delete qs;

        litem = qlw->item(count);
        litem->setFlags(litem->flags() | Qt::ItemIsUserCheckable);
        litem->setCheckState(Qt::Unchecked);

        count += 1;
        cur = cur->next;
    }

    sprintf(buf, "%u interfaces found.", count);
    ShowNormalMsgBox(buf);

    if(devNames) {
        for(i = 0; i < nDevs; i += 1) delete[] devNames[i];
        delete[] devNames;
    }
    devNames = new char*[count];

    if(devs) delete[] devs;
    devs = new pcap_if_t[count];

    cur = head;
    for(i = 0; i < count; i += 1, cur = cur->next) {
        strncpy(devName, cur->name, sizeof(devName) - 1);

        devNames[i] = new char[(totalStrLen = strlen(devName)) + 1];
        memcpy(devNames[i], devName, totalStrLen + 1);

        memcpy(devs + i, cur, sizeof(*cur));
        devs[i].next = 0;
    }
    nDevs = count;
}

void MainWindow::on_pushButton_4_clicked()
{
    FindAllInterfaces(ui->listWidget);
}

void MainWindow::on_pushButton_3_clicked()
{
    QListWidgetItem *item;
    int i, j, c, d;
    uint u;

    c = ui->listWidget->count();
    d = 0;
    for(i = 0; i < c; i += 1) {
        item = ui->listWidget->item(i);
        if(item->checkState() == Qt::Checked)
            d += 1;
    }

    if(monDevs) {
        for(u = 0; u < nMonDevs; u += 1) monDevs[u].~ITHControl();
        free(monDevs);
    }
    monDevs = (ITHControl*)malloc(sizeof(*monDevs) * d);

    if(pkts) delete[] pkts;
    pkts = new IPPacketInput[d];

    j = 0;
    for(i = 0; i < c; i += 1) {
        item = ui->listWidget->item(i);
        if(item->checkState() == Qt::Checked) {
            new (monDevs + j) ITHControl(devs[i], pkts + j);
            monDevs[j].operate();
            j += 1;
        }
    }

    nMonDevs = d;
    if(_update) delete _update;
    _update = new UpdateControl(monDevs, nMonDevs);
    _update->operate();

    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
}

void MainWindow::UIClear() {
    ui->treeWidget_2->clear();
}

void MainWindow::UIAddTop(const char *text, QTreeWidgetItem **item) {
    QTreeWidgetItem *_item;
    _item = new QTreeWidgetItem(ui->treeWidget_2);
    _item->setText(0, tr(text));
    _item->setExpanded(true);
    *item = _item;
}

void MainWindow::UIAddSubItem(QTreeWidgetItem *parent, QTreeWidgetItem **item) {
    *item = new QTreeWidgetItem(parent);
}

void MainWindow::UISetText(QTreeWidgetItem* item, int col, const char *text) {
    if(item) item->setText(col, tr(text));
}
