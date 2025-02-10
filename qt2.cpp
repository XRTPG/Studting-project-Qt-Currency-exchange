#include <QtWidgets/qwidget.h>
#include <windows.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qframe.h>
#include <QtWidgets/qlineedit.h>
#include <QtCore/qtextcodec.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qcombobox.h>
#include <QtGui/qfont.h>
#include <QtCore/qstringlist>
#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qicon.h>
#include <QtWidgets/qtextedit.h>
#include "QC.hpp"
#define Button QPushButton
#define Label QLabel
#define QHBox QHBoxLayout
#define QVBox QVBoxLayout
std::vector<const char*> vs = { "人民币/美元","日币/人民币","日币/美元","人民币/英镑","美元/英镑","日币/英镑","欧元/英镑","人民币/欧元","日币/欧元","美元/欧元","韩币/人民币","韩币/美元","韩币/日币","韩币/英镑","韩币/欧元","韩币/卢布","卢布/人民币","卢布/美元","卢布/英镑","卢布/欧元","卢布/日币","人民币/瑞士法郎","美元/瑞士法郎","日币/瑞士法郎","韩币/瑞士法郎","欧元/瑞士法郎","卢布/瑞士法郎","瑞士法郎/英镑" };
std::vector<double> vi = { 0.1369,0.04796,0.006573,0.11024,0.80557,0.00529,0.83216,0.13248,0.0063625,0.9678,0.005032,0.000684,0.10486,0.00055,0.000667,0.06652,0.07481,0.010259,0.00828,0.009929,0.6387,0.124,0.90988,0.00598,0.000622,0.9398,0.00933,0.8849 };



void convert(Label* label_one,Label* label_two,QTextEdit* te1,QTextEdit* te2) {
    QString content1 = label_one->text();
    QString content2 = label_two->text();
    QString character = QCT("/");
    QString tirecontent = content1 + character + content2;
    int index = 0;
    for (auto cbct : QCTLT(vs)) {
        if (tirecontent == cbct){
        QString number = te1->toPlainText();
        double onetext = number.toDouble();
        double res = vi[index] * onetext;
        te2->clear(); te2->setText(QString::number(res));
        }
        else if ((SingleQRB(tirecontent, '/')) == cbct) {
            QString number = te1->toPlainText();
            double onetext = number.toDouble();
            double res =  onetext/vi[index] ;
            te2->clear(); te2->setText(QString::number(res));
        }
        else { index++; }


    }
    
}
//交换
void text_switch(Label* label_one,Label* label_two) {
    QString content1 = label_one->text();
    QString content2 = label_two->text();
    label_one->setText(content2);
    label_two->setText(content1);
}
//获取内容
void change(Label* label_one, Label* label_two, QComboBox* combo) {
    bool sign = true;
    QString content = combo->currentText();
    QString content1 = QCT("");
    QString content2 = QCT("");
    for (auto ct : content) {
        if (ct != '/' && sign) {
            content1 += ct;
        }
        else if (!sign) { content2 += ct; }
        else { sign = false; }
    }
    label_one->setText(content1);
    label_two->setText(content2);
}

// WinMain 入口函数 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);//应用程序类
    QWidget mainwindow;  //主窗口类
    QC title({ "货币转换" });//titlecontent
    mainwindow.setWindowTitle(title.contents[0]);
    mainwindow.resize(400, 200);
    //组件
    QFont font("Afrail", 15);
    QFrame* frame = new QFrame(&mainwindow);
    Button* button = new Button(QCT("转    换"), &mainwindow);
    QComboBox* combo = new QComboBox(&mainwindow);
    combo->setFont(font);
    combo->addItems(QCTLT(vs));
    button->setFont(font);
    QFrame* frame1 = new QFrame(frame);
    QFrame* frame2 = new QFrame(frame);
    QFrame* frame3 = new QFrame(frame);
    QPixmap pic("pic.png");
    QIcon icon(pic);
    Label* label1 = new Label(QCT("人民币"), frame1);
    Label* label2 = new Label(QCT("美元"), frame3);
    Label* label3 = new Label(QCT(">>>>"), frame2);
    Button* button1 = new Button(frame2);
    button1->setIcon(icon);
    QTextEdit* text1 = new QTextEdit(frame1);
    QTextEdit* text2 = new QTextEdit(frame3);
    
    QVBox* Vbox = new QVBox(&mainwindow);
    QHBox* hbox = new QHBox(frame);
    QVBox* vbox1 = new QVBox(frame1);
    QVBox* vbox2 = new QVBox(frame2);
    QVBox* vbox3 = new QVBox(frame3);
    
    label1->setFont(font); label2->setFont(font); label3->setFont(font);
    vbox1->addWidget(label1);
    vbox1->addWidget(text1);
    vbox2->addWidget(label3);
    vbox2->addWidget(button1);
    vbox3->addWidget(label2);
    vbox3->addWidget(text2);
    hbox->addWidget(frame1);
    hbox->addWidget(frame2);
    hbox->addWidget(frame3);
    Vbox->addWidget(combo);
    Vbox->addWidget(frame);
    Vbox->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [=]() {convert(label1, label2,text1,text2); });
    QObject::connect(button1, &QPushButton::clicked, [=]() {text_switch(label1, label2); });
    QObject::connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {change(label1,label2,combo); });
    //显示窗口 
    mainwindow.show();
    return app.exec();
}