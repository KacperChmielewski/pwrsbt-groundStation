#ifndef SUPERLOGGER_H
#define SUPERLOGGER_H

#include <QObject>

#include <QPlainTextEdit>
#include <QPushButton>

class superLogger : public QObject
{
    Q_OBJECT
private:
    QPlainTextEdit* textEdit;
    QPushButton* button;
public:
    explicit superLogger(QObject *parent = nullptr);
    void setLoggerUI(QPlainTextEdit *txt, QPushButton *btn);
    void print(QString text);
    void print(const char* text);
    void clean();
signals:

public slots:
};

#endif // SUPERLOGGER_H
