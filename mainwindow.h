#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include<QQmlContext>

#include "glWindow/globjwin.h"
#include "glWindow/glbox.h"

class MainWindow : public QObject
{
    Q_OBJECT

    QQmlApplicationEngine *engine;
public:
    explicit MainWindow(QObject *parent = nullptr);
    explicit MainWindow(QQmlApplicationEngine *eng = nullptr);

    gpu *GPU = nullptr;
signals:

public slots:
    QString buttonClicked(const QString& sA, const QString& sB, const QString& sC);
    void buttonClickedDraw(const QString& sA, const QString& sB, const QString& sC);

    QString CalcBB(float a,float b,float c);

    QString kek(){
        return GPU->Kek;
    }
};

#endif // MAINWINDOW_H
