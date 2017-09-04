/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "camera.h"

//#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QtMultimedia/QSound>

#include <QMessageBox>
#include <QPalette>
#include <QDebug>


#include <QtWidgets>

Q_DECLARE_METATYPE(QCameraInfo)


Camera::Camera(QWidget *parent) :
    QWidget(parent),
    camera(0),
    imageCapture(0),
    isCapturingImage(false),
    applicationExiting(false)
{
    setupUi(this);
    menuDevices = new QMenu();
    L_displayTextCode->setAttribute(Qt::WA_TranslucentBackground);
    Bt_code->setAttribute(Qt::WA_TranslucentBackground);

    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    // Detect Available camera, list them in the MenuBar.
    foreach (const QCameraInfo &cameraInfo, QCameraInfo::availableCameras()) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);

        menuDevices->addAction(videoDeviceAction);
    }

    isCameraActive = true;

    setCamera(QCameraInfo::defaultCamera());
}

Camera::~Camera()
{
    delete imageCapture;
    delete camera;
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
    delete imageCapture;
    delete camera;

    camera = new QCamera(cameraInfo);

    connect(camera, SIGNAL(stateChanged(QCamera::State)), this, SLOT(updateCameraState(QCamera::State)));
    connect(camera, SIGNAL(error(QCamera::Error)), this, SLOT(displayCameraError()));

    imageCapture = new QCameraImageCapture(camera);

    connect(exposureCompensation, SIGNAL(valueChanged(int)), SLOT(setExposureCompensation(int)));

    camera->setViewfinder(displayFrameUi->displaySurface());

    updateCameraState(camera->state());
    updateLockStatus(camera->lockStatus(), QCamera::UserRequest);

    connect(imageCapture, SIGNAL(error(int,QCameraImageCapture::Error,QString)), this,
            SLOT(displayCaptureError(int,QCameraImageCapture::Error,QString)));

    connect(camera, SIGNAL(lockStatusChanged(QCamera::LockStatus,QCamera::LockChangeReason)),
            this, SLOT(updateLockStatus(QCamera::LockStatus,QCamera::LockChangeReason)));

    connect(Bt_switch,SIGNAL(clicked(bool)),this,SLOT(changeStackindex()));

    connect(displayFrameUi->displaySurface(),SIGNAL(frameAvailable(QImage)),
            this,SLOT(DisplayCodeNow(QImage)));

    connect(Bt_code,SIGNAL(clicked(bool)),this,SLOT(changeCameraState()));

    updateCaptureMode();

    camera->start();
    configureImageSettings();
}

void Camera::changeCameraState()
{
    if(isCameraActive)
    {
        camera->stop();
        isCameraActive = false;
        Bt_code->setIcon(QIcon(":/b/icons/b/ic_replay_2x.png"));
    }else{
        camera->start();
        isCameraActive = true;
        Bt_code->setIcon(QIcon(":/w/icons/w/ic_pause_white_2x.png"));
    }
}

void Camera::changeStackindex()
{
    if(stackedWidget->currentIndex() == 0)
    {
        displaySettings();
        Bt_switch->setIcon(QIcon("://icons/ic_done_2x.png"));
    }
    else
    {
        updateSettings();
        displayViewfinder();
        Bt_switch->setIcon(QIcon("://icons/ic_settings_2x.png"));
    }
}

void Camera::keyPressEvent(QKeyEvent * event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        displayViewfinder();
        camera->searchAndLock();
        event->accept();
        break;
    case Qt::Key_Camera:
        if (camera->captureMode() == QCamera::CaptureStillImage) {
            // takeImage();
        }
        event->accept();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Camera::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        camera->unlock();
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void Camera::DisplayCodeNow(QImage image)
{
    QTime t;
    t.start();

//    decoder.setDecoder( QZXing::DecoderFormat_QR_CODE | QZXing::DecoderFormat_EAN_13 |
//                        QZXing::DecoderFormat_CODE_128 );
    // Use all CodeBar exists
    // decoder.setTryHarder(true);

    QString result = decoder.decodeImage(image);

    if(!result.isEmpty())
    {
        QSound::play("://sounds/beepBarCode.wav");
        L_displayTextCode->setText("Code :"+result+"  "+QString::number(t.elapsed())+" ms."+
                                   decoder.foundedFormat());
        emit codeAvailable(result);
        camera->stop();
        QTimer::singleShot(5000,camera,SLOT(start()));
    }
}

void Camera::configureCaptureSettings()
{
    switch (camera->captureMode()) {
    case QCamera::CaptureStillImage:
        configureImageSettings();
        break;
    default:
        break;
    }
}

void Camera::configureImageSettings()
{
    mSettingsDialog = new ImageSettings(imageCapture);

    mSettingsDialog->setImageSettings(imageSettings);

    settingGridLayout->addWidget(mSettingsDialog);

}

void Camera::updateSettings()
{
    imageSettings = mSettingsDialog->imageSettings();

    imageCapture->setEncodingSettings(imageSettings);
}

void Camera::toggleLock()
{
    switch (camera->lockStatus()) {
    case QCamera::Searching:
    case QCamera::Locked:
        camera->unlock();
        break;
    case QCamera::Unlocked:
        camera->searchAndLock();
    }
}

void Camera::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    QColor indicationColor = Qt::black;

    switch (status) {
    case QCamera::Searching:
        indicationColor = Qt::yellow;
        lockButton->setText(tr("Focusing..."));
        break;
    case QCamera::Locked:
        indicationColor = Qt::darkGreen;
        lockButton->setText(tr("Unlock"));
        break;
    case QCamera::Unlocked:
        indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
        lockButton->setText(tr("Focus"));
        if (reason == QCamera::LockFailed)
            QString x =0; // just to skip this, new message .
    }

    QPalette palette = lockButton->palette();
    palette.setColor(QPalette::ButtonText, indicationColor);
    lockButton->setPalette(palette);
}

void Camera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    isCapturingImage = false;
}

void Camera::startCamera()
{
    camera->start();
}

void Camera::stopCamera()
{
    camera->stop();
}

void Camera::updateCaptureMode()
{
    if (camera->isCaptureModeSupported(QCamera::CaptureStillImage))
        camera->setCaptureMode(QCamera::CaptureStillImage);
}

// enable/disable item on Camera menu List [setting, Stop, Start ]
void Camera::updateCameraState(QCamera::State state)
{
    switch (state) {
    case QCamera::ActiveState:
//        actionStartCamera->setEnabled(false);
//        actionStopCamera->setEnabled(true);

//        actionSettings->setEnabled(true);
        break;
    case QCamera::UnloadedState:
        break;
    case QCamera::LoadedState:
        break;
//        actionStartCamera->setEnabled(true);
//        actionStopCamera->setEnabled(false);

//        actionSettings->setEnabled(false);
    }
}

void Camera::setExposureCompensation(int index)
{
    camera->exposure()->setExposureCompensation(index*0.5);
}


void Camera::displayCameraError()
{
    QMessageBox::warning(this, tr("Camera error"), camera->errorString());
}

void Camera::updateCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void Camera::displayViewfinder()
{
    stackedWidget->setCurrentIndex(0);
}

void Camera::displaySettings()
{
    stackedWidget->setCurrentIndex(1);
}

void Camera::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    Q_UNUSED(fileName);

    isCapturingImage = false;
    if (applicationExiting)
        close();
}

void Camera::closeEvent(QCloseEvent *event)
{
    if (isCapturingImage) {
        setEnabled(false);
        applicationExiting = true;
        event->ignore();
    } else {
        event->accept();
    }
}
