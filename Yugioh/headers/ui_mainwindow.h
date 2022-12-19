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
    QLabel *labelCurrentPlayerConst;
    QLabel *labelCurrentPlayerDynamic;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelHealthPointsConst;
    QLabel *labelHealthPointsDynamic;
    QPushButton *btnTestNetwork;
    QLabel *labelMessageFromServer;
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
        layoutWidget->setGeometry(QRect(9, 9, 401, 760));
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
        labelCurrentPlayerConst = new QLabel(layoutWidget);
        labelCurrentPlayerConst->setObjectName(QString::fromUtf8("labelCurrentPlayerConst"));

        horizontalLayout->addWidget(labelCurrentPlayerConst);

        labelCurrentPlayerDynamic = new QLabel(layoutWidget);
        labelCurrentPlayerDynamic->setObjectName(QString::fromUtf8("labelCurrentPlayerDynamic"));

        horizontalLayout->addWidget(labelCurrentPlayerDynamic);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelHealthPointsConst = new QLabel(layoutWidget);
        labelHealthPointsConst->setObjectName(QString::fromUtf8("labelHealthPointsConst"));

        horizontalLayout_2->addWidget(labelHealthPointsConst);

        labelHealthPointsDynamic = new QLabel(layoutWidget);
        labelHealthPointsDynamic->setObjectName(QString::fromUtf8("labelHealthPointsDynamic"));

        horizontalLayout_2->addWidget(labelHealthPointsDynamic);


        verticalLayout->addLayout(horizontalLayout_2);

        btnTestNetwork = new QPushButton(layoutWidget);
        btnTestNetwork->setObjectName(QString::fromUtf8("btnTestNetwork"));

        verticalLayout->addWidget(btnTestNetwork);

        labelMessageFromServer = new QLabel(layoutWidget);
        labelMessageFromServer->setObjectName(QString::fromUtf8("labelMessageFromServer"));

        verticalLayout->addWidget(labelMessageFromServer);

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
        labelImage->setText(QCoreApplication::translate("MainWindow", "ImageLabel", nullptr));
        textBrowserEffect->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Monster effect</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        labelGamePhase->setText(QString());
        btnBattlePhase->setText(QCoreApplication::translate("MainWindow", "Battle Phase", nullptr));
        btnMainPhase2->setText(QCoreApplication::translate("MainWindow", "Main Phase 2", nullptr));
        btnEndPhase->setText(QCoreApplication::translate("MainWindow", "End Phase", nullptr));
        labelCurrentPlayerConst->setText(QCoreApplication::translate("MainWindow", "Current Player:", nullptr));
        labelCurrentPlayerDynamic->setText(QString());
        labelHealthPointsConst->setText(QCoreApplication::translate("MainWindow", "Health Points: ", nullptr));
        labelHealthPointsDynamic->setText(QString());
        btnTestNetwork->setText(QCoreApplication::translate("MainWindow", "Test Network Connectivity", nullptr));
        labelMessageFromServer->setText(QCoreApplication::translate("MainWindow", "Message from server", nullptr));
        btnWriteData->setText(QCoreApplication::translate("MainWindow", "Write data to server", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
