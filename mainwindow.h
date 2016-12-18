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

private:
    Ui::MainWindow *ui;

public slots:
    void UIClear();
    void UIAddTop(const char *text, QTreeWidgetItem **item);
    void UIAddSubItem(QTreeWidgetItem *parent, QTreeWidgetItem **item);
    void UISetText(QTreeWidgetItem* item, int col, const char *text);
};
#endif // MAINWINDOW_H
