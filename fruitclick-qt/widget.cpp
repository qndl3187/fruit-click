#include "widget.h"
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>

QtPlatrom::QtPlatrom()
    : m_background("images/background.png")
    , m_apple("images/apple.png")
    , m_crunch("sounds/crunch.wav")
    , m_crash("sounds/crash.wav")
{
    QFont font = QApplication::font();
    font.setPixelSize(24);
    QApplication::setFont(font);

    m_app = new FruitClick::Application();
    setFixedSize(320, 480);
    Platform::set(this);
    step();
}

QtPlatrom::~QtPlatrom()
{
    delete m_app;
}

void QtPlatrom::step()
{
    QTimer::singleShot(1000 / 60, this, SLOT(step()));
    update();
}

void QtPlatrom::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_painter = &painter;
    m_app->render();
}

void QtPlatrom::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    m_app->touch(e->x(), height() - e->y());
}

void QtPlatrom::drawImpl(Texture id, float x, float y, float angle)
{
    QPixmap* pixmap = NULL;
    switch(id)
    {
    case FruitClick::Platform::APPLE:
        pixmap = &m_apple;
        break;
    case FruitClick::Platform::BACKGROUND:
        pixmap = &m_background;
        break;
    default:
        break;
    }

    if (pixmap)
    {
        y = height() - y;
        m_painter->translate(x, y);
        m_painter->rotate(-angle * TO_DEG);

        int w = pixmap->width();
        int h = pixmap->height();
        m_painter->drawPixmap(-w/2, -h/2, w, h, *pixmap);

        m_painter->rotate(angle * TO_DEG);
        m_painter->translate(-x, -y);
    }
}

void QtPlatrom::drawTextImpl(const char *text, float x, float y)
{
    y = height() - y;
    m_painter->drawText(x, y, text);
}

void QtPlatrom::playSoundImpl(Sound id)
{
    switch (id)
    {
    case FruitClick::Platform::CRUNCH:
        m_crunch.play();
        break;
    case FruitClick::Platform::CRASH:
        m_crash.play();
        break;
    default:
        break;
    }
}

void QtPlatrom::logImpl(const char *text)
{
    qDebug() << text;
}

