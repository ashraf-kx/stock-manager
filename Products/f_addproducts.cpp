#include "f_addproducts.h"
#include "ui_f_addproducts.h"

F_AddProducts::F_AddProducts(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::F_AddProducts)
{
    ui->setupUi(this);

    DBH = new DB("localhost:3306","root","","test");

    PreparedStatement *pstmt = DBH->getConnection()->prepareStatement("SELECT * FROM users");
    ResultSet         *resultSet = NULL;
    try{
      resultSet=pstmt->executeQuery();
      while(resultSet->next()){
         qDebug()<<QString::number(resultSet->getInt("id"));
         qDebug()<<QString::fromStdString(resultSet->getString("userName"));
      }
    }catch(SQLException &ex){
      std::cout<<"Exception Occurred"<<ex.getErrorCode()<<endl;
    }

    resultSet->close();
    pstmt->close();
    delete pstmt;
    delete resultSet;
//    DBH->getConnection()->reconnect();
//    DBH->getConnection()->close();
}

F_AddProducts::~F_AddProducts()
{
    delete ui;
}
