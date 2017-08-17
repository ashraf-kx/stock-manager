#include "mdlineedit.h"

MDLineEdit::MDLineEdit(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("MDLineEdit");

    // init
    qreal mFontSize = 14;//fontInfo().pixelSize();
    qDebug()<<mFontSize<<" size MDLineEdit";
    mlineEdit = new QLineEdit(this);
    mlineEdit->setObjectName(QStringLiteral("mlineEdit"));
    // mlineEdit->setMinimumWidth(260);
    mlineEdit->setVisible(false);

    mlabel = new MDLabel(this);
    mlabel->setObjectName(QStringLiteral("mlabel"));
    // mlabel->setMinimumWidth(260);
    mlabel->setScaledContents(false);
    mlabel->setWordWrap(false);
    mlabel->setCursor(QCursor(Qt::IBeamCursor));
    mlabel->setVisible(true);

    layout = new QGridLayout(this);
    this->setLayout(layout);

    layout->setSpacing(0);
    layout->setObjectName(QStringLiteral("Layout"));
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    layout->setContentsMargins(0, 0, 0, 0);

    verticalSpacerUp   = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalSpacerDown = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacerUp,0,1,1,1);

    layout->addWidget(dynamic_cast<QLabel*>(mlabel),1,1,1,1);
    QLabel *lb = new QLabel(" ");
    layout->addWidget(mlineEdit,2,1,1,1);
    layout->addWidget(lb,1,2,1,1);

    mline = new QFrame(this);
    mline->setObjectName(QStringLiteral("mline"));
    mline->setMinimumHeight(1);
    mline->setMaximumHeight(2);
    mline->setFrameShape(QFrame::HLine);
    mline->setFrameShadow(QFrame::Sunken);

    mhelper = new QLabel(this);
    mhelper->setObjectName(QStringLiteral("mhelper"));
    mhelper->setScaledContents(true);
    mhelper->setWordWrap(true);

    layout->addWidget(mhelper, 4, 1,1,1);

    mleftButton = new QPushButton(this);
    mleftButton->setObjectName(QStringLiteral("mleftButton"));
    mleftButton->setCursor(QCursor(Qt::PointingHandCursor));
    mleftButton->setFlat(true);

    layout->addWidget(mleftButton, 2, 0,1,1);

    mrightButton = new QPushButton(this);
    mrightButton->setObjectName(QStringLiteral("mrightButton"));
    mrightButton->setCursor(QCursor(Qt::PointingHandCursor));
    mrightButton->setFocusPolicy(Qt::NoFocus);
    mrightButton->setFlat(true);

    layout->addWidget(mrightButton, 2, 2,1,1);

    layout->addWidget(mline,3, 1, 1, 2);
    layout->addItem(verticalSpacerDown,5,1,1,1);

    zoomOutFont = new QPropertyAnimation(dynamic_cast<QLabel*>(mlabel), "fontPointSize");

    zoomOutFont->setDuration(200);
    zoomOutFont->setStartValue(mFontSize);
    zoomOutFont->setEndValue(mFontSize-3);
    zoomOutFont->setEasingCurve(QEasingCurve::InSine);

    zoomInFont = new QPropertyAnimation(dynamic_cast<QLabel*>(mlabel), "fontPointSize");

    zoomInFont->setDuration(200);
    zoomInFont->setStartValue(mFontSize-3);
    zoomInFont->setEndValue(mFontSize);
    zoomInFont->setEasingCurve(QEasingCurve::OutSine);

    connect(mlabel,SIGNAL(clicked()),this,SLOT(floating()));
    connect(mlineEdit,SIGNAL(editingFinished()),this,SLOT(resting()));

    connect(mleftButton,SIGNAL(clicked(bool)),this,SLOT(parseError()));

    connect(mlineEdit,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(activeStyle()));

    layout->addWidget(mlabel,2,1); // Resting.
    layout->addWidget(mlineEdit,1,1); // resting.

    this->mlabel->setFontPointSize(mFontSize);
    mlineEdit->setFont(QFont("",mFontSize));
}

void MDLineEdit::floating()
{
    if(mlineEdit->text().isEmpty() )
    {

        zoomOutFont->start();

        mlineEdit->setFocus();
        mlineEdit->setCursorPosition(0);
        layout->addWidget(mlabel,1,1,1,1); // floating.
        layout->addWidget(mlineEdit,2,1,1,1); // floating.
        mlineEdit->setVisible(true);

        activeStyle();
    }
}

void MDLineEdit::resting()
{
    if(mlineEdit->text().isEmpty() )
    {
        layout->addWidget(mlabel,2,1); // replace.
        layout->addWidget(mlineEdit,1,1);

        mlineEdit->setVisible(false);
        inactiveStyle();

        zoomInFont->start();
    }else
    {
        inactiveStyle();
    }

}

void MDLineEdit::activeStyle()
{
    mlabel->setStyleSheet("color:#0091EA;");
    mline->setStyleSheet("border:2px solid #0091EA;");
}

void MDLineEdit::inactiveStyle()
{
    mlabel->setStyleSheet("color:#c7c7c7;");
    mline->setStyleSheet("border:1px solid #c7c7c7;");
}

void MDLineEdit::parseError(const QString& msg)
{
    if(!msg.isEmpty())
        mhelper->setText(msg);

    mhelper->setStyleSheet("padding-top: 8 dp;"
                           "color: #FF1744;");  // "font-size: 11pt ;"
    mlabel->setStyleSheet( "color: #FF1744;");
    mline->setStyleSheet(  "border:2px solid #FF1744;");
}

void MDLineEdit::setDisabled(bool state)
{
    this->setEnabled(!state);
    if(state)
    {
        mline->setStyleSheet("border:1px dashed #c7c7c7;");
    }else
    {
        mline->setStyleSheet("border:1px solid #c7c7c7;");
    }
}

QString MDLineEdit::text() const
{
    return mlineEdit->text();
}

void MDLineEdit::setText(const QString &text)
{
    mlineEdit->setText(text);
}

QString MDLineEdit::labelText() const
{
    return mlabel->text();
}

void MDLineEdit::setLabelText(const QString &text)
{
    mlabel->setText(text);
}

QString MDLineEdit::helperText() const
{
    return mhelper->text();
}

void MDLineEdit::setHelperText(const QString &text)
{
    mhelper->setText(text);
}

QString MDLineEdit::placeHolder() const
{
    return mlineEdit->placeholderText();
}

void MDLineEdit::setPlaceHolder(const QString &text)
{
    mlineEdit->setPlaceholderText(text);
}

bool MDLineEdit::helperIsVisible()
{
    return mhelper->isVisible();
}

void MDLineEdit::setHelperVisibile(bool visible)
{
    mhelper->setVisible(visible);
}

bool MDLineEdit::leftIconIsVisible()
{
    return mleftButton->isVisible();
}

void MDLineEdit::setLeftIconVisibile(bool visible)
{
    mleftButton->setVisible(visible);
}

bool MDLineEdit::rightIconIsVisible()
{
    return mrightButton->isVisible();
}

void MDLineEdit::setRightIconVisibile(bool visible)
{
    mrightButton->setVisible(visible);
}

QPixmap MDLineEdit::leftIconPixmap()
{

    return mleftButton->icon().pixmap(mleftButton->iconSize());
}

void MDLineEdit::setLeftIconPixmap(const QPixmap &pixmap)
{
    mleftButton->setIcon(QIcon(pixmap));
}

QPixmap MDLineEdit::rightIconPixmap()
{
    return mrightButton->icon().pixmap(mrightButton->iconSize());
}

void MDLineEdit::setRightIconPixmap(const QPixmap &pixmap)
{
    mrightButton->setIcon(QIcon(pixmap));
}

QSize MDLineEdit::leftIconSize() const
{
    return mleftButton->iconSize();
}

void MDLineEdit::setLeftIconSize(const QSize &size)
{
    mleftButton->setIconSize(size);
}

QSize MDLineEdit::rightIconSize() const
{
    return mrightButton->iconSize();
}

void MDLineEdit::setRightIconSize(const QSize &size)
{
    mrightButton->setIconSize(size);
}

QPushButton *MDLineEdit::getLeftBtn()
{
    return mleftButton;
}

QPushButton *MDLineEdit::getRightBtn()
{
    return mrightButton;
}

QLabel *MDLineEdit::getHelper()
{
    return mhelper;
}

QLineEdit *MDLineEdit::getLineEdit()
{
    return mlineEdit;
}

MDLabel *MDLineEdit::getLabel()
{
    return mlabel;
}

void MDLineEdit::showLineEdit()
{
    layout->addWidget(mlabel,1,1,1,1); // floating.
    layout->addWidget(mlineEdit,2,1,1,1); // floating.
    mlineEdit->setVisible(true);
}

// TODO (3): Use Validation With MDLineEdit.
