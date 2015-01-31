#include "widget.h"

Overlay::Overlay(QWidget *parent) : QWidget(parent){
    press = true;
    setPalette(Qt::transparent);
    currentWeb = static_cast<Widget *>(parent)->webViewArray[0];

    //currentWeb->ren
    //setAttribute(Qt::WA_TransparentForMouseEvents);

    testImage = QImage(200,200,QImage::Format_ARGB32);
}

void Overlay::paintEvent(QPaintEvent *event){
    QPainter p(this);

    p.setBrush(QColor(100,255,150));
    p.drawEllipse(100,100,20,20);


    if(press){
        p.drawEllipse(pointPress,40,40);

        int r = 160;

        p.drawEllipse(pointPress + QPoint(-r,0),40,40);  // UP
        p.drawEllipse(pointPress + QPoint(0,r),40,40);   // RIGHT
        p.drawEllipse(pointPress + QPoint(r,0),40,40);   // DOWN
        p.drawEllipse(pointPress + QPoint(0,-r),40,40);  // LEFT

        p.drawEllipse(mousePos ,30,30);

        QSize size =  currentWeb->page()->mainFrame()->contentsSize();
        testImage = QImage(size, QImage::Format_ARGB32_Premultiplied);
        testImage.fill(Qt::transparent);

        QPainter webPainter(&testImage);
        //currentWeb->render(&webPainter);
        currentWeb->page()->mainFrame()->render(&webPainter);
        webPainter.end();

        p.drawImage(0,0,testImage,0,0,200,200);
    }


}

bool Overlay::event(QEvent *e){

    if(e->type() == QEvent::MouseButtonPress ||
       e->type() == QEvent::MouseButtonRelease ||
       e->type() == QEvent::Wheel ||
       e->type() == QEvent::ContextMenu ||
       e->type() == QEvent::MouseMove){



        //qDebug() << e;

        if(e->type() == QEvent::MouseMove){
            update();
            mousePos = static_cast<QMouseEvent * >(e)->pos();
        }

        if(e->type() == QEvent::MouseButtonPress){
            press = true;
            pointPress = static_cast<QMouseEvent * >(e)->pos();
            return QWidget::event(e);
        }

        if(e->type() == QEvent::MouseButtonRelease){
            press = false;
            return QWidget::event(e);
        }

        if(!press){
            QApplication::sendEvent(currentWeb , e);
        }
    }

    return QWidget::event(e);



}







Widget::Widget(QWidget *parent) : QWidget(parent){

    resize(400, 300);

    webViewArray.resize(1);
    webViewArray[0] =  new QWebView(this);
    webViewArray[0]->load(QUrl("http://webew.ru/articles/180.webew"));

    overlay = new Overlay(this);



    //setPalette(Qt::transparent);
    //setAttribute(Qt::WA_TransparentForMouseEvents);

    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    this->installEventFilter(this);
}

bool Widget::eventFilter(QObject *object, QEvent *event){

    return false;
}



void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawLine(0,0,100,100);
}

void Widget::resizeEvent(QResizeEvent *event){
    overlay->resize(event->size());
    webViewArray[0]->resize(event->size());
}
