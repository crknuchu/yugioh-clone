/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QWidget *layoutWidget;
    QVBoxLayout *leftVerticalLayout;
    QLabel *labelImage;
    QTextBrowser *textBrowserEffect;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelGamePhase;
    QSpacerItem *verticalSpacer;
    QPushButton *btnBattlePhase;
    QPushButton *btnMainPhase2;
    QPushButton *btnEndPhase;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelCurrentPlayerNameConst;
    QLabel *labelCurrentPlayerNameDynamic;
    QLabel *labelOtherPlayerNameConst;
    QLabel *labelOtherPlayerNameDynamic;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelCurrentPlayerLpConst;
    QLabel *labelCurrentPlayerLpDynamic;
    QLabel *labelOtherPlayerLpConst;
    QLabel *labelOtherPlayerLpDynamic;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelServerAddress;
    QLabel *labelServerPort;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *textEditAddress;
    QTextEdit *textEditPort;
    QPushButton *btnTestNetwork;
    QPushButton *btnWriteData;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1629, 861);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(423, 9, 1191, 761));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 401, 761));
        leftVerticalLayout = new QVBoxLayout(layoutWidget);
        leftVerticalLayout->setObjectName(QString::fromUtf8("leftVerticalLayout"));
        leftVerticalLayout->setContentsMargins(0, 0, 0, 0);
        labelImage = new QLabel(layoutWidget);
        labelImage->setObjectName(QString::fromUtf8("labelImage"));
        labelImage->setEnabled(true);
        labelImage->setMinimumSize(QSize(399, 300));

        leftVerticalLayout->addWidget(labelImage);

        textBrowserEffect = new QTextBrowser(layoutWidget);
        textBrowserEffect->setObjectName(QString::fromUtf8("textBrowserEffect"));

        leftVerticalLayout->addWidget(textBrowserEffect);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        leftVerticalLayout->addItem(verticalSpacer_2);

        labelGamePhase = new QLabel(layoutWidget);
        labelGamePhase->setObjectName(QString::fromUtf8("labelGamePhase"));

        leftVerticalLayout->addWidget(labelGamePhase);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        leftVerticalLayout->addItem(verticalSpacer);

        btnBattlePhase = new QPushButton(layoutWidget);
        btnBattlePhase->setObjectName(QString::fromUtf8("btnBattlePhase"));

        leftVerticalLayout->addWidget(btnBattlePhase);

        btnMainPhase2 = new QPushButton(layoutWidget);
        btnMainPhase2->setObjectName(QString::fromUtf8("btnMainPhase2"));
        btnMainPhase2->setEnabled(false);

        leftVerticalLayout->addWidget(btnMainPhase2);

        btnEndPhase = new QPushButton(layoutWidget);
        btnEndPhase->setObjectName(QString::fromUtf8("btnEndPhase"));

        leftVerticalLayout->addWidget(btnEndPhase);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelCurrentPlayerNameConst = new QLabel(layoutWidget);
        labelCurrentPlayerNameConst->setObjectName(QString::fromUtf8("labelCurrentPlayerNameConst"));

        horizontalLayout->addWidget(labelCurrentPlayerNameConst);

        labelCurrentPlayerNameDynamic = new QLabel(layoutWidget);
        labelCurrentPlayerNameDynamic->setObjectName(QString::fromUtf8("labelCurrentPlayerNameDynamic"));

        horizontalLayout->addWidget(labelCurrentPlayerNameDynamic);

        labelOtherPlayerNameConst = new QLabel(layoutWidget);
        labelOtherPlayerNameConst->setObjectName(QString::fromUtf8("labelOtherPlayerNameConst"));

        horizontalLayout->addWidget(labelOtherPlayerNameConst);

        labelOtherPlayerNameDynamic = new QLabel(layoutWidget);
        labelOtherPlayerNameDynamic->setObjectName(QString::fromUtf8("labelOtherPlayerNameDynamic"));

        horizontalLayout->addWidget(labelOtherPlayerNameDynamic);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelCurrentPlayerLpConst = new QLabel(layoutWidget);
        labelCurrentPlayerLpConst->setObjectName(QString::fromUtf8("labelCurrentPlayerLpConst"));

        horizontalLayout_2->addWidget(labelCurrentPlayerLpConst);

        labelCurrentPlayerLpDynamic = new QLabel(layoutWidget);
        labelCurrentPlayerLpDynamic->setObjectName(QString::fromUtf8("labelCurrentPlayerLpDynamic"));

        horizontalLayout_2->addWidget(labelCurrentPlayerLpDynamic);

        labelOtherPlayerLpConst = new QLabel(layoutWidget);
        labelOtherPlayerLpConst->setObjectName(QString::fromUtf8("labelOtherPlayerLpConst"));

        horizontalLayout_2->addWidget(labelOtherPlayerLpConst);

        labelOtherPlayerLpDynamic = new QLabel(layoutWidget);
        labelOtherPlayerLpDynamic->setObjectName(QString::fromUtf8("labelOtherPlayerLpDynamic"));

        horizontalLayout_2->addWidget(labelOtherPlayerLpDynamic);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelServerAddress = new QLabel(layoutWidget);
        labelServerAddress->setObjectName(QString::fromUtf8("labelServerAddress"));

        horizontalLayout_4->addWidget(labelServerAddress);

        labelServerPort = new QLabel(layoutWidget);
        labelServerPort->setObjectName(QString::fromUtf8("labelServerPort"));

        horizontalLayout_4->addWidget(labelServerPort);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        textEditAddress = new QTextEdit(layoutWidget);
        textEditAddress->setObjectName(QString::fromUtf8("textEditAddress"));

        horizontalLayout_3->addWidget(textEditAddress);

        textEditPort = new QTextEdit(layoutWidget);
        textEditPort->setObjectName(QString::fromUtf8("textEditPort"));

        horizontalLayout_3->addWidget(textEditPort);


        verticalLayout->addLayout(horizontalLayout_3);

        btnTestNetwork = new QPushButton(layoutWidget);
        btnTestNetwork->setObjectName(QString::fromUtf8("btnTestNetwork"));

        verticalLayout->addWidget(btnTestNetwork);

        btnWriteData = new QPushButton(layoutWidget);
        btnWriteData->setObjectName(QString::fromUtf8("btnWriteData"));

        verticalLayout->addWidget(btnWriteData);


        leftVerticalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1629, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelImage->setText(QString());
        textBrowserEffect->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Card effect</p></body></html>", nullptr));
        labelGamePhase->setText(QString());
        btnBattlePhase->setText(QCoreApplication::translate("MainWindow", "Battle Phase", nullptr));
        btnMainPhase2->setText(QCoreApplication::translate("MainWindow", "Main Phase 2", nullptr));
        btnEndPhase->setText(QCoreApplication::translate("MainWindow", "End Phase", nullptr));
        labelCurrentPlayerNameConst->setText(QCoreApplication::translate("MainWindow", "Current Player:", nullptr));
        labelCurrentPlayerNameDynamic->setText(QString());
        labelOtherPlayerNameConst->setText(QCoreApplication::translate("MainWindow", "Other Player:", nullptr));
        labelOtherPlayerNameDynamic->setText(QString());
        labelCurrentPlayerLpConst->setText(QCoreApplication::translate("MainWindow", "Life Points:", nullptr));
        labelCurrentPlayerLpDynamic->setText(QString());
        labelOtherPlayerLpConst->setText(QCoreApplication::translate("MainWindow", "Life Points:", nullptr));
        labelOtherPlayerLpDynamic->setText(QString());
        labelServerAddress->setText(QCoreApplication::translate("MainWindow", "Server address", nullptr));
        labelServerPort->setText(QCoreApplication::translate("MainWindow", "Server port", nullptr));
        btnTestNetwork->setText(QCoreApplication::translate("MainWindow", "Connect to the server", nullptr));
        btnWriteData->setText(QCoreApplication::translate("MainWindow", "Test write data to server", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
