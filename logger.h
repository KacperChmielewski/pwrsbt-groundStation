#ifndef LOGGER_H
#define LOGGER_H

#include <QPlainTextEdit>
#include <QPushButton>
#include <QString>

class logger
{
private:
    QPlainTextEdit* textEdit;
    QPushButton* button;
public:
    logger(QPlainTextEdit* txt, QPushButton* btn);
    void print(QString text);
    void print(const char* text);
};

#endif // LOGGER_H
