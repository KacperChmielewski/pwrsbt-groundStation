#include "superlogger.h"

superLogger::superLogger(QObject *parent) : QObject(parent)
{

}

void superLogger::setLoggerUI(QPlainTextEdit *txt, QPushButton *btn) {
    this->textEdit = txt;
    this->button = btn;
}


void superLogger::print(QString text){
    this->textEdit->insertPlainText(text + "\r\n");
}

void superLogger::print(const char* text){
    this->print(QString(text));
}

void superLogger::clean(){
    this->textEdit->clear();
}
