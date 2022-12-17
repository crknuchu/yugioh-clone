#include "profilesettings.h"
#include "ui_profilesettings.h"
#include "QPixmap"
#include "QGraphicsPixmapItem"
#include "QGraphicsItem"
#include "QGraphicsView"
profileSettings::profileSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileSettings)
{
    ui->setupUi(this);
    ui->sleeveWindow->setBaseSize(400, 500);
//    ui->sleeveWindow->setMaximumSize(300, 400);
    ui->cancel->setMaximumSize(50, 100);
    ui->save->setMaximumSize(50, 100);
    QPixmap imageBackG(":/resources/avatars.jpg");
    imageBackG = imageBackG.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QBrush brush(imageBackG);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);

    QPalette textColor;
    textColor.setColor(QPalette::WindowText, Qt::white);
    textColor.setColor(QPalette::Window, Qt::gray);

    ui->lb1->setAutoFillBackground(true);
    ui->lb1->setPalette(textColor);

    ui->lb2->setAutoFillBackground(true);
    ui->lb2->setPalette(textColor);

    QFont font("Arial", 15, QFont::Bold);
    ui->lb1->setFont(font);
    ui->lb2->setFont(font);

    QImage card(":/resources/card_back.jpg");
    //bkgnd.devicePixelRatioFScale();
    card = card.scaled(ui->sleeveWindow->width(), ui->sleeveWindow->height());

    QBrush b(card);
    ui->sleeveWindow->setBackgroundBrush(b);
    ui->sleeveWindow->show();

    cardSleve = ui->sleeveWindow;
    cardSleve->setBackgroundBrush(b);

    scene = new QGraphicsScene(this);
    ui->sleeveWindow->setScene(scene);
    ui->sleeveWindow->setBackgroundBrush(b);
    ui->sleeveWindow->fitInView(ui->sleeveWindow->sceneRect(), Qt::IgnoreAspectRatio);

    QImage avatar(":/resources/yugi.png");
    card = card.scaled(ui->sleeveWindow->width(), ui->sleeveWindow->height());

    QBrush a(avatar);
    ui->avatarWindow->setBackgroundBrush(a);
    ui->avatarWindow->show();
    \
    ui->avatarWindow->setScene(scene);
    ui->avatarWindow->setBackgroundBrush(a);
    ui->avatarWindow->fitInView(ui->avatarWindow->sceneRect(), Qt::KeepAspectRatio);
}


profileSettings::~profileSettings()
{
    delete ui;
}
