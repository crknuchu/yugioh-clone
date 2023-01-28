/********************************************************************************
** Form generated from reading UI file 'DeckSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECKSETTINGS_H
#define UI_DECKSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_deckSettings {
public:
  void setupUi(QDialog* deckSettings) {
    if (deckSettings->objectName().isEmpty())
      deckSettings->setObjectName(QString::fromUtf8("deckSettings"));
    deckSettings->resize(400, 300);

    retranslateUi(deckSettings);

    QMetaObject::connectSlotsByName(deckSettings);
  } // setupUi

  void retranslateUi(QDialog* deckSettings) {
    deckSettings->setWindowTitle(QCoreApplication::translate("deckSettings", "Dialog", nullptr));
  } // retranslateUi
};

namespace Ui {
class deckSettings : public Ui_deckSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECKSETTINGS_H
