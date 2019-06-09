#include "logger.h"

logger::logger(QObject *parent) : QObject(parent) {

}

void logger::setUI(QPlainTextEdit *txt, QPushButton *btn) {
    textEdit = txt;
    button = btn;

    textEdit->setReadOnly(true);

    connect(button, SIGNAL (released()), this, SLOT (cleanButtonClicked()));
}


void logger::print(QString text){
    textEdit->insertPlainText(text + "\r\n");
}

void logger::print(const char* text){
    print(QString(text));
}

void logger::clean() {
    textEdit->clear();
}

void logger::cleanButtonClicked() {
    clean();
}
