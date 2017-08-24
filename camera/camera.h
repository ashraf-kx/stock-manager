#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include "ui_camera.h"

#include <QCamera>
#include <QCameraImageCapture>
#include "displaywidget.h"
#include "imagesettings.h"
#include <QZXing>
#include <QMenu>


QT_BEGIN_NAMESPACE
namespace Ui { class Camera; }
QT_END_NAMESPACE

class Camera : public QWidget, private Ui::Camera
{
    Q_OBJECT

public:
    Camera(QWidget *parent = 0);
    ~Camera();

public slots:
    void changeStackindex();
    void updateSettings();
    void changeCameraState();
signals:
    void codeAvailable(const QString& code);
private slots:
    void setCamera(const QCameraInfo &cameraInfo);

    void startCamera();
    void stopCamera();

    void toggleLock();

    void displayCaptureError(int, QCameraImageCapture::Error, const QString &errorString);

    void configureCaptureSettings();
    void configureImageSettings();

    void displayCameraError();

    void updateCameraDevice(QAction *action);

    void updateCameraState(QCamera::State);
    void updateCaptureMode();
    void setExposureCompensation(int index);

    void updateLockStatus(QCamera::LockStatus, QCamera::LockChangeReason);

    void displayViewfinder();
    void displaySettings();

    void imageSaved(int id, const QString &fileName);

    void DisplayCodeNow(QImage image);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);


private:

    QCamera              *camera;
    QCameraImageCapture  *imageCapture;
    QImageEncoderSettings imageSettings;

    QString videoContainerFormat;
    bool    isCapturingImage;
    bool    applicationExiting;

    QZXing        decoder;
    QMenu         *menuDevices;
    ImageSettings *mSettingsDialog;
    bool isCameraActive;
};

#endif
