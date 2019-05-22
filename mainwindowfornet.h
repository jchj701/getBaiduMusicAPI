#ifndef MAINWINDOWFORNET_H
#define MAINWINDOWFORNET_H

#include <QMainWindow>

namespace Ui {
    class MainWindowForNet;
    }

class MainWindowForNet : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForNet(QWidget *parent = nullptr);
    ~MainWindowForNet();

private:
    Ui::MainWindowForNet *ui;
};

#endif // MAINWINDOWFORNET_H
