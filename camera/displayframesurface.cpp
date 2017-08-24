#include "displayframesurface.h"
#include <QDebug>

//! [0]
DisplayFrameSurface::DisplayFrameSurface(QWidget *widget, QObject *parent):
  QAbstractVideoSurface(parent)
      , mWidget(widget)
      , imageFormat(QImage::Format_Invalid)
{

}

QList<QVideoFrame::PixelFormat> DisplayFrameSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }
}
//! [0]

//! [1]
bool DisplayFrameSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid
            && !size.isEmpty()
            && format.handleType() == QAbstractVideoBuffer::NoHandle;
}
//! [1]

//! [2]
bool DisplayFrameSurface::start(const QVideoSurfaceFormat &format)
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    if (imageFormat != QImage::Format_Invalid && !size.isEmpty()) {
        this->imageFormat = imageFormat;
        imageSize = size;
        sourceRect = format.viewport();

        QAbstractVideoSurface::start(format);

        mWidget->updateGeometry();
        updateVideoRect();

        return true;
    } else {
        return false;
    }
}
//! [2]

//! [3]
void DisplayFrameSurface::stop()
{
    currentFrame = QVideoFrame();
    targetRect   = QRect();

    QAbstractVideoSurface::stop();

    mWidget->update();
}
//! [3]

//! [4]
bool DisplayFrameSurface::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat() || surfaceFormat().frameSize() != frame.size())
    {
        setError(IncorrectFormatError);
        stop();
        return false;
    }else{

        currentFrame = frame;
        mWidget->repaint(targetRect);
        return true;
    }
}
//! [4]

//! [5]
void DisplayFrameSurface::updateVideoRect()
{
    QSize size = surfaceFormat().sizeHint();
    qDebug()<<"Size Form surface Format"<<size;
    size.scale(mWidget->size().boundedTo(size), Qt::KeepAspectRatio);
    qDebug()<<"Size For Target Rect"<<size;

    targetRect = QRect(QPoint(0, 0), size);
    targetRect.moveCenter(mWidget->rect().center());
}
//! [5]

//! [6]
void DisplayFrameSurface::paint(QPainter *painter)
{
    if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
        const QTransform oldTransform = painter->transform();

        if (surfaceFormat().scanLineDirection() == QVideoSurfaceFormat::BottomToTop) {
           painter->scale(1, -1);
           painter->translate(0, -mWidget->height());
        }

        QImage image(
                currentFrame.bits(),
                currentFrame.width(),
                currentFrame.height(),
                currentFrame.bytesPerLine(),
                imageFormat);

        emit frameAvailable(image);

        painter->drawImage(targetRect, image, sourceRect);

        painter->setTransform(oldTransform);

        currentFrame.unmap();
    }
}
//! [6]
