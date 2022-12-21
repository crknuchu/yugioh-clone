#ifndef PROFILESETTINGS_H
#define PROFILESETTINGS_H

#include <QWidget>
#include <QGraphicsView>
namespace Ui {
class profileSettings;
}

enum class sleeves{
    BLACK,
    RED,
    WHITE,
    GREEN,
    BLUE
};


class profileSettings : public QWidget
{
    Q_OBJECT

public:
    explicit profileSettings(QWidget *parent = nullptr);
    ~profileSettings();

private:
    void setUpConnections();
    QGraphicsScene *scene;

    Ui::profileSettings *ui;
    QGraphicsView *cardSleve;

private slots:
    void changeAvatar();
    void changeSleeve();
    void undoChanges();
    void saveChanges();
};

#endif // PROFILESETTINGS_H
