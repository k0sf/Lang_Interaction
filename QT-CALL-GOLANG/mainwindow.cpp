#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef Q_OS_MACOS
#include "libdemo.h" // 包含go的静态库头文件
#endif

#ifdef Q_OS_WINDOWS
#include "../build/windows/libdemo.h"
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QT-CALL-GOLANG (qt调用go库)");
    ui->lineEdit->setPlaceholderText("参数1");
    ui->lineEdit_2->setPlaceholderText("参数2");
//    ui->textEdit->setDisabled(true);
    ui->textEdit->setReadOnly(true); // 只读模式
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        int arg1 = ui->lineEdit->text().toInt(nullptr,10);
        int arg2 = ui->lineEdit_2->text().toInt(nullptr,10);
        GoInt num = AddInt(arg1,arg2);
        ui->textEdit->insertPlainText(QString("%1\n").arg(num));
    });
    connect(ui->pushButton_call_hello,&QPushButton::clicked,[=](){
        GoString hello = Hello();
        std::string str = ToCString(hello);
        ui->textEdit->insertPlainText(QString("%1\n").arg(str.c_str()));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

