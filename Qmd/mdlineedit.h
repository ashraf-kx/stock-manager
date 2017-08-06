#ifndef MDLINEEDIT_H
#define MDLINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLine>
#include <QPushButton>
#include <QGridLayout>

// QAnimate Framework
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QTimer>

class MDLabel: public QLabel
{
    Q_OBJECT
    Q_PROPERTY(qreal fontPointSize READ fontPointSize WRITE setFontPointSize)
public:
    MDLabel(QWidget* parent = 0)
        :QLabel(parent)
    {

    }

    void mousePressEvent(QMouseEvent *ev) override
    {
        if(ev->button() == Qt::LeftButton)
        {
            emit clicked();
        }
    }
    qreal fontPointSize() const
    {
        return font().pointSizeF();
    }

public slots:
    void setFontPointSize(qreal pointSizeF)
    {
        QFont f = QFont();
        f.setPointSizeF(pointSizeF);
        setFont(f);
    }

signals:
    void clicked();
};

class MDLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString labelText READ labelText WRITE setLabelText)
    Q_PROPERTY(QString helperText READ helperText WRITE setHelperText)
    Q_PROPERTY(QString placeHolder READ placeHolder WRITE setPlaceHolder)

    Q_PROPERTY(bool helperVisible READ helperIsVisible WRITE setHelperVisibile)
    Q_PROPERTY(bool leftIconVisible READ leftIconIsVisible WRITE setLeftIconVisibile)
    Q_PROPERTY(bool rightIconVisible READ rightIconIsVisible WRITE setRightIconVisibile)

    Q_PROPERTY(QPixmap LIconPixmap READ leftIconPixmap WRITE setLeftIconPixmap)
    Q_PROPERTY(QPixmap RIconPixmap READ rightIconPixmap WRITE setRightIconPixmap)

    Q_PROPERTY(QSize LIconSize READ leftIconSize WRITE setLeftIconSize)
    Q_PROPERTY(QSize RIconSize READ rightIconSize WRITE setRightIconSize)

public:
    explicit MDLineEdit(QWidget *parent = 0);
    MDLineEdit(const QString& labelText,const QString& placeholder,const QString& helperText);

    void loadStyle();
public slots:
    void resting();
    void activeStyle();
    void floating();
    void inactiveStyle();

    void parseError(const QString &msg);
    void setDisabled(bool state);

    // Qt-Property Sheet
    QString text() const;
    void setText(const QString& text);

    QString labelText() const;
    void setLabelText(const QString& text);

    QString helperText() const;
    void setHelperText(const QString& text);

    QString placeHolder() const;
    void setPlaceHolder(const QString& text);

    bool helperIsVisible();
    void setHelperVisibile(bool visible);

    bool leftIconIsVisible();
    void setLeftIconVisibile(bool visible);

    bool rightIconIsVisible();
    void setRightIconVisibile(bool visible);

    QPixmap leftIconPixmap();
    void setLeftIconPixmap(const QPixmap& pixmap);

    QPixmap rightIconPixmap();
    void setRightIconPixmap(const QPixmap& pixmap);

    QSize leftIconSize() const ;
    void setLeftIconSize(const QSize& size);

    QSize rightIconSize() const;
    void setRightIconSize(const QSize& size);

    QPushButton *getLeftBtn();
    QPushButton *getRightBtn();
    QLabel      *getHelper();
    QLineEdit   *getLineEdit();
    MDLabel     *getLabel();
private:

    QPropertyAnimation *zoomInFont;
    QPropertyAnimation *zoomOutFont;

    MDLabel        *mlabel;
    QLineEdit    *mlineEdit;
    QGridLayout* layout;

    QSpacerItem *verticalSpacerUp;
    QSpacerItem *verticalSpacerDown;
    QFrame      *mline;

    QPushButton *mrightButton;
    QPushButton *mleftButton;
    QLabel      *mhelper;

};

#endif // MDLINEEDIT_H
