#include "mdlineedit.h"

MDLineEdit::MDLineEdit(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("MDLineEdit");
    this->loadStyle();

    // init
    mlineEdit = new QLineEdit(this);
    mlineEdit->setObjectName(QStringLiteral("mlineEdit"));
    mlineEdit->setPlaceholderText(tr("Type Something"));
    mlineEdit->setMinimumWidth(120);
    mlineEdit->setVisible(false);

    mlabel = new MDLabel(this);
    mlabel->setObjectName(QStringLiteral("mlabel"));
    mlabel->setText(tr("First Name *"));
    mlineEdit->setMinimumWidth(120);
    mlabel->setVisible(true);

    layout = new QGridLayout(this);
    this->setLayout(layout);

    layout->setSpacing(0);
    layout->setObjectName(QStringLiteral("Layout"));
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setContentsMargins(0, 0, 0, 0);
    verticalSpacerUp   = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalSpacerDown = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacerUp,0,1,1,1);

    mlabel->setScaledContents(true);
    mlabel->setWordWrap(true);
    mlabel->setCursor(QCursor(Qt::IBeamCursor));
    layout->addWidget(dynamic_cast<QLabel*>(mlabel),1,1,1,1);
    layout->addWidget(mlineEdit,2,1,1,1);

    mline = new QFrame(this);
    mline->setObjectName(QStringLiteral("mline"));
    mline->setMinimumSize(QSize(0, 1));
    mline->setMaximumHeight(2);
    mline->setFrameShape(QFrame::HLine);
    mline->setFrameShadow(QFrame::Sunken);

    mhelper = new QLabel(this);
    mhelper->setObjectName(QStringLiteral("mhelper"));
    mhelper->setScaledContents(true);
    mhelper->setWordWrap(true);
    mhelper->setText(tr("Only Lettres, Numbers a spaces"));

    layout->addWidget(mhelper, 4, 1,1,1);

    mleftButton = new QPushButton(this);
    mleftButton->setObjectName(QStringLiteral("mleftButton"));
    mleftButton->setCursor(QCursor(Qt::PointingHandCursor));
    QIcon icon;
    icon.addFile(QStringLiteral(":/ic_person_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
    mleftButton->setIcon(icon);
    mleftButton->setIconSize(QSize(24, 24));
    mleftButton->setMaximumSize(QSize(40,24));
    mleftButton->setFlat(true);

    layout->addWidget(mleftButton, 2, 0,1,1);

    mrightButton = new QPushButton(this);
    mrightButton->setObjectName(QStringLiteral("mrightButton"));
    mrightButton->setCursor(QCursor(Qt::PointingHandCursor));
    mrightButton->setFocusPolicy(Qt::NoFocus);
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/ic_mic_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
    mrightButton->setIcon(icon1);
    mrightButton->setIconSize(QSize(24, 24));
    mrightButton->setMaximumSize(QSize(24,24));
    mrightButton->setFlat(true);

    layout->addWidget(mrightButton, 2, 2,1,1);

    layout->addWidget(mline,3, 1, 1, 2);
    layout->addItem(verticalSpacerDown,5,1,1,1);

    zoomOutFont = new QPropertyAnimation(dynamic_cast<QLabel*>(mlabel), "fontPointSize");

    zoomOutFont->setDuration(300);
    zoomOutFont->setStartValue(14);
    zoomOutFont->setEndValue(9);
    zoomOutFont->setEasingCurve(QEasingCurve::Linear);

    zoomInFont = new QPropertyAnimation(dynamic_cast<QLabel*>(mlabel), "fontPointSize");

    zoomInFont->setDuration(300);
    zoomInFont->setStartValue(9);
    zoomInFont->setEndValue(14);
    zoomInFont->setEasingCurve(QEasingCurve::Linear);

    connect(mlabel,SIGNAL(clicked()),this,SLOT(floating()));
    connect(mlineEdit,SIGNAL(editingFinished()),this,SLOT(resting()));

    // connect(mleftButton,SIGNAL(clicked(bool)),this,SLOT(parseError()));

    connect(mlineEdit,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(activeStyle()));

    layout->addWidget(mlabel,2,1); // Resting.
    layout->addWidget(mlineEdit,1,1); // resting.
}

MDLineEdit::MDLineEdit(const QString &labelText, const QString &placeholder, const QString &helperText)
{
    mlabel->setText(labelText);
    mlineEdit->setPlaceholderText(placeholder);
    mhelper->setText(helperText);
}

void MDLineEdit::floating()
{
    layout->addWidget(mlabel,1,1,1,1); // floating.
    layout->addWidget(mlineEdit,2,1,1,1); // floating.
    zoomOutFont->start();

    mlineEdit->setFocus();
    mlineEdit->setCursorPosition(0);
    mlineEdit->setVisible(true);

    activeStyle();
}

void MDLineEdit::resting()
{
    if(mlineEdit->text().isEmpty())
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
    mlabel->setStyleSheet("color:#0091ea;");
    mline->setStyleSheet("border:2px solid #0091ea;");
}

void MDLineEdit::inactiveStyle()
{
    mlabel->setStyleSheet("color:#c7c7c7;");
    mline->setStyleSheet("border:1px solid #c7c7c7;");
}

void MDLineEdit::parseError(const QString& msg)
{
    mhelper->setText(msg);
    mhelper->setStyleSheet("padding-top: 8 dp;"
                              "color: #ff1744;"
                              "font: calibri 10pt ;");
    mlabel->setStyleSheet("color  : #ff1744;");
    mline->setStyleSheet("border:2px solid #FF1744;");
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

void MDLineEdit::loadStyle()
{
    this->setStyleSheet("#MDLineEdit {"
                "background-color: rgb(255, 255, 255);}"
                "#mhelper"
                "{"
                "padding-top: 8 dp;"
                "color: #c7c7c7;"
                "font: calibri 10pt;"
                "}"

                "#mleftButton"
                "{"
                "padding-right:16 dp;"
                "}"

                "#mlineEdit"
                "{"
                "border:none;"
                "font: calibri 14pt;"
                "font: 75 14pt \"Calibri\";"
                "padding-bottom: 8 dp;"
                "}"

                "#mline"
                "{"
                "border:2px solid #c7c7c7;"
                "}"
                "#mlabel{font: calibri 14pt; "
                        "padding-top: 16 dp;"
                        "padding-bottom: 8 dp;"
                        "color:#c7c7c7;"
                        "}");
}
