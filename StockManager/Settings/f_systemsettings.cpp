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
    textOut.clear();
    mainList.clear();

    listCountries = getAllCountries();

    connect(ui->Bt_GetLines,SIGNAL(clicked(bool)),this,SLOT(getLines()));
    connect(ui->Bt_SplitLine,SIGNAL(clicked(bool)),this,SLOT(getUsefullText()));
    connect(ui->Cb_NumLine,SIGNAL(currentIndexChanged(int)),this,SLOT(clearAllInputs()));
}

void F_SystemSettings::getUsefullText()
{
    for(int i=0; i< mainList.length(); i++)
    {
        ui->Cb_NumLine->setCurrentIndex(i);
        getSplitOneLine();
    }

    ui->text->clear();
    ui->text->setPlainText(textOut);
}

void F_SystemSettings::clearAllInputs()
{
    ui->ISO->clear();
    ui->ISO3->clear();
    ui->ISO_Numeric->clear();
    ui->fips->clear();
    ui->Country->clear();
    ui->Capital->clear();
    ui->Area->clear();
    ui->Population->clear();
    ui->Continent->clear();
    ui->tld->clear();
    ui->CurrencyCode->clear();
    ui->CurrencyName->clear();
    ui->Phone->clear();
    ui->PostalCodeFormat->clear();
    ui->PostalCodeReg->clear();
    ui->Languages->clear();
    ui->geonameid->clear();
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

    query->prepare("SELECT country FROM country_info");
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
    getArea();
    getPopulation();
    getContinent();
    getTld();
    getCurrencyCode();
    getCurrencyName();
    getPhone();
    getPostal_Code_Format();
    // Do not Call : getPostal_Code_Regex() Here ;)
    getLanguages();
    getGeonameid();

//    // Get One Line.
//    QString tmp  = ui->ISO->text()+"<0>";
//            tmp += ui->ISO3->text()+"<1>";
//            tmp += ui->ISO_Numeric->text()+"<2>";
//            tmp += ui->fips->text()+"<3>";
//            tmp += ui->Country->text()+"<4>";
//            tmp += ui->Capital->text()+"<5>";
//            tmp += ui->Area->text()+"<6>";
//            tmp += ui->Population->text()+"<7>";
//            tmp += ui->Continent->text()+"<8>";
//            tmp += ui->tld->text()+"<9>";
//            tmp += ui->CurrencyCode->text()+"<a>";
//            tmp += ui->CurrencyName->text()+"<b>";
//            tmp += ui->Phone->text()+"<c>";
//            tmp += ui->PostalCodeFormat->text()+"<d>";
//            tmp += ui->PostalCodeReg->text()+"<e>";
//            tmp += ui->Languages->text()+"<f>\n";
    // Get One Line.
        QString tmp  ="(\""+ui->ISO->text()+"\",";
                tmp += "\""+ui->ISO3->text()+"\",";
                tmp += "\""+ui->ISO_Numeric->text()+"\",";
                tmp += "\""+ui->fips->text()+"\",";
                tmp += "\""+ui->Country->text()+"\",";
                tmp += "\""+ui->Capital->text()+"\",";
                tmp += "\""+ui->Area->text()+"\",";
                tmp += "\""+ui->Population->text()+"\",";
                tmp += "\""+ui->Continent->text()+"\",";
                tmp += "\""+ui->tld->text()+"\",";
                tmp += "\""+ui->CurrencyCode->text()+"\",";
                tmp += "\""+ui->CurrencyName->text()+"\",";
                tmp += "\""+ui->Phone->text()+"\",";
                tmp += "\""+ui->PostalCodeFormat->text()+"\",";
                tmp += "\""+ui->PostalCodeReg->text()+"\",";
                tmp += "\""+ui->Languages->text()+"\");\n";
     textOut += tmp;
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
  if(tmp.at(1).isUpper() && tmp.at(0).isUpper()){
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
      if(line.contains(listCountries.at(i),Qt::CaseSensitive))
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
            index = i;         // save Index.
            i = line.length(); // Break Loop
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

void F_SystemSettings::getArea()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index=0;

  for(int i =0; i <line.length(); i++)
  {
      if(!line.at(i).isDigit())
      {
          index = i;         // save Index.
          i = line.length(); // Break Loop.
      }
  }

  if( index > 0 ){
      ui->Area->setText(line.left(index));
      line.remove(0,index);
      // Delete Extra WhiteSpaces in The End.
      QString tmp = ui->Area->text();
      while (tmp.right(1).at(0).isSpace()) {
          tmp.chop(1);
      }
      ui->Area->setText(tmp);
      // Clean the WhiteSpaces.
      while (line.left(1).at(0).isSpace()) {
          line.remove(0,1);
      }
      ui->L_info->setText(line);
      mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
  }
}

void F_SystemSettings::getPopulation()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index=0;

  for(int i =0;i <line.length(); i++)
  {
      if(!line.at(i).isDigit())
      {
          index = i;              // Save Index.
          i     = line.length();  // Brk Loop.
      }
  }

  if( index > 0 ){
      ui->Population->setText(line.left(index));
      line.remove(0,index);
      // Delete Extra WhiteSpaces in The End.
      QString tmp = ui->Population->text();
      while (tmp.right(1).at(0).isSpace()) {
          tmp.chop(1);
      }
      ui->Population->setText(tmp);
      // Clean the WhiteSpaces.
      while (line.left(1).at(0).isSpace()) {
          line.remove(0,1);
      }
      ui->L_info->setText(line);
      mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
  }
}

void F_SystemSettings::getContinent()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index    = 0;

  for(int i = 0; i < line.length(); i++)
  {
      if(!line.at(i).isLetter())
      {
          index = i;             // save Index.
          i     = line.length(); // Break Loop.
      }
  }

  if( index > 0 ){
      if(line.left(index).at(0).isUpper()){ // IS Continent string FORMAT X??
          ui->Continent->setText(line.left(index));
          line.remove(0,index);
          // Delete Extra WhiteSpaces in The End.
          QString tmp = ui->Continent->text();
          while (tmp.right(1).at(0).isSpace()) {
              tmp.chop(1);
          }
          ui->Continent->setText(tmp);
          // Clean the WhiteSpaces.
          while (line.left(1).at(0).isSpace()) {
              line.remove(0,1);
          }
          ui->L_info->setText(line);
          mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
      }
  }
}

void F_SystemSettings::getTld()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index=0;

  for(int i =0;i <line.length(); i++)
  {
      if(!line.at(i).isLetter()  && !line.at(i).isPunct() )
      {
          index = i;             // save Index.
          i     = line.length(); // Break Loop.
      }
  }

  if( index > 0 ){
      if(line.left(index).contains(".",Qt::CaseInsensitive)) // make sure FORMAT .xx
      {
          ui->tld->setText(line.left(index));
          line.remove(0,index);
          // Delete Extra WhiteSpaces in The End.
          QString tmp = ui->tld->text();
          while (tmp.right(1).at(0).isSpace()) {
              tmp.chop(1);
          }
          ui->tld->setText(tmp);
          // Clean the WhiteSpaces.
          while (line.left(1).at(0).isSpace()) {
              line.remove(0,1);
          }
          ui->L_info->setText(line);
          mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
      }
  }
}

void F_SystemSettings::getCurrencyCode()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index=0;

  for(int i =0;i <line.length(); i++)
  {
      if(!line.at(i).isLetter())
      {
          index = i;             // save Index.
          i     = line.length(); // Brk Loop.
      }
  }

  if( index > 0 ){
      if(line.left(index).at(0).isUpper() && line.left(index).at(1).isUpper()){ // verif: XXX
          ui->CurrencyCode->setText(line.left(index));
          line.remove(0,index);
          // Delete Extra WhiteSpaces in The End.
          QString tmp = ui->CurrencyCode->text();
          while (tmp.right(1).at(0).isSpace()) {
              tmp.chop(1);
          }
          ui->CurrencyCode->setText(tmp);
          // Clean the WhiteSpaces.
          while (line.left(1).at(0).isSpace()) {
              line.remove(0,1);
          }
          ui->L_info->setText(line);
          mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
      }
  }
}

void F_SystemSettings::getCurrencyName()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index=0;

  for(int i =0;i <line.length(); i++)
  {
      if(!line.at(i).isLetter())
      {
          index = i;             // save Index.
          i     = line.length(); // Break Loop
      }
  }

  if( index > 0 ){
      if(line.left(index).at(0).isUpper() && line.left(index).at(1).isLower()){ // verif: Xxx
          ui->CurrencyName->setText(line.left(index));
          line.remove(0,index);
          // Delete Extra WhiteSpaces in The End.
          QString tmp = ui->CurrencyName->text();
          while (tmp.right(1).at(0).isSpace()) {
              tmp.chop(1);
          }
          ui->CurrencyName->setText(tmp);
          // Clean the WhiteSpaces.
          while (line.left(1).at(0).isSpace()) {
              line.remove(0,1);
          }
          ui->L_info->setText(line);
          mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
      }
  }
}

void F_SystemSettings::getPhone()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index=0;

  for(int i =0;i <line.length(); i++)
  {
      if(!line.at(i).isDigit() || (line.at(i).isLetter() && !line.at(i).isSpace()))
      {
          index = i;             // save Index.
          i     = line.length(); // break Loop.
      }
  }

  if( index > 0 ){
      ui->Phone->setText(line.left(index));
      line.remove(0,index);
      // Delete Extra WhiteSpaces in The End.
      QString tmp = ui->Phone->text();
      while (tmp.right(1).at(0).isSpace()) {
          tmp.chop(1);
      }
      ui->Phone->setText(tmp);
      // Clean the WhiteSpaces.
      while (line.left(1).at(0).isSpace()) {
          line.remove(0,1);
      }
      ui->L_info->setText(line);
      mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
  }
}

void F_SystemSettings::getPostal_Code_Format()
{
  if(getPostal_Code_Regex())
  {
    QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
    QString tmp;

    int idxEnd   = line.indexOf('$',Qt::CaseSensitive);
    for(int i=0; i<idxEnd; i++)  tmp += line.at(i);
    line.remove(idxEnd,1); // Delete "$".
    line.remove(0,idxEnd); // Delete PostalCodeFormat.

    // Delete Extra WhiteSpaces in The End.
    while (tmp.right(1).at(0).isSpace()) {
        tmp.chop(1);
    }
    ui->PostalCodeFormat->setText(tmp);
    // Clean the WhiteSpaces.
    while (line.left(1).at(0).isSpace()) {
      line.remove(0,1);
    }

    ui->L_info->setText(line);
    mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
  }
}

bool F_SystemSettings::getPostal_Code_Regex()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  QString tmp; tmp.clear();
  if(line.contains("$"))
  {
      int idxBegin = line.indexOf('^',Qt::CaseSensitive);
      int idxEnd   = line.indexOf('$',Qt::CaseSensitive);
      for(int i = idxBegin; i <= idxEnd; i++) tmp += line.at(i);

      ui->PostalCodeReg->setText(tmp);

      line.remove(idxBegin,(idxEnd-idxBegin));
      // line.insert(idxBegin,"$");

      ui->L_info->setText(line);
      mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);

      return true;
  }else
      return false;
}

void F_SystemSettings::getLanguages()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index=0;

  for(int i =0;i <line.length(); i++)
  {
      if(line.at(i).isSpace())
      {
          index = i;         // save Index.
          i = line.length(); // Break Loop
      }
  }

  if( index > 0 ){
          // verif: Xxx
          ui->Languages->setText(line.left(index));
          line.remove(0,index);
          // Delete Extra WhiteSpaces in The End.
          QString tmp = ui->Languages->text();
          while (tmp.right(1).at(0).isSpace()) {
              tmp.chop(1);
          }
          ui->Languages->setText(tmp);
          // Clean the WhiteSpaces.
          while (line.left(1).at(0).isSpace()) {
              line.remove(0,1);
          }
          ui->L_info->setText(line);
          mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
  }
}

void F_SystemSettings::getGeonameid()
{
  QString line = mainList.at(ui->Cb_NumLine->currentText().toInt());
  int index=0;

  for(int i =0;i <line.length(); i++)
  {
      if(!line.at(i).isDigit())
      {
          index = i;             // save Index.
          i     = line.length(); // break Loop.
      }
  }

  if( index > 0 ){
      ui->geonameid->setText(line.left(index));
      line.remove(0,index);
      // Delete Extra WhiteSpaces in The End.
      QString tmp = ui->geonameid->text();
      while (tmp.right(1).at(0).isSpace()) {
          tmp.chop(1);
      }
      ui->geonameid->setText(tmp);
      // Clean the WhiteSpaces.
      while (line.left(1).at(0).isSpace()) {
          line.remove(0,1);
      }
      ui->L_info->setText(line);
      mainList.replace(ui->Cb_NumLine->currentText().toInt(),line);
  }
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
