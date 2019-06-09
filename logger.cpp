#include "logger.h"

logger::logger(QObject *parent) : QObject(parent) {

}

void logger::setLoggerUI(QPlainTextEdit *txt, QPushButton *btn) {
    this->textEdit = txt;
    this->button = btn;
    connect(this->button, SIGNAL (released()), this, SLOT (cleanButtonClicked()));
}


void logger::print(QString text){
    this->textEdit->insertPlainText(text + "\r\n");
}

void logger::print(const char* text){
    this->print(QString(text));
}

void logger::clean() {
    this->textEdit->clear();
}

void logger::cleanButtonClicked() {
    this->clean();
}
