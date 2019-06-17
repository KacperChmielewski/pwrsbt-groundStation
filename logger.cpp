#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent) {

}

void Logger::setUI(QPlainTextEdit *txt, QPushButton *btn) {
    textEdit = txt;
    button = btn;

    textEdit->setReadOnly(true);

    connect(button, SIGNAL (released()), this, SLOT (cleanButtonClicked()));
}


void Logger::print(QString text){
    textEdit->insertPlainText(text + "\r\n");
}

void Logger::print(const char* text){
    print(QString(text));
}

void Logger::clean() {
    textEdit->clear();
}

void Logger::cleanButtonClicked() {
    clean();
}
