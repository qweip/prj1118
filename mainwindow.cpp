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

static void addr2Str(struct sockaddr *addr, char *buf, size_t maxLength) {
    char *tmp;

    switch(addr->sa_family) {
    case AF_INET:
        sockaddr_in v4addr;
        memcpy(&v4addr, addr, sizeof(v4addr));
        tmp = inet_ntoa(v4addr.sin_addr);
        strncpy(buf, tmp, maxLength);
        break;
    case AF_INET6:
        sockaddr_in6 v6addr;
        memcpy(&v6addr, addr, sizeof(v6addr));
        inet6_ntoa(v6addr.sin6_addr, buf, maxLength);
        break;
    default:
        buf[0] = '\0';
        break;
    }
}

static void FindAllInterfaces(QListWidget *qlw, bool ipv6Address, bool ignoreNull) {
    char devName[MAX_DEV_NAME], addrStr[64], netmaskStr[64], buf[32], *interfaceInfo;
    QString *qs;
    const char *desc;
    QListWidgetItem *litem;
    size_t totalStrLen, descLen, addrLen, netmastLen;
    pcap_if_t *cur;
    pcap_addr *pcur;
    uint count, i;
    sa_family_t targetFamilay = AF_INET;

    bool skipInterface;

    if(head) pcap_freealldevs(head);
    if(pcap_findalldevs(&head, pcapErrBuf) != 0) {
        ShowNormalMsgBox(pcapErrBuf);
        return;
    }

    if(ipv6Address) targetFamilay = AF_INET6;

    qlw->clear();
    cur = head;
    count = 0;
    while(cur) {
        sprintf(addrStr, "NULL");
        addrLen = 4;
        sprintf(netmaskStr, "NULL");
        netmastLen = 4;

        skipInterface = true;

        if(cur->addresses) {
            pcur = cur->addresses;
            while(pcur) {

                if(pcur->addr) {
                    if(pcur->addr->sa_family != targetFamilay) {
                        pcur = pcur->next;
                        continue;
                    }

                    addr2Str(pcur->addr, addrStr, sizeof(addrStr) - 1);
                    addrLen = strlen(addrStr);
                    skipInterface = false;
                }

                if(pcur->netmask) {
                    addr2Str(pcur->netmask, netmaskStr, sizeof(netmaskStr) - 1);
                    netmastLen = strlen(netmaskStr);
                    netmastLen = strlen(netmaskStr);
                }

                pcur = pcur->next;
            }
        }
        else { }

        if(skipInterface && ignoreNull) {
            cur = cur->next;
            continue;
        }

#ifdef __linux__
        if(cur->name) {
            desc = cur->name;
            descLen = strlen(cur->name);
        }
#else
        if(cur->description) {
            desc = cur->description;
            descLen = strlen(cur->description);
        }
#endif //ifdef __linux__
        else {
            desc = "NULL";
            descLen = 4;
        }


        totalStrLen = descLen + addrLen + netmastLen;
        interfaceInfo = new char[totalStrLen + 1 + 4];
        sprintf(interfaceInfo, "%s (%s/%s)", desc, addrStr, netmaskStr);
        qs = new QString(interfaceInfo);

        qlw->addItem(*qs);
        delete[] interfaceInfo;
        delete qs;

        litem = qlw->item(count);
        litem->setFlags(litem->flags() | Qt::ItemIsUserCheckable);
        litem->setCheckState(Qt::Unchecked);
        if(cur->description) litem->setToolTip(cur->description);

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
    FindAllInterfaces(ui->listWidget, ui->radioButton_3->isChecked(), ui->checkBox->isChecked());
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

void MainWindow::on_action_triggered()
{
    QMessageBox msg;
    msg.setText(
        "國立金門大學 105學年上學期\n"
        "資工系專題第3組 網路流量分析研究\n"
        "即時分析DEMO程式\n"
        );
    msg.exec();
}
