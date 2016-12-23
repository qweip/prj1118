#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;

public slots:
    void UIClear();
    void UIAddTop(const char *text, QTreeWidgetItem **item);
    void UIAddIP(const char *text, QTreeWidgetItem **item);
    void UIAddSubItem(QTreeWidgetItem *parent, QTreeWidgetItem **item, bool expend);
    void UISetBG(QTreeWidgetItem *item, int nCols, const QBrush &background);
    void UISetTextColor(QTreeWidgetItem *item, int nCols, const QColor &text);
    void UISetText(QTreeWidgetItem* item, int col, const char *text);
};
#endif // MAINWINDOW_H
