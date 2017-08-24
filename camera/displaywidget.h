#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QObject>
#include <QWidget>
#include "displayframesurface.h"
#include <QAbstractVideoSurface>


class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = nullptr);

    DisplayFrameSurface *displaySurface();

    QSize sizeHint() const override;

    ~DisplayWidget();
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    DisplayFrameSurface *surface;
};

#endif // DISPLAYWIDGET_H
