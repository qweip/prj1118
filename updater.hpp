#ifndef UPDATER_HPP
#define UPDATER_HPP

#include <QThread>
#include <QMutex>
#include <QTreeWidget>
#include "interface_thread.hpp"

class Updater : public QObject
{
    Q_OBJECT

    ITHControl *controls; //ref
    uint n;

public:
    void SetController(ITHControl *pkts);
    void SetN(uint _n);

public slots:
    void doWork();

signals:
    void resultReady(uint result);

signals:
    void UIClear();
    void UIAddTop(const char *text, QTreeWidgetItem **item);
    void UIAddSubItem(QTreeWidgetItem *parent, QTreeWidgetItem **item);
    void UISetText(QTreeWidgetItem* item, int col, const char *text);
};


class UpdateControl : public QObject
{
    Q_OBJECT

    QThread workerThread;
    ITHControl *controls; //set outside
    uint n;
    uint result;

public:
    UpdateControl(ITHControl *_controls, uint _n);

    ~UpdateControl();

    bool isRunnung() const;
    bool isFinished() const;
    uint GetResult() const;

public slots:
    void handleResults(uint _result);

signals:
    void operate();
};


#endif // UPDATER_HPP
