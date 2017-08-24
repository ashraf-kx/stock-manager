#include "displaywidget.h"

#include <QtWidgets>
#include <qvideosurfaceformat.h>

//! [0]
DisplayWidget::DisplayWidget(QWidget *parent)
    : QWidget(parent)
    , surface(0)
{
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NoSystemBackground, true);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::black);
    setPalette(palette);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    surface = new DisplayFrameSurface(this);
}

DisplayFrameSurface *DisplayWidget::displaySurface()
{
    return surface;
}
//! [0]

//! [1]
DisplayWidget::~DisplayWidget()
{
    delete surface;
}
//! [1]

//! [2]
QSize DisplayWidget::sizeHint() const
{
    return surface->surfaceFormat().sizeHint();
}
//! [2]


//! [3]
void DisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (surface->isActive()) {
        const QRect videoRect = surface->videoRect();

        if (!videoRect.contains(event->rect())) {
            QRegion region = event->region();
            region = region.subtracted(videoRect);

            QBrush brush = palette().background();

            foreach (const QRect &rect, region.rects())
                painter.fillRect(rect, brush);
        }

        surface->paint(&painter);
    } else {
        painter.fillRect(event->rect(), palette().background());
    }
}
//! [3]

//! [4]
void DisplayWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    surface->updateVideoRect();
}
//! [4]
