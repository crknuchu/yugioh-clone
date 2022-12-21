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

enum class avatars {
    YUGI,
    KAIBA
};

extern sleeves currentSleeve;
extern avatars currentAvatar;

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
    void changeSleeveNext();
    void changeSleevePrevious();
    void undoChanges();
    void saveChanges();
};

#endif // PROFILESETTINGS_H
