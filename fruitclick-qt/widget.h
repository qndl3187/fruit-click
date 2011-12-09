#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QSound>
#include <QPainter>
#include "application.h"
#include "platform.h"

class QtPlatrom : public QWidget, public FruitClick::Platform
{
    Q_OBJECT

public:
    QtPlatrom();
    ~QtPlatrom();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *e);

protected:
    virtual void drawImpl(Texture id, float x, float y, float angle);
    virtual void drawTextImpl(const char* text, float x, float y);
    virtual void playSoundImpl(Sound id);
    virtual void logImpl(const char* text);

private slots:
    void step();

private:
    FruitClick::Application* m_app;
    QPainter* m_painter;

    QPixmap m_background;
    QPixmap m_apple;

    QSound m_crunch;
    QSound m_crash;
};

#endif
