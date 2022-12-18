/********************************************************************************
** Form generated from reading UI file 'GameSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESETTINGS_H
#define UI_GAMESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameSettings
{
public:
    QDialogButtonBox *Back;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *SetLifepoints;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QComboBox *SetTimePerMove;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QComboBox *SetInitialNumberOfCards;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton;

    void setupUi(QDialog *GameSettings)
    {
        if (GameSettings->objectName().isEmpty())
            GameSettings->setObjectName(QString::fromUtf8("GameSettings"));
        GameSettings->resize(524, 345);
        GameSettings->setStyleSheet(QString::fromUtf8(""));
        Back = new QDialogButtonBox(GameSettings);
        Back->setObjectName(QString::fromUtf8("Back"));
        Back->setGeometry(QRect(140, 290, 341, 32));
        Back->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));
        Back->setOrientation(Qt::Horizontal);
        Back->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(GameSettings);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 20, 211, 271));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 italic 11pt \"Ubuntu Mono\";"));

        verticalLayout->addWidget(label);

        SetLifepoints = new QComboBox(verticalLayoutWidget);
        SetLifepoints->setObjectName(QString::fromUtf8("SetLifepoints"));
        SetLifepoints->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        verticalLayout->addWidget(SetLifepoints);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 italic 11pt \"Ubuntu Mono\";"));

        verticalLayout->addWidget(label_2);

        SetTimePerMove = new QComboBox(verticalLayoutWidget);
        SetTimePerMove->setObjectName(QString::fromUtf8("SetTimePerMove"));
        SetTimePerMove->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        verticalLayout->addWidget(SetTimePerMove);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 italic 11pt \"Ubuntu Mono\";"));

        verticalLayout->addWidget(label_3);

        SetInitialNumberOfCards = new QComboBox(verticalLayoutWidget);
        SetInitialNumberOfCards->setObjectName(QString::fromUtf8("SetInitialNumberOfCards"));
        SetInitialNumberOfCards->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        verticalLayout->addWidget(SetInitialNumberOfCards);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(35, 40, 3, 255), stop:0.16 rgba(136, 106, 22, 255), stop:0.225 rgba(166, 140, 41, 255), stop:0.285 rgba(204, 181, 74, 255), stop:0.345 rgba(235, 219, 102, 255), stop:0.415 rgba(245, 236, 112, 255), stop:0.52 rgba(209, 190, 76, 255), stop:0.57 rgba(187, 156, 51, 255), stop:0.635 rgba(168, 142, 42, 255), stop:0.695 rgba(202, 174, 68, 255), stop:0.75 rgba(218, 202, 86, 255), stop:0.815 rgba(208, 187, 73, 255), stop:0.88 rgba(187, 156, 51, 255), stop:0.935 rgba(137, 108, 26, 255), stop:1 rgba(35, 40, 3, 255));"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(GameSettings);
        QObject::connect(Back, SIGNAL(accepted()), GameSettings, SLOT(accept()));
        QObject::connect(Back, SIGNAL(rejected()), GameSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(GameSettings);
    } // setupUi

    void retranslateUi(QDialog *GameSettings)
    {
        GameSettings->setWindowTitle(QCoreApplication::translate("GameSettings", "Game settings", nullptr));
        label->setText(QCoreApplication::translate("GameSettings", "Set life points", nullptr));
        label_2->setText(QCoreApplication::translate("GameSettings", "Set time per move", nullptr));
        label_3->setText(QCoreApplication::translate("GameSettings", "Set initial number of cards", nullptr));
        pushButton->setText(QCoreApplication::translate("GameSettings", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameSettings: public Ui_GameSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESETTINGS_H
