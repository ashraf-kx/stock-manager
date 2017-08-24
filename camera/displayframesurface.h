#ifndef DISPLAYFRAMESURFACE_H
#define DISPLAYFRAMESURFACE_H

#include <QObject>
#include <QWidget>
#include <QAbstractVideoSurface>
#include <QtWidgets>
#include <qabstractvideosurface.h>
#include <qvideosurfaceformat.h>
#include <QImage>
#include <QRect>
#include <QVideoFrame>

class DisplayFrameSurface : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    DisplayFrameSurface(QWidget *widget, QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const override;

    bool start(const QVideoSurfaceFormat &format) override;
    void stop() override;

    bool present(const QVideoFrame &frame) override;

    QRect videoRect() const { return targetRect; }
    void updateVideoRect();

public slots:
    void paint(QPainter *painter);

signals:
    void frameAvailable(QImage image);
private:
    QWidget *mWidget;
    QImage::Format imageFormat;
    QRect targetRect;
    QSize imageSize;
    QRect sourceRect;
    QVideoFrame currentFrame;
    int x;
};

#endif // DISPLAYFRAMESURFACE_H
