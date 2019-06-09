#include "logger.h"

#include <iostream>

logger::logger(QPlainTextEdit* txt, QPushButton* btn) : textEdit(txt), button(btn)
{
    std::cout << "test" << std::endl;
}

void logger::print(QString text) {
    this->textEdit->insertPlainText(text + "\r\n");
}

void logger::print(const char* text) {
    this->print(QString(text));
}
