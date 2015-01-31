#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWebView>
#include <QPainter>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWebPage>
#include <QWebFrame>

#include <QApplication>


class Overlay : public QWidget{
Q_OBJECT
public:
    Overlay(QWidget *parent);
    QWebView * currentWeb;
    //bool mousePressEvent(QMouseEvent *e);
    bool event(QEvent *e);


    bool press;
    QPoint pointPress;
    QPoint mousePos;

    QImage  testImage;

protected:
    void paintEvent(QPaintEvent *event);
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    QVector <QWebView * > webViewArray;
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *object, QEvent *event);

    Overlay * overlay;

protected:
    void resizeEvent(QResizeEvent *event);




};

#endif // WIDGET_H
