/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
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
    QPushButton *btnBattlePhase;
    QPushButton *btnMainPhase2;
    QPushButton *btnEndPhase;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *avatarPlayer;
    QLineEdit *namePlayer;
    QProgressBar *progressBar;
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
        graphicsView->setGeometry(QRect(410, 0, 1201, 711));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 401, 777));
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

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(410, 0, 151, 131));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_6->addWidget(label);

        lineEdit_4 = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout_6->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        verticalLayout_6->addWidget(lineEdit_5);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(450, 590, 131, 151));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        avatarPlayer = new QLabel(verticalLayoutWidget);
        avatarPlayer->setObjectName(QString::fromUtf8("avatarPlayer"));

        verticalLayout_3->addWidget(avatarPlayer);

        namePlayer = new QLineEdit(verticalLayoutWidget);
        namePlayer->setObjectName(QString::fromUtf8("namePlayer"));

        verticalLayout_3->addWidget(namePlayer);

        progressBar = new QProgressBar(verticalLayoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(8000);
        progressBar->setValue(8000);

        verticalLayout_3->addWidget(progressBar);

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
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt;\">Monster effect</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p></body></html>", nullptr));
        labelGamePhase->setText(QString());
        btnBattlePhase->setText(QCoreApplication::translate("MainWindow", "Battle Phase", nullptr));
        btnMainPhase2->setText(QCoreApplication::translate("MainWindow", "Main Phase 2", nullptr));
        btnEndPhase->setText(QCoreApplication::translate("MainWindow", "End Phase", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        avatarPlayer->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        progressBar->setFormat(QCoreApplication::translate("MainWindow", "%p%", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
