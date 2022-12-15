#include "profilesettings.h"
#include "ui_profilesettings.h"

profileSettings::profileSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileSettings)
{
    ui->setupUi(this);
    ui->sleeveWindow->setBaseSize(300, 400);
    ui->sleeveWindow->setMaximumSize(300, 400);
    ui->cancel->setMaximumSize(50, 100);
    ui->save->setMaximumSize(50, 100);
}


profileSettings::~profileSettings()
{
    delete ui;
}
