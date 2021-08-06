#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget *parent = nullptr);
    ~DialogSettings();
signals:
    void onAcceptSignal(qint32 server);
private slots:
    void onAcceptSlot();

private:
    Ui::DialogSettings *ui;
};

#endif // DIALOGSETTINGS_H
