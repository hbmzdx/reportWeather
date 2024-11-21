#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>
#include<QDebug>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPainter>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,menuQuit(new QMenu(this))
{
    ui->setupUi(this);
    setFixedSize(423,713);
    setWindowFlag(Qt::FramelessWindowHint);

    //menuQuit =new QMenu(this);
    //设置菜单项文字颜色
    menuQuit->setStyleSheet("QMenu::item{color:white}");

    QAction *openAct=new QAction(QIcon(":/res/close.png"),tr("退出"),this);
    menuQuit->addAction(openAct);
    connect(menuQuit,&QMenu::triggered,this,[=]{
        this->close();
        }
    );

    //获取http请求get请求
    manager=new  QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,[](){
        qDebug()<<"Manager finished";
    });
    //strurl="http://gfeljm.tianqiapi.com/api?unescape=1&version=v61&appid=77932665&appsecret=Vpfwt5Ka";
    strurl="http://gfeljm.tianqiapi.com/api?unescape=1&version=v9&appid=77932665&appsecret=Vpfwt5Ka";


    QUrl urlTianQi(strurl);
    QNetworkRequest res(urlTianQi);
     reply=manager->get(res);
    connect(manager,&QNetworkAccessManager::finished,this,&Widget::readHttpReply);

    mWeekList<<ui->labelday0<<ui->labelday1<<ui->labelday2<<ui->labelday3
            <<ui->labelday4<<ui->labelday5;
    mDateList <<ui->labelDate0<<ui->labelDate1<<ui->labelDate2<<ui->labelDate3
             <<ui->labelDate4<<ui->labelDate5;
    mIconList<<ui->labelWeatherIcon0<<ui->labelWeatherIcon1<<ui->labelWeatherIcon2
            <<ui->labelWeatherIcon3<<ui->labelWeatherIcon4<<ui->labelWeatherIcon5;
    mWeaTypeList<<ui->labelWeatherTypeDate0<<ui->labelWeatherTypeDate1<<ui->labelWeatherTypeDate2
               <<ui->labelWeatherTypeDate3<<ui->labelWeatherTypeDate4<<ui->labelWeatherTypeDate5;
    mAirqList<<ui->labelaiq0<<ui->labelaiq1<<ui->labelaiq2<<ui->labelaiq3
            <<ui->labelaiq4<<ui->labelaiq5;
    mFxList<<ui->labelFL0<<ui->labelFL1<<ui->labelFL2<<ui->labelFL3
          <<ui->labelFL4<<ui->labelFL5;
    mFlList<<ui->labelFL0<<ui->labelFL1<<ui->labelFL2<<ui->labelFL3
          <<ui->labelFL4<<ui->labelFL5;


    mTypeMap.insert("暴雪",":/res/type/BaoXue.png");
    mTypeMap.insert("暴雨",":/res/type/BaoYu.png");
    mTypeMap.insert("暴雨到大暴雨",":/res/type/BaoYuDaoDaBaoYu.png");
    mTypeMap.insert("大暴雨",":/res/type/DaBaoYu.png");
    mTypeMap.insert("大暴雨到特大暴雨",":/res/type/DaBaoYuDaoTeDaBaoYu.png");
    mTypeMap.insert("大到暴雪",":/res/type/DaBaoYuDaoTeDaBaoYu.png");

    mTypeMap.insert("大雪",":/res/type/DaXue.png");
    mTypeMap.insert("大雨",":/res/type/DaYu.png");
    mTypeMap.insert("冻雨",":/res/type/DongYu.png");
    mTypeMap.insert("多云",":/res/type/DuoYun.png");
    mTypeMap.insert("浮尘",":/res/type/FuChen.png");
    mTypeMap.insert("雷阵雨",":/res/type/LeiZhenYu.png");
    mTypeMap.insert("雷阵雨伴有冰雹",":/res/type/LeiZhenYuBanYouBingBao.png");
    mTypeMap.insert("霾",":/res/type/Mai.png");
    mTypeMap.insert("强沙尘暴",":/res/type/QiangShaChenBao.png");
    mTypeMap.insert("晴",":/res/type/Qing.png");
    mTypeMap.insert("沙尘暴",":/res/type/ShaChenBao.png");
    mTypeMap.insert("特大暴雨",":/res/type/TeDaBaoYu.png");
    mTypeMap.insert("雾",":/res/type/Wu.png");
    mTypeMap.insert("小到中雪",":/res/type/XiaoDaoZhongXue.png");
    mTypeMap.insert("小到中雨",":/res/type/XiaoDaoZhongYu.png");
    mTypeMap.insert("小雪",":/res/type/XiaoXue.png");
    mTypeMap.insert("小雨",":/res/type/XiaoYu.png");
    mTypeMap.insert("雪",":/:/res/type/Xue.png");
    mTypeMap.insert("扬沙",":/res/type/YangSha.png");
    mTypeMap.insert("阴",":/res/type/Yin.png");

    mTypeMap.insert("雨",":/res/type/Yu.png");
    mTypeMap.insert("雨夹雪",":/res/type/YuJiaXue.png");
    mTypeMap.insert("阵雪",":/res/type/ZhenXue.png");
    mTypeMap.insert("阵雨",":/res/type/ZhenYu.png");
    mTypeMap.insert("中到大雪",":/res/type/ZhongDaoDaXue.png");
    mTypeMap.insert("中到大雨",":/res/type/ZhongDaoDaYu.png");
    mTypeMap.insert("中雪",":/res/type/ZhongXue.png");
    mTypeMap.insert("中雨",":/res/type/ZhongYu.png");

    ui->widget0404->installEventFilter(this);
    ui->widget0405->installEventFilter(this);

}
/*QMenu menu;
 QAction *at = actions[0]; // Assumes actions is not empty
 for (QAction *a : qAsConst(actions))
     menu.addAction(a);
 menu.exec(pos, at);*/


Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        //qDebug()<<"right";
        menuQuit->exec(QCursor::pos());//右键退出功能
    }

    if(event->button()==Qt::LeftButton)
    {
       // qDebug()<<event->localPos();
       //qDebug()<< event->globalPos()<<this->pos();
        mOffset=event->globalPos()-this->pos();
    }
}
//鼠标当前位置，event->localPos();
//窗口当前位置，event->globalPos()
//窗口新位置 event->globalPos()- mOffset

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()-mOffset);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->widget0404 &&event->type() ==QEvent::Paint)
    {
        drawTempLineHigh();
        return true;
    }
    if(watched == ui->widget0405 &&event->type() ==QEvent::Paint)
    {
        drawTempLineLow();
        return true;
    }
    return QWidget::eventFilter(watched,event);
}

void Widget::drawTempLineHigh()
{
    QPainter painter(ui->widget0404);
    painter.setPen(QColor(208,107,39));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::yellow);

    int avg,sum=0;
    int offset=0; //偏移值
    int middle=ui->widget0404->height()/2;
    for (int i=0;i<6;i++) {
        sum+=days[i].mTmpHigh.toInt();
    }
    avg=sum/6;

    //定义6个点
    QPoint points[6];
    for (int i=0;i<6;i++) {
        points[i].setX(mAirqList[i]->x()+mAirqList[i]->width()/2);
        offset=(days[i].mTmpHigh.toInt()-avg)*2;
        points[i].setY(middle-offset);

        //画出6个点
        painter.drawEllipse(QPoint(points[i]),3,3);

        //当天温度
        painter.drawText(points[i].x()-10,points[i].y()+13,days[i].mTmpHigh +"°");
    }

    for (int i=0;i<5;i++) {
        painter.drawLine(points[i],points[i+1]);
    }

}

void Widget::drawTempLineLow()
{
    QPainter painter(ui->widget0405);
    painter.setPen(QColor(208,107,39));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(70,192,203));
    painter.setPen(QColor(70,192,203));

    int avg,sum=0;
    int offset=0; //偏移值
    int middle=ui->widget0405->height()/2;
    for (int i=0;i<6;i++) {
        sum+=days[i].mTmpLow.toInt();
    }
    avg=sum/6;

    //定义6个点
    QPoint points[6];
    for (int i=0;i<6;i++) {
        points[i].setX(mAirqList[i]->x()+mAirqList[i]->width()/2);
        offset=(days[i].mTmpLow.toInt()-avg)*2;
        points[i].setY(middle-offset);

        //画出6个点
        painter.drawEllipse(QPoint(points[i]),3,3);

        //当天温度
        painter.drawText(points[i].x()-10,points[i].y()+13,days[i].mTmpLow +"°");
    }

    for (int i=0;i<5;i++) {
        painter.drawLine(points[i],points[i+1]);
    }

}

//解析json
void Widget::parseWeatherJsonData(QByteArray rawData)
{
    QJsonDocument jsonObj=QJsonDocument::fromJson(rawData);
    if(!jsonObj.isNull()&&jsonObj.isObject())
    {
        QJsonObject objRoot=jsonObj.object();
        //解析日期
        QString date=objRoot["date"].toString();
        QString week=objRoot["week"].toString();
        ui->labelCurrentDate->setText(date+" "+week);
        //解析城市名称
        QString cityName=objRoot["city"].toString();
        ui->labelCity->setText(cityName+"市");
        //解析当前温度
        QString currentTemp=objRoot["tem"].toString();
        ui->labelTmp->setText(currentTemp+"℃");
        ui->labelTempRange->setText(objRoot["tem2"].toString()+"~"+objRoot["tem1"].toString());

        //解析天气类型
        ui->labelWeatherType->setText(objRoot["wea"].toString());
        ui->laberWeathericon->setPixmap(mTypeMap[objRoot["wea"].toString()]);

        //感冒指数
        ui->labelGanmao->setText(objRoot["air_tips"].toString());
        //风向
        ui->labelFxType->setText(objRoot["win"].toString());
        //风力
        ui->labelFxType_2->setText(objRoot["win_speed"].toString());
        //pm2.5
        ui->labelPM25Data->setText(objRoot["air_pm25"].toString());
        //湿度
        ui->labelShiduData->setText(objRoot["humidity"].toString());
        //空气质量
        ui->labelairData->setText(objRoot["air_level"].toString());

    }
}
void Widget::parseWeatherJsonDataNew(QByteArray rawData)
{
    QJsonDocument jsonDoc=QJsonDocument::fromJson(rawData);
    if(!jsonDoc.isNull()&&jsonDoc.isObject())
    {
        QJsonObject jsonRoot=jsonDoc.object();
        days[0].mCity=jsonRoot["city"].toString();
        days[0].mPm25=jsonRoot["aqi"].toObject()["pm25"].toString();
        if(jsonRoot.contains("data") && jsonRoot["data"].isArray())
        {
            QJsonArray weaArray=jsonRoot["data"].toArray();
            for (int i=0;i<weaArray.size();++i) {
                QJsonObject obj=weaArray[i].toObject();
                days[i].mDate=obj["date"].toString();
                days[i].mWeek=obj["week"].toString();
                days[i].mWeathType=obj["wea"].toString();
                days[i].mTmp=obj["tem"].toString();
                days[i].mTmpLow=obj["tem2"].toString();
                days[i].mTmpHigh=obj["tem1"].toString();
                days[i].mFx=obj["win"].toArray()[0].toString();
                days[i].mFl=obj["win_speed"].toString();
                days[i].mAirq=obj["air_level"].toString();
                days[i].mTips=obj["air_tips"].toString();
                 days[i].mHu=obj["humidity"].toString();

            }
        }

        updateUI();
    }

}

void Widget:: updateUI()
{

        QPixmap pixmap;
        //解析日期
        ui->labelCurrentDate->setText(days[0].mDate+"  "+days[0].mWeek);
        //解析城市名称
        ui->labelCity->setText(days[0].mCity+"市");
        //解析当前温度
        ui->labelTmp->setText(days[0].mTmp+"℃");
        ui->labelTempRange->setText(days[0].mTmpLow+"~"+days[0].mTmpHigh);

        //解析天气类型
        ui->labelWeatherType->setText(days[0].mWeathType);
        ui->laberWeathericon->setPixmap(mTypeMap[days[0].mWeathType]);

        //感冒指数
        ui->labelGanmao->setText(days[0].mTips);
        //风向
        ui->labelFxType->setText(days[0].mFx);
        //风力
        ui->labelFxType_2->setText(days[0].mFl);
        //pm2.5
        ui->labelPM25Data->setText(days[0].mPm25);
        //湿度
        ui->labelShiduData->setText(days[0].mHu);
        //空气质量
        ui->labelairData->setText(days[0].mAirq);

        for(int i=0;i<6;++i)
        {
            QStringList dayList=days[i].mDate.split("-");

            mDateList[i]->setText(dayList.at(1)+"-"+dayList.at(2)); //2024/10/3
            mWeekList[i]->setText(days[i].mWeek);
            mWeekList[0]->setText("今天");
            mWeekList[1]->setText("明天");
            mWeekList[2]->setText("后天");

            int index=days[i].mWeathType.indexOf("转");
            if(index!=-1){
                 pixmap=mTypeMap[days[i].mWeathType.left(index)];
            }
            else{
                 pixmap=mTypeMap[days[i].mWeathType];
            }

            //缩放图片大小与label匹配
            //pixmap=mTypeMap[days[i].mWeathType];
            pixmap=pixmap.scaled(mIconList[i]->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            mIconList[i]->setMaximumHeight(50);
            mIconList[i]->setMaximumWidth(ui->widget02->width()/6.5);
            mIconList[i]->setPixmap(pixmap);
            mWeaTypeList[i]->setText(days[i].mWeathType);

            QString airQ=days[i].mAirq;
            mAirqList[i]->setText(airQ);
            if(airQ=="优")
            {
                mAirqList[i]->setStyleSheet("background-color: rgb(150,213,32);border-radius:5px;color: rgba(230, 230, 230, 230)");//绿色
            }
            if(airQ=="良")
            {
                mAirqList[i]->setStyleSheet("background-color: rgb(208,107,39);border-radius:5px;color: rgba(230, 230, 230, 230)");
            }
            if(airQ=="轻度")
            {
                mAirqList[i]->setStyleSheet("background-color: rgb(255,199,199);border-radius:5px;color: rgba(230, 230, 230, 230)");
            }
            if(airQ=="中度")
            {
                mAirqList[i]->setStyleSheet("background-color: rgb(255,17,17);border-radius:5px;color: rgba(230, 230, 230, 230)");
            }
            if(airQ=="重度")
            {
                mAirqList[i]->setStyleSheet("background-color: rgb(153,0,0);border-radius:5px;color: rgba(230, 230, 230, 230)");
            }



            mFlList[i]->setText(days[i].mFl);
            index=days[i].mFl.indexOf("转");
            if(index!=-1)
            {
                mFlList[i]->setText(days[i].mFl.left(index));
            }
            else{
                mFlList[i]->setText(days[i].mFl);
            }
            mFxList[i]->setText(days[i].mFx);
        }

        update();


}


void Widget::readHttpReply(QNetworkReply *reply)
{
    int resCode=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<resCode;
    if(reply->error()==QNetworkReply::NoError&&resCode==200)
    {
    QByteArray data= reply->readAll();
    //parseWeatherJsonData(data);
    parseWeatherJsonDataNew(data);
    qDebug()<<"data"<<QString::fromUtf8(data);
    }else
    {
        QMessageBox mes;
        mes.setWindowTitle("错误");
        mes.setText("网络请求失败");
        mes.setStyleSheet("QPushButton{color:red}");
        mes.setStandardButtons(QMessageBox::Ok);
        mes.exec();
        //qDebug()<<"请求失败:"<<reply->errorString();
    }
}



void Widget::on_pushButton_Search_clicked()
{
    QString cityNameFromUser=ui->lineEditCity->text();
   // QString cityCode=getCityCodeFromName(cityNameFromUser);
    QString cityCode=cityCodeUtils.getCityCodeFromName(cityNameFromUser);
    if(cityCode!=nullptr)
    {
        strurl +="&cityid="+cityCode;
        qDebug()<<strurl;
        manager->get(QNetworkRequest(QUrl(strurl)));
    }else{
        qDebug()<<"123";
        QMessageBox mes;
        mes.setWindowTitle("错误");
        mes.setText("请输入正确的城市名称");
        mes.setStyleSheet("QPushButton{color:red}");
        mes.setStandardButtons(QMessageBox::Ok);
        mes.exec();
    }
}


//QString getCityCodeFromName(QString name)
//{
//    QFile file(":/citycode.json");
//    file.open(QIODevice::ReadOnly);
//    QByteArray rawData=file.readAll();
//    file.close();

//    QJsonDocument jsonDoc=QJsonDocument::fromJson(rawData);
//    if(jsonDoc.isArray())
//    {
//        QJsonArray citys=jsonDoc.array();
//        for(QJsonValue value:citys)
//        {
//            if(value.isObject())
//            {
//                QString cityName=value["city_name"].toString();
//                if(cityName==name)
//                {
//                    return value["city_code"].toString();
//                }
//            }
//        }
//        return  " ";
//    }
//}

void Widget::on_lineEditCity_returnPressed()
{
    on_pushButton_Search_clicked();
}
