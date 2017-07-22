#include "f_systemsettings.h"
#include "ui_f_systemsettings.h"

F_SystemSettings::F_SystemSettings(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_SystemSettings)
{
    ui->setupUi(this);

    mCfgDb = new Cfg_Db();

    this->DBH = QSqlDatabase::addDatabase(mCfgDb->getDriverName(),"CnxBrands");
    this->DBH.setHostName(mCfgDb->getHostname());
    this->DBH.setDatabaseName(mCfgDb->getSchemaName());
    this->DBH.setUserName(mCfgDb->getUsername());
    this->DBH.setPassword(mCfgDb->getPassword());
    this->DBH.open();


    listCountries.clear();

    listCountries = getAllCountries();

    connect(ui->Bt_GetLines,SIGNAL(clicked(bool)),this,SLOT(getLines()));
    connect(ui->Bt_SplitLine,SIGNAL(clicked(bool)),this,SLOT(getSplitOneLine()));
}

void F_SystemSettings::getLines()
{
    mainList.clear();
    mainList = ui->text->toPlainText().split("\n");

    ui->Cb_NumLine->clear();

    for(int i=0; i< mainList.size();i++)
        ui->Cb_NumLine->addItem(QString::number(i));

    ui->Bt_GetLines->setDisabled(true);
}

QStringList F_SystemSettings::getAllCountries()
{
    QStringList tmpList;
    if(!this->DBH.isOpen())
        this->DBH.open();
    this->DBH.transaction();

    //! [1] Execute Statements On `countries` Table.
    QSqlQuery *query = new QSqlQuery(this->DBH);

    query->prepare("SELECT name FROM countries");
    query->exec();

    while(query->next()){
        if(!query->value(0).toString().isEmpty())
            tmpList<<query->value(0).toString();
    }

    this->DBH.commit();
    return tmpList;
}

void F_SystemSettings::getSplitOneLine()
{
    getISO();
    getISO3();
    getISO_Numeric();
    getFips();
    getCountry();
    getCapital();
}

void F_SystemSettings::getISO()
{
    QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());

    ui->ISO->setText(line.left(2));
    line.remove(0,2);
    // Clean the WhiteSpaces.
    while (line.left(1).at(0).isSpace()) {
      line.remove(0,1);
    }
    mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
}

void F_SystemSettings::getISO3()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  ui->ISO3->setText(line.left(3));
  line.remove(0,3);
  // Clean the WhiteSpaces.
  while (line.left(1).at(0).isSpace()) {
      line.remove(0,1);
  }
  mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
}

void F_SystemSettings::getISO_Numeric()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  ui->ISO_Numeric->setText(line.left(3));
  line.remove(0,3);
  // Clean the WhiteSpaces.
  while (line.left(1).at(0).isSpace()) {
      line.remove(0,1);
  }
  mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
}

void F_SystemSettings::getFips()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp = line.left(2);
  if(tmp.at(1).isUpper()){
      ui->fips->setText(tmp);
      line.remove(0,2);
      // Clean the WhiteSpaces.
      while (line.left(1).at(0).isSpace()) {
          line.remove(0,1);
      }

      mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
  }
}

void F_SystemSettings::getCountry()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());

  for(int i=0; i<listCountries.length(); i++)
  {
      if(line.contains(listCountries.at(i),Qt::CaseInsensitive))
      {
          ui->Country->setText(line.left(listCountries.at(i).size()));
          line.remove(0,listCountries.at(i).size());
          // Clean the WhiteSpaces.
          while (line.left(1).at(0).isSpace()) {
              line.remove(0,1);
          }
          mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
          i = listCountries.length(); // Break the Loop NOW.
      }
  }
}

void F_SystemSettings::getCapital()
{
    QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
    int index=0;

    for(int i =0;i <line.length(); i++)
    {
        if(line.at(i).isDigit())
        {
            index = i; // save Index.
            i = line.length();
        }
    }

    if( index != 0 ){
        ui->Capital->setText(line.left(index));
        line.remove(0,index);
        // Delete Extra WhiteSpaces in The End.
        QString tmp = ui->Capital->text();
        while (tmp.right(1).at(0).isSpace()) {
            tmp.chop(1);
        }
        ui->Capital->setText(tmp);
        // Clean the WhiteSpaces.
        while (line.left(1).at(0).isSpace()) {
            line.remove(0,1);
        }
        ui->L_info->setText(line);
        mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
    }
}

QString F_SystemSettings::getArea()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

void F_SystemSettings::getRest()
{
  //QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());

}

QString F_SystemSettings::getPopulation()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getContinent()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getTld()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getCurrencyCode()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getCurrencyName()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getPhone()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getPostal_Code_Format()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getPostal_Code_Regex()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getLanguages()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getGeonameid()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getNeighbours()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

QString F_SystemSettings::getEquivalentFipsCode()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp;

  return tmp;
}

F_SystemSettings::~F_SystemSettings()
{
    delete ui;
}
