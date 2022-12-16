#ifndef PROFILESETTINGS_H
#define PROFILESETTINGS_H

#include <QWidget>
#include "headers/Game.h"
#include <QGraphicsView>
namespace Ui {
class profileSettings;
}

class profileSettings : public QWidget
{
    Q_OBJECT

public:
    explicit profileSettings(QWidget *parent = nullptr);
    ~profileSettings();

private:
    Ui::profileSettings *ui;
    profileSettings *p;
};

#endif // PROFILESETTINGS_H
