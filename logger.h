#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

#include <QPlainTextEdit>
#include <QPushButton>

class logger : public QObject
{
    Q_OBJECT
private:
    QPlainTextEdit* textEdit;
    QPushButton* button;
public:
    explicit logger(QObject *parent = nullptr);
    void setUI(QPlainTextEdit *txt, QPushButton *btn);
    void print(QString text);
    void print(const char* text);
    void clean();
signals:

public slots:
    void cleanButtonClicked();
};

#endif // LOGGER_H
