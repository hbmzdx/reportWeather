#ifndef WIDGET_H
#define WIDGET_H

#include <QMenu>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QLabel>
#include"CityCodeUtils.h"
#include"Day.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Day days[7];
    QList<QLabel *> mDateList;
    QList<QLabel *> mWeekList;
    QList<QLabel *> mIconList;
    QList<QLabel *> mWeaTypeList;
    QList<QLabel *> mAirqList;
    QList<QLabel *> mFxList;
    QList<QLabel *> mFlList;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched,QEvent *event);

public slots:
    void readHttpReply(QNetworkReply *reply);


private slots:
    void on_pushButton_Search_clicked();

    void on_lineEditCity_returnPressed();

private:
    Ui::Widget *ui;
    QMenu *menuQuit;
    QPoint mOffset;
    QNetworkReply *reply;
    QString strurl;
    QNetworkAccessManager *manager;
    void parseWeatherJsonData(QByteArray rawData);
    void parseWeatherJsonDataNew(QByteArray rawData);
    void updateUI();
    void drawTempLineHigh();
    void drawTempLineLow();

    CityCodeUtils cityCodeUtils;

    QMap<QString,QString> mTypeMap;
};
#endif // WIDGET_H
