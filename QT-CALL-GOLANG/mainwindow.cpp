#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef Q_OS_MACOS
#include "libdemo.h" // 包含go的静态库头文件
#endif

#ifdef Q_OS_WINDOWS
#include "../build/windows/libdemo.h"
#endif

struct MyPoint{//类型和顺序必须和go中的MyPoint对应
    GoString Name;
    long long X;
    long long Y;
};

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
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        int arg1 = ui->lineEdit->text().toInt(nullptr,10);
        int arg2 = ui->lineEdit_2->text().toInt(nullptr,10);
        GoInt num = AddInt(arg1,arg2);
        ui->textEdit->insertPlainText(QString("%1\n").arg(num));
    });
    connect(ui->pushButton_call_hello,&QPushButton::clicked,this,[=](){
        GoString hello = Hello();
        std::string str = ToCString(hello);
        ui->textEdit->insertPlainText(QString("%1\n").arg(str.c_str()));
    });

    // 传入结构体
    connect(ui->pushButton_set_struct,&QPushButton::clicked,this,[=]{
        GoString hello = Hello();
        MyPoint mp{hello,0,0};
        SetMyPoint((GoUintptr)&mp);
//        ctx_info *info;
//        info = createCtx("测试","测试描述");
//        qDebug()<<info->name<<info->desc;
        ctx_info x = GetMyInfo("测试信息");
        qDebug()<<x.name<<x.desc;
        langs l = GetLangs();
        qDebug()<<l.name<<l.num;
        GoUint8 ok = '0';
        auto err = GetErr(ok);
        qDebug()<<ToCString(err);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

