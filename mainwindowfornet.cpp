#include "mainwindowfornet.h"
#include "ui_mainwindowfornet.h"

MainWindowForNet::MainWindowForNet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowForNet)
{
    ui->setupUi(this);
}

MainWindowForNet::~MainWindowForNet()
{
    delete ui;
}
