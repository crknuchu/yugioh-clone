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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GameSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_4;
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
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *leaveButton;
    QPushButton *okButton;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *GameSettings)
    {
        if (GameSettings->objectName().isEmpty())
            GameSettings->setObjectName(QString::fromUtf8("GameSettings"));
        GameSettings->resize(524, 345);
        GameSettings->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(GameSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(100, -1, 100, -1);
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        label = new QLabel(GameSettings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 italic 11pt \"Ubuntu Mono\";"));

        verticalLayout->addWidget(label);

        SetLifepoints = new QComboBox(GameSettings);
        SetLifepoints->setObjectName(QString::fromUtf8("SetLifepoints"));
        SetLifepoints->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        verticalLayout->addWidget(SetLifepoints);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(GameSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 italic 11pt \"Ubuntu Mono\";"));

        verticalLayout->addWidget(label_2);

        SetTimePerMove = new QComboBox(GameSettings);
        SetTimePerMove->setObjectName(QString::fromUtf8("SetTimePerMove"));
        SetTimePerMove->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        verticalLayout->addWidget(SetTimePerMove);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(GameSettings);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 italic 11pt \"Ubuntu Mono\";"));

        verticalLayout->addWidget(label_3);

        SetInitialNumberOfCards = new QComboBox(GameSettings);
        SetInitialNumberOfCards->setObjectName(QString::fromUtf8("SetInitialNumberOfCards"));
        SetInitialNumberOfCards->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        verticalLayout->addWidget(SetInitialNumberOfCards);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButton = new QPushButton(GameSettings);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        verticalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leaveButton = new QPushButton(GameSettings);
        leaveButton->setObjectName(QString::fromUtf8("leaveButton"));
        leaveButton->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        horizontalLayout->addWidget(leaveButton);

        okButton = new QPushButton(GameSettings);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 211, 45);"));

        horizontalLayout->addWidget(okButton);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);


        retranslateUi(GameSettings);

        QMetaObject::connectSlotsByName(GameSettings);
    } // setupUi

    void retranslateUi(QDialog *GameSettings)
    {
        GameSettings->setWindowTitle(QCoreApplication::translate("GameSettings", "Game settings", nullptr));
        label->setText(QCoreApplication::translate("GameSettings", "Set life points", nullptr));
        label_2->setText(QCoreApplication::translate("GameSettings", "Set time per move", nullptr));
        label_3->setText(QCoreApplication::translate("GameSettings", "Set initial number of cards", nullptr));
        pushButton->setText(QCoreApplication::translate("GameSettings", "Help", nullptr));
        leaveButton->setText(QCoreApplication::translate("GameSettings", "Leave", nullptr));
        okButton->setText(QCoreApplication::translate("GameSettings", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameSettings: public Ui_GameSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESETTINGS_H
