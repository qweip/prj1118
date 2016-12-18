#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConnA.hpp"

char pcapErrBuf[PCAP_ERRBUF_SIZE];

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

void MainWindow::on_pushButton_clicked()
{
    MessageBoxA(0, "Button Clicked", "Info", MB_OK);
}

void MainWindow::on_pushButton_4_clicked()
{
    char addrStr[64], netmaskStr[64], buf[32], *_addr, *interfaceInfo;
    sockaddr_in addrIn;
    QString *qs;
    QListWidgetItem *litem;
    size_t totalStrLen;
    pcap_if_t *head, *cur;
    uint count = 0;

    if(pcap_findalldevs(&head, pcapErrBuf) != 0) {
        MessageBoxA(0, pcapErrBuf, "Error", MB_OK);
        return;
    }

    ui->listWidget->clear();
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

        ui->listWidget->addItem(*qs);
        delete[] interfaceInfo;
        delete qs;

        litem = ui->listWidget->item(count);
        litem->setFlags(litem->flags() | Qt::ItemIsUserCheckable);
        litem->setCheckState(Qt::Unchecked);

        count += 1;
        cur = cur->next;
    }

    sprintf(buf, "%u interfaces found.", count);
    MessageBoxA(0, buf, "Info", MB_OK);

    pcap_freealldevs(head);
}
