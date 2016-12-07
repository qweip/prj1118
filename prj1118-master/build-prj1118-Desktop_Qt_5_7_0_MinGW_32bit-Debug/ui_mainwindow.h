/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action01;
    QAction *action;
    QAction *action12313;
    QAction *actionQwdq;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QPushButton *pushButton_2;
    QTextEdit *textEdit_3;
    QRadioButton *radioButton;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QLabel *label;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QTreeWidget *treeWidget_2;
    QTreeWidget *treeWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu02;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(692, 423);
        action01 = new QAction(MainWindow);
        action01->setObjectName(QStringLiteral("action01"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action12313 = new QAction(MainWindow);
        action12313->setObjectName(QStringLiteral("action12313"));
        actionQwdq = new QAction(MainWindow);
        actionQwdq->setObjectName(QStringLiteral("actionQwdq"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tabWidget->setContextMenuPolicy(Qt::NoContextMenu);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 1, 0, 1, 1);

        textEdit_2 = new QTextEdit(tab);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        gridLayout->addWidget(textEdit_2, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 3, 1, 1, 1);

        textEdit_3 = new QTextEdit(tab);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));

        gridLayout->addWidget(textEdit_3, 1, 1, 1, 1);

        radioButton = new QRadioButton(tab);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout->addWidget(radioButton, 3, 0, 1, 1);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 1, 1, 1);

        textBrowser = new QTextBrowser(tab);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 1, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        treeWidget_2 = new QTreeWidget(tab_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget_2);
        __qtreewidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem3->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(treeWidget_2);
        new QTreeWidgetItem(__qtreewidgetitem5);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));

        gridLayout_4->addWidget(treeWidget_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_3->addWidget(tabWidget, 1, 0, 2, 1);

        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem6->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem9);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout_3->addWidget(treeWidget, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 692, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu->setTearOffEnabled(false);
        menu02 = new QMenu(menuBar);
        menu02->setObjectName(QStringLiteral("menu02"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu02->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action);
        menu->addAction(actionQwdq);
        mainToolBar->addAction(action01);
        mainToolBar->addAction(action12313);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action01->setText(QApplication::translate("MainWindow", "01", 0));
        action->setText(QApplication::translate("MainWindow", "01", 0));
        action12313->setText(QApplication::translate("MainWindow", "12313", 0));
        actionQwdq->setText(QApplication::translate("MainWindow", "qwdq", 0));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'PMingLiU'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">e wfewfwefwefwefwefefeeeweww</p></body></html>", 0));
        textEdit_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'PMingLiU'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1234568798</p></body></html>", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", 0));
        textEdit_3->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'PMingLiU'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1234568798</p></body></html>", 0));
        radioButton->setText(QApplication::translate("MainWindow", "RadioButton", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'PMingLiU'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">123456789</p></body></html>", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_2->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "123", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "123", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "\346\226\260\345\242\236\346\254\204\344\275\215", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "133333", 0));

        const bool __sortingEnabled = treeWidget_2->isSortingEnabled();
        treeWidget_2->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_2->topLevelItem(0);
        ___qtreewidgetitem1->setText(3, QApplication::translate("MainWindow", "12312", 0));
        ___qtreewidgetitem1->setText(2, QApplication::translate("MainWindow", "123123", 0));
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "12321", 0));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "\346\226\260\345\242\236\351\240\205\347\233\256", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(3, QApplication::translate("MainWindow", "2132", 0));
        ___qtreewidgetitem2->setText(2, QApplication::translate("MainWindow", "213213", 0));
        ___qtreewidgetitem2->setText(1, QApplication::translate("MainWindow", "2133", 0));
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "12321", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(3, QApplication::translate("MainWindow", "213123", 0));
        ___qtreewidgetitem3->setText(2, QApplication::translate("MainWindow", "213", 0));
        ___qtreewidgetitem3->setText(1, QApplication::translate("MainWindow", "21332", 0));
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "123122222", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(3, QApplication::translate("MainWindow", "2132", 0));
        ___qtreewidgetitem4->setText(2, QApplication::translate("MainWindow", "21321", 0));
        ___qtreewidgetitem4->setText(1, QApplication::translate("MainWindow", "21323", 0));
        ___qtreewidgetitem4->setText(0, QApplication::translate("MainWindow", "1232121321", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem5->setText(3, QApplication::translate("MainWindow", "213", 0));
        ___qtreewidgetitem5->setText(2, QApplication::translate("MainWindow", "213213", 0));
        ___qtreewidgetitem5->setText(1, QApplication::translate("MainWindow", "12312", 0));
        ___qtreewidgetitem5->setText(0, QApplication::translate("MainWindow", "123", 0));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(3, QApplication::translate("MainWindow", "123123", 0));
        ___qtreewidgetitem6->setText(2, QApplication::translate("MainWindow", "2132", 0));
        ___qtreewidgetitem6->setText(1, QApplication::translate("MainWindow", "1231231", 0));
        ___qtreewidgetitem6->setText(0, QApplication::translate("MainWindow", "2131232321", 0));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem5->child(1);
        ___qtreewidgetitem7->setText(3, QApplication::translate("MainWindow", "21323", 0));
        ___qtreewidgetitem7->setText(2, QApplication::translate("MainWindow", "213", 0));
        ___qtreewidgetitem7->setText(1, QApplication::translate("MainWindow", "213213", 0));
        ___qtreewidgetitem7->setText(0, QApplication::translate("MainWindow", "12321321", 0));
        QTreeWidgetItem *___qtreewidgetitem8 = treeWidget_2->topLevelItem(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("MainWindow", "21321231231", 0));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(0, QApplication::translate("MainWindow", "\346\226\260\345\242\236\345\255\220\351\240\205\347\233\256", 0));
        treeWidget_2->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
        QTreeWidgetItem *___qtreewidgetitem10 = treeWidget->headerItem();
        ___qtreewidgetitem10->setText(3, QApplication::translate("MainWindow", "123", 0));
        ___qtreewidgetitem10->setText(2, QApplication::translate("MainWindow", "123", 0));
        ___qtreewidgetitem10->setText(1, QApplication::translate("MainWindow", "\346\226\260\345\242\236\346\254\204\344\275\215", 0));
        ___qtreewidgetitem10->setText(0, QApplication::translate("MainWindow", "133333", 0));

        const bool __sortingEnabled1 = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem11 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem11->setText(3, QApplication::translate("MainWindow", "12312", 0));
        ___qtreewidgetitem11->setText(2, QApplication::translate("MainWindow", "123123", 0));
        ___qtreewidgetitem11->setText(1, QApplication::translate("MainWindow", "12321", 0));
        ___qtreewidgetitem11->setText(0, QApplication::translate("MainWindow", "\346\226\260\345\242\236\351\240\205\347\233\256", 0));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem11->child(0);
        ___qtreewidgetitem12->setText(3, QApplication::translate("MainWindow", "2132", 0));
        ___qtreewidgetitem12->setText(2, QApplication::translate("MainWindow", "213213", 0));
        ___qtreewidgetitem12->setText(1, QApplication::translate("MainWindow", "2133", 0));
        ___qtreewidgetitem12->setText(0, QApplication::translate("MainWindow", "12321", 0));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem12->child(0);
        ___qtreewidgetitem13->setText(3, QApplication::translate("MainWindow", "213123", 0));
        ___qtreewidgetitem13->setText(2, QApplication::translate("MainWindow", "213", 0));
        ___qtreewidgetitem13->setText(1, QApplication::translate("MainWindow", "21332", 0));
        ___qtreewidgetitem13->setText(0, QApplication::translate("MainWindow", "123122222", 0));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem12->child(1);
        ___qtreewidgetitem14->setText(3, QApplication::translate("MainWindow", "2132", 0));
        ___qtreewidgetitem14->setText(2, QApplication::translate("MainWindow", "21321", 0));
        ___qtreewidgetitem14->setText(1, QApplication::translate("MainWindow", "21323", 0));
        ___qtreewidgetitem14->setText(0, QApplication::translate("MainWindow", "1232121321", 0));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem11->child(1);
        ___qtreewidgetitem15->setText(3, QApplication::translate("MainWindow", "213", 0));
        ___qtreewidgetitem15->setText(2, QApplication::translate("MainWindow", "213213", 0));
        ___qtreewidgetitem15->setText(1, QApplication::translate("MainWindow", "12312", 0));
        ___qtreewidgetitem15->setText(0, QApplication::translate("MainWindow", "123", 0));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem15->child(0);
        ___qtreewidgetitem16->setText(3, QApplication::translate("MainWindow", "123123", 0));
        ___qtreewidgetitem16->setText(2, QApplication::translate("MainWindow", "2132", 0));
        ___qtreewidgetitem16->setText(1, QApplication::translate("MainWindow", "1231231", 0));
        ___qtreewidgetitem16->setText(0, QApplication::translate("MainWindow", "2131232321", 0));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem15->child(1);
        ___qtreewidgetitem17->setText(3, QApplication::translate("MainWindow", "21323", 0));
        ___qtreewidgetitem17->setText(2, QApplication::translate("MainWindow", "213", 0));
        ___qtreewidgetitem17->setText(1, QApplication::translate("MainWindow", "213213", 0));
        ___qtreewidgetitem17->setText(0, QApplication::translate("MainWindow", "12321321", 0));
        QTreeWidgetItem *___qtreewidgetitem18 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem18->setText(0, QApplication::translate("MainWindow", "21321231231", 0));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem18->child(0);
        ___qtreewidgetitem19->setText(0, QApplication::translate("MainWindow", "\346\226\260\345\242\236\345\255\220\351\240\205\347\233\256", 0));
        treeWidget->setSortingEnabled(__sortingEnabled1);

        menu->setTitle(QApplication::translate("MainWindow", "\346\252\224\346\241\210", 0));
        menu02->setTitle(QApplication::translate("MainWindow", "02", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\351\227\234\346\226\274", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
