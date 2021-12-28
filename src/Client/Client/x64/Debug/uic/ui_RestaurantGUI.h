/********************************************************************************
** Form generated from reading UI file 'RestaurantGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTAURANTGUI_H
#define UI_RESTAURANTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RestaurantGUI
{
public:
    QStackedWidget *RestaurantInterface;
    QWidget *OrdersToPrepare;
    QTableWidget *ordersToPrepareList;
    QPushButton *readyToCollectBtn;
    QLabel *readyToCollectLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *ordersToPrepareBtn;
    QPushButton *ordersToCollectBtn;
    QPushButton *ordersHistoryBtn;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *restaurantProfileBtn;
    QPushButton *restaurantMenuBtn;
    QPushButton *restaurantStatsBtn;
    QPushButton *logoutBtn;
    QWidget *OrdersToCollect;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *ordersToPrepareBtn_2;
    QPushButton *ordersToCollectBtn_2;
    QPushButton *ordersHistoryBtn_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *restaurantProfileBtn_2;
    QPushButton *restaurantMenuBtn_2;
    QPushButton *restaurantStatsBtn_2;
    QPushButton *logoutBtn_2;
    QLabel *collectetLabel;
    QPushButton *collectedBtn;
    QTableWidget *ordersToCollectList;
    QWidget *OrdersHistory;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *ordersToPrepareBtn_3;
    QPushButton *ordersToCollectBtn_3;
    QPushButton *ordersHistoryBtn_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *restaurantProfileBtn_3;
    QPushButton *restaurantMenuBtn_3;
    QPushButton *restaurantStatsBtn_3;
    QPushButton *logoutBtn_3;
    QTableWidget *ordersHistoryList;
    QWidget *Profile;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *ordersToPrepareBtn_4;
    QPushButton *ordersToCollectBtn_4;
    QPushButton *ordersHistoryBtn_4;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *restaurantProfileBtn_4;
    QPushButton *restaurantMenuBtn_4;
    QPushButton *restaurantStatsBtn_4;
    QPushButton *logoutBtn_4;
    QLabel *profileLabel;
    QWidget *layoutWidget_6;
    QVBoxLayout *verticalLayout_7;
    QLabel *nameProfileLabel;
    QLineEdit *nameLineEdit;
    QLabel *addressProfileLabel;
    QLineEdit *addressLineEdit;
    QLabel *emailProfileLabel;
    QLineEdit *emailLineEdit;
    QLabel *pswProfileLabel;
    QLineEdit *pswLineEdit;
    QLabel *phoneProfileLabel;
    QLineEdit *phoneLineEdit;
    QWidget *layoutWidget_7;
    QVBoxLayout *verticalLayout_8;
    QLabel *errorProfileLabel;
    QPushButton *updateProfileBtn;
    QWidget *Menu;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *ordersToPrepareBtn_5;
    QPushButton *ordersToCollectBtn_5;
    QPushButton *ordersHistoryBtn_5;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *restaurantProfileBtn_5;
    QPushButton *restaurantMenuBtn_5;
    QPushButton *restaurantStatsBtn_5;
    QPushButton *logoutBtn_5;
    QPushButton *deleteDishBtn;
    QTableWidget *dishesList;
    QWidget *layoutWidget_16;
    QVBoxLayout *verticalLayout_19;
    QLabel *addDishLabel;
    QPushButton *addDishBtn;
    QLabel *createDishLabel;
    QFrame *line_2;
    QWidget *layoutWidget_17;
    QVBoxLayout *verticalLayout_20;
    QLabel *dishNameLabel;
    QLineEdit *dishNameLineEdit;
    QLabel *dishTypeLabel;
    QComboBox *dishTypeBox;
    QLabel *dishPriceLabel;
    QDoubleSpinBox *dishPriceSpinBox;
    QLabel *deleteDishLabel;
    QWidget *Stats;
    QWidget *layoutWidget_5;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *ordersToPrepareBtn_6;
    QPushButton *ordersToCollectBtn_6;
    QPushButton *ordersHistoryBtn_6;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *restaurantProfileBtn_6;
    QPushButton *restaurantMenuBtn_6;
    QPushButton *restaurantStatsBtn_6;
    QPushButton *logoutBtn_6;

    void setupUi(QDialog *RestaurantGUI)
    {
        if (RestaurantGUI->objectName().isEmpty())
            RestaurantGUI->setObjectName(QString::fromUtf8("RestaurantGUI"));
        RestaurantGUI->resize(800, 630);
        RestaurantInterface = new QStackedWidget(RestaurantGUI);
        RestaurantInterface->setObjectName(QString::fromUtf8("RestaurantInterface"));
        RestaurantInterface->setGeometry(QRect(10, 10, 781, 611));
        OrdersToPrepare = new QWidget();
        OrdersToPrepare->setObjectName(QString::fromUtf8("OrdersToPrepare"));
        ordersToPrepareList = new QTableWidget(OrdersToPrepare);
        if (ordersToPrepareList->columnCount() < 4)
            ordersToPrepareList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        ordersToPrepareList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        ordersToPrepareList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        ordersToPrepareList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        ordersToPrepareList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        ordersToPrepareList->setObjectName(QString::fromUtf8("ordersToPrepareList"));
        ordersToPrepareList->setGeometry(QRect(0, 90, 781, 481));
        ordersToPrepareList->horizontalHeader()->setDefaultSectionSize(190);
        readyToCollectBtn = new QPushButton(OrdersToPrepare);
        readyToCollectBtn->setObjectName(QString::fromUtf8("readyToCollectBtn"));
        readyToCollectBtn->setGeometry(QRect(580, 580, 201, 28));
        readyToCollectLabel = new QLabel(OrdersToPrepare);
        readyToCollectLabel->setObjectName(QString::fromUtf8("readyToCollectLabel"));
        readyToCollectLabel->setGeometry(QRect(400, 580, 181, 31));
        layoutWidget = new QWidget(OrdersToPrepare);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 10, 781, 69));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ordersToPrepareBtn = new QPushButton(layoutWidget);
        ordersToPrepareBtn->setObjectName(QString::fromUtf8("ordersToPrepareBtn"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        ordersToPrepareBtn->setFont(font);
        ordersToPrepareBtn->setAutoDefault(false);
        ordersToPrepareBtn->setFlat(true);

        horizontalLayout->addWidget(ordersToPrepareBtn);

        ordersToCollectBtn = new QPushButton(layoutWidget);
        ordersToCollectBtn->setObjectName(QString::fromUtf8("ordersToCollectBtn"));

        horizontalLayout->addWidget(ordersToCollectBtn);

        ordersHistoryBtn = new QPushButton(layoutWidget);
        ordersHistoryBtn->setObjectName(QString::fromUtf8("ordersHistoryBtn"));

        horizontalLayout->addWidget(ordersHistoryBtn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        restaurantProfileBtn = new QPushButton(layoutWidget);
        restaurantProfileBtn->setObjectName(QString::fromUtf8("restaurantProfileBtn"));

        horizontalLayout_2->addWidget(restaurantProfileBtn);

        restaurantMenuBtn = new QPushButton(layoutWidget);
        restaurantMenuBtn->setObjectName(QString::fromUtf8("restaurantMenuBtn"));

        horizontalLayout_2->addWidget(restaurantMenuBtn);

        restaurantStatsBtn = new QPushButton(layoutWidget);
        restaurantStatsBtn->setObjectName(QString::fromUtf8("restaurantStatsBtn"));

        horizontalLayout_2->addWidget(restaurantStatsBtn);

        logoutBtn = new QPushButton(layoutWidget);
        logoutBtn->setObjectName(QString::fromUtf8("logoutBtn"));

        horizontalLayout_2->addWidget(logoutBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        RestaurantInterface->addWidget(OrdersToPrepare);
        OrdersToCollect = new QWidget();
        OrdersToCollect->setObjectName(QString::fromUtf8("OrdersToCollect"));
        layoutWidget1 = new QWidget(OrdersToCollect);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 10, 781, 69));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        ordersToPrepareBtn_2 = new QPushButton(layoutWidget1);
        ordersToPrepareBtn_2->setObjectName(QString::fromUtf8("ordersToPrepareBtn_2"));

        horizontalLayout_3->addWidget(ordersToPrepareBtn_2);

        ordersToCollectBtn_2 = new QPushButton(layoutWidget1);
        ordersToCollectBtn_2->setObjectName(QString::fromUtf8("ordersToCollectBtn_2"));
        ordersToCollectBtn_2->setFont(font);
        ordersToCollectBtn_2->setAutoDefault(false);
        ordersToCollectBtn_2->setFlat(true);

        horizontalLayout_3->addWidget(ordersToCollectBtn_2);

        ordersHistoryBtn_2 = new QPushButton(layoutWidget1);
        ordersHistoryBtn_2->setObjectName(QString::fromUtf8("ordersHistoryBtn_2"));

        horizontalLayout_3->addWidget(ordersHistoryBtn_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        restaurantProfileBtn_2 = new QPushButton(layoutWidget1);
        restaurantProfileBtn_2->setObjectName(QString::fromUtf8("restaurantProfileBtn_2"));

        horizontalLayout_4->addWidget(restaurantProfileBtn_2);

        restaurantMenuBtn_2 = new QPushButton(layoutWidget1);
        restaurantMenuBtn_2->setObjectName(QString::fromUtf8("restaurantMenuBtn_2"));

        horizontalLayout_4->addWidget(restaurantMenuBtn_2);

        restaurantStatsBtn_2 = new QPushButton(layoutWidget1);
        restaurantStatsBtn_2->setObjectName(QString::fromUtf8("restaurantStatsBtn_2"));

        horizontalLayout_4->addWidget(restaurantStatsBtn_2);

        logoutBtn_2 = new QPushButton(layoutWidget1);
        logoutBtn_2->setObjectName(QString::fromUtf8("logoutBtn_2"));

        horizontalLayout_4->addWidget(logoutBtn_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        collectetLabel = new QLabel(OrdersToCollect);
        collectetLabel->setObjectName(QString::fromUtf8("collectetLabel"));
        collectetLabel->setGeometry(QRect(400, 580, 181, 31));
        collectedBtn = new QPushButton(OrdersToCollect);
        collectedBtn->setObjectName(QString::fromUtf8("collectedBtn"));
        collectedBtn->setGeometry(QRect(580, 580, 201, 28));
        ordersToCollectList = new QTableWidget(OrdersToCollect);
        if (ordersToCollectList->columnCount() < 4)
            ordersToCollectList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        ordersToCollectList->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        ordersToCollectList->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        ordersToCollectList->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        ordersToCollectList->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        ordersToCollectList->setObjectName(QString::fromUtf8("ordersToCollectList"));
        ordersToCollectList->setGeometry(QRect(0, 90, 781, 481));
        ordersToCollectList->horizontalHeader()->setDefaultSectionSize(190);
        RestaurantInterface->addWidget(OrdersToCollect);
        OrdersHistory = new QWidget();
        OrdersHistory->setObjectName(QString::fromUtf8("OrdersHistory"));
        layoutWidget_2 = new QWidget(OrdersHistory);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 10, 781, 69));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        ordersToPrepareBtn_3 = new QPushButton(layoutWidget_2);
        ordersToPrepareBtn_3->setObjectName(QString::fromUtf8("ordersToPrepareBtn_3"));

        horizontalLayout_5->addWidget(ordersToPrepareBtn_3);

        ordersToCollectBtn_3 = new QPushButton(layoutWidget_2);
        ordersToCollectBtn_3->setObjectName(QString::fromUtf8("ordersToCollectBtn_3"));

        horizontalLayout_5->addWidget(ordersToCollectBtn_3);

        ordersHistoryBtn_3 = new QPushButton(layoutWidget_2);
        ordersHistoryBtn_3->setObjectName(QString::fromUtf8("ordersHistoryBtn_3"));
        ordersHistoryBtn_3->setFont(font);
        ordersHistoryBtn_3->setAutoDefault(false);
        ordersHistoryBtn_3->setFlat(true);

        horizontalLayout_5->addWidget(ordersHistoryBtn_3);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        restaurantProfileBtn_3 = new QPushButton(layoutWidget_2);
        restaurantProfileBtn_3->setObjectName(QString::fromUtf8("restaurantProfileBtn_3"));

        horizontalLayout_6->addWidget(restaurantProfileBtn_3);

        restaurantMenuBtn_3 = new QPushButton(layoutWidget_2);
        restaurantMenuBtn_3->setObjectName(QString::fromUtf8("restaurantMenuBtn_3"));

        horizontalLayout_6->addWidget(restaurantMenuBtn_3);

        restaurantStatsBtn_3 = new QPushButton(layoutWidget_2);
        restaurantStatsBtn_3->setObjectName(QString::fromUtf8("restaurantStatsBtn_3"));

        horizontalLayout_6->addWidget(restaurantStatsBtn_3);

        logoutBtn_3 = new QPushButton(layoutWidget_2);
        logoutBtn_3->setObjectName(QString::fromUtf8("logoutBtn_3"));

        horizontalLayout_6->addWidget(logoutBtn_3);


        verticalLayout_3->addLayout(horizontalLayout_6);

        ordersHistoryList = new QTableWidget(OrdersHistory);
        if (ordersHistoryList->columnCount() < 4)
            ordersHistoryList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        ordersHistoryList->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        ordersHistoryList->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        ordersHistoryList->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        ordersHistoryList->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        ordersHistoryList->setObjectName(QString::fromUtf8("ordersHistoryList"));
        ordersHistoryList->setGeometry(QRect(0, 90, 781, 521));
        ordersHistoryList->horizontalHeader()->setDefaultSectionSize(190);
        RestaurantInterface->addWidget(OrdersHistory);
        Profile = new QWidget();
        Profile->setObjectName(QString::fromUtf8("Profile"));
        layoutWidget_3 = new QWidget(Profile);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(0, 10, 781, 69));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        ordersToPrepareBtn_4 = new QPushButton(layoutWidget_3);
        ordersToPrepareBtn_4->setObjectName(QString::fromUtf8("ordersToPrepareBtn_4"));

        horizontalLayout_7->addWidget(ordersToPrepareBtn_4);

        ordersToCollectBtn_4 = new QPushButton(layoutWidget_3);
        ordersToCollectBtn_4->setObjectName(QString::fromUtf8("ordersToCollectBtn_4"));

        horizontalLayout_7->addWidget(ordersToCollectBtn_4);

        ordersHistoryBtn_4 = new QPushButton(layoutWidget_3);
        ordersHistoryBtn_4->setObjectName(QString::fromUtf8("ordersHistoryBtn_4"));

        horizontalLayout_7->addWidget(ordersHistoryBtn_4);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        restaurantProfileBtn_4 = new QPushButton(layoutWidget_3);
        restaurantProfileBtn_4->setObjectName(QString::fromUtf8("restaurantProfileBtn_4"));
        restaurantProfileBtn_4->setFont(font);
        restaurantProfileBtn_4->setAutoDefault(false);
        restaurantProfileBtn_4->setFlat(true);

        horizontalLayout_8->addWidget(restaurantProfileBtn_4);

        restaurantMenuBtn_4 = new QPushButton(layoutWidget_3);
        restaurantMenuBtn_4->setObjectName(QString::fromUtf8("restaurantMenuBtn_4"));

        horizontalLayout_8->addWidget(restaurantMenuBtn_4);

        restaurantStatsBtn_4 = new QPushButton(layoutWidget_3);
        restaurantStatsBtn_4->setObjectName(QString::fromUtf8("restaurantStatsBtn_4"));

        horizontalLayout_8->addWidget(restaurantStatsBtn_4);

        logoutBtn_4 = new QPushButton(layoutWidget_3);
        logoutBtn_4->setObjectName(QString::fromUtf8("logoutBtn_4"));

        horizontalLayout_8->addWidget(logoutBtn_4);


        verticalLayout_4->addLayout(horizontalLayout_8);

        profileLabel = new QLabel(Profile);
        profileLabel->setObjectName(QString::fromUtf8("profileLabel"));
        profileLabel->setGeometry(QRect(300, 90, 181, 41));
        QFont font1;
        font1.setPointSize(20);
        profileLabel->setFont(font1);
        layoutWidget_6 = new QWidget(Profile);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(260, 140, 241, 319));
        verticalLayout_7 = new QVBoxLayout(layoutWidget_6);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        nameProfileLabel = new QLabel(layoutWidget_6);
        nameProfileLabel->setObjectName(QString::fromUtf8("nameProfileLabel"));

        verticalLayout_7->addWidget(nameProfileLabel);

        nameLineEdit = new QLineEdit(layoutWidget_6);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        verticalLayout_7->addWidget(nameLineEdit);

        addressProfileLabel = new QLabel(layoutWidget_6);
        addressProfileLabel->setObjectName(QString::fromUtf8("addressProfileLabel"));

        verticalLayout_7->addWidget(addressProfileLabel);

        addressLineEdit = new QLineEdit(layoutWidget_6);
        addressLineEdit->setObjectName(QString::fromUtf8("addressLineEdit"));

        verticalLayout_7->addWidget(addressLineEdit);

        emailProfileLabel = new QLabel(layoutWidget_6);
        emailProfileLabel->setObjectName(QString::fromUtf8("emailProfileLabel"));

        verticalLayout_7->addWidget(emailProfileLabel);

        emailLineEdit = new QLineEdit(layoutWidget_6);
        emailLineEdit->setObjectName(QString::fromUtf8("emailLineEdit"));
        emailLineEdit->setEnabled(true);

        verticalLayout_7->addWidget(emailLineEdit);

        pswProfileLabel = new QLabel(layoutWidget_6);
        pswProfileLabel->setObjectName(QString::fromUtf8("pswProfileLabel"));

        verticalLayout_7->addWidget(pswProfileLabel);

        pswLineEdit = new QLineEdit(layoutWidget_6);
        pswLineEdit->setObjectName(QString::fromUtf8("pswLineEdit"));
        pswLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_7->addWidget(pswLineEdit);

        phoneProfileLabel = new QLabel(layoutWidget_6);
        phoneProfileLabel->setObjectName(QString::fromUtf8("phoneProfileLabel"));

        verticalLayout_7->addWidget(phoneProfileLabel);

        phoneLineEdit = new QLineEdit(layoutWidget_6);
        phoneLineEdit->setObjectName(QString::fromUtf8("phoneLineEdit"));

        verticalLayout_7->addWidget(phoneLineEdit);

        layoutWidget_7 = new QWidget(Profile);
        layoutWidget_7->setObjectName(QString::fromUtf8("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(180, 480, 391, 53));
        verticalLayout_8 = new QVBoxLayout(layoutWidget_7);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        errorProfileLabel = new QLabel(layoutWidget_7);
        errorProfileLabel->setObjectName(QString::fromUtf8("errorProfileLabel"));

        verticalLayout_8->addWidget(errorProfileLabel);

        updateProfileBtn = new QPushButton(layoutWidget_7);
        updateProfileBtn->setObjectName(QString::fromUtf8("updateProfileBtn"));

        verticalLayout_8->addWidget(updateProfileBtn);

        RestaurantInterface->addWidget(Profile);
        Menu = new QWidget();
        Menu->setObjectName(QString::fromUtf8("Menu"));
        layoutWidget_4 = new QWidget(Menu);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(0, 10, 781, 69));
        verticalLayout_5 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        ordersToPrepareBtn_5 = new QPushButton(layoutWidget_4);
        ordersToPrepareBtn_5->setObjectName(QString::fromUtf8("ordersToPrepareBtn_5"));

        horizontalLayout_9->addWidget(ordersToPrepareBtn_5);

        ordersToCollectBtn_5 = new QPushButton(layoutWidget_4);
        ordersToCollectBtn_5->setObjectName(QString::fromUtf8("ordersToCollectBtn_5"));

        horizontalLayout_9->addWidget(ordersToCollectBtn_5);

        ordersHistoryBtn_5 = new QPushButton(layoutWidget_4);
        ordersHistoryBtn_5->setObjectName(QString::fromUtf8("ordersHistoryBtn_5"));

        horizontalLayout_9->addWidget(ordersHistoryBtn_5);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        restaurantProfileBtn_5 = new QPushButton(layoutWidget_4);
        restaurantProfileBtn_5->setObjectName(QString::fromUtf8("restaurantProfileBtn_5"));

        horizontalLayout_10->addWidget(restaurantProfileBtn_5);

        restaurantMenuBtn_5 = new QPushButton(layoutWidget_4);
        restaurantMenuBtn_5->setObjectName(QString::fromUtf8("restaurantMenuBtn_5"));
        restaurantMenuBtn_5->setFont(font);
        restaurantMenuBtn_5->setAutoDefault(false);
        restaurantMenuBtn_5->setFlat(true);

        horizontalLayout_10->addWidget(restaurantMenuBtn_5);

        restaurantStatsBtn_5 = new QPushButton(layoutWidget_4);
        restaurantStatsBtn_5->setObjectName(QString::fromUtf8("restaurantStatsBtn_5"));

        horizontalLayout_10->addWidget(restaurantStatsBtn_5);

        logoutBtn_5 = new QPushButton(layoutWidget_4);
        logoutBtn_5->setObjectName(QString::fromUtf8("logoutBtn_5"));

        horizontalLayout_10->addWidget(logoutBtn_5);


        verticalLayout_5->addLayout(horizontalLayout_10);

        deleteDishBtn = new QPushButton(Menu);
        deleteDishBtn->setObjectName(QString::fromUtf8("deleteDishBtn"));
        deleteDishBtn->setGeometry(QRect(390, 570, 391, 28));
        dishesList = new QTableWidget(Menu);
        if (dishesList->columnCount() < 4)
            dishesList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        dishesList->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        dishesList->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        dishesList->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        dishesList->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        dishesList->setObjectName(QString::fromUtf8("dishesList"));
        dishesList->setGeometry(QRect(390, 80, 391, 461));
        layoutWidget_16 = new QWidget(Menu);
        layoutWidget_16->setObjectName(QString::fromUtf8("layoutWidget_16"));
        layoutWidget_16->setGeometry(QRect(10, 470, 371, 53));
        verticalLayout_19 = new QVBoxLayout(layoutWidget_16);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        addDishLabel = new QLabel(layoutWidget_16);
        addDishLabel->setObjectName(QString::fromUtf8("addDishLabel"));

        verticalLayout_19->addWidget(addDishLabel);

        addDishBtn = new QPushButton(layoutWidget_16);
        addDishBtn->setObjectName(QString::fromUtf8("addDishBtn"));

        verticalLayout_19->addWidget(addDishBtn);

        createDishLabel = new QLabel(Menu);
        createDishLabel->setObjectName(QString::fromUtf8("createDishLabel"));
        createDishLabel->setGeometry(QRect(20, 110, 361, 31));
        createDishLabel->setFont(font1);
        line_2 = new QFrame(Menu);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(380, 80, 20, 541));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        layoutWidget_17 = new QWidget(Menu);
        layoutWidget_17->setObjectName(QString::fromUtf8("layoutWidget_17"));
        layoutWidget_17->setGeometry(QRect(10, 160, 201, 291));
        verticalLayout_20 = new QVBoxLayout(layoutWidget_17);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        dishNameLabel = new QLabel(layoutWidget_17);
        dishNameLabel->setObjectName(QString::fromUtf8("dishNameLabel"));

        verticalLayout_20->addWidget(dishNameLabel);

        dishNameLineEdit = new QLineEdit(layoutWidget_17);
        dishNameLineEdit->setObjectName(QString::fromUtf8("dishNameLineEdit"));

        verticalLayout_20->addWidget(dishNameLineEdit);

        dishTypeLabel = new QLabel(layoutWidget_17);
        dishTypeLabel->setObjectName(QString::fromUtf8("dishTypeLabel"));

        verticalLayout_20->addWidget(dishTypeLabel);

        dishTypeBox = new QComboBox(layoutWidget_17);
        dishTypeBox->addItem(QString());
        dishTypeBox->addItem(QString());
        dishTypeBox->addItem(QString());
        dishTypeBox->addItem(QString());
        dishTypeBox->addItem(QString());
        dishTypeBox->setObjectName(QString::fromUtf8("dishTypeBox"));
        dishTypeBox->setFrame(true);

        verticalLayout_20->addWidget(dishTypeBox);

        dishPriceLabel = new QLabel(layoutWidget_17);
        dishPriceLabel->setObjectName(QString::fromUtf8("dishPriceLabel"));

        verticalLayout_20->addWidget(dishPriceLabel);

        dishPriceSpinBox = new QDoubleSpinBox(layoutWidget_17);
        dishPriceSpinBox->setObjectName(QString::fromUtf8("dishPriceSpinBox"));
        dishPriceSpinBox->setSingleStep(0.500000000000000);

        verticalLayout_20->addWidget(dishPriceSpinBox);

        deleteDishLabel = new QLabel(Menu);
        deleteDishLabel->setObjectName(QString::fromUtf8("deleteDishLabel"));
        deleteDishLabel->setGeometry(QRect(400, 550, 371, 20));
        RestaurantInterface->addWidget(Menu);
        Stats = new QWidget();
        Stats->setObjectName(QString::fromUtf8("Stats"));
        layoutWidget_5 = new QWidget(Stats);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(0, 10, 781, 69));
        verticalLayout_6 = new QVBoxLayout(layoutWidget_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        ordersToPrepareBtn_6 = new QPushButton(layoutWidget_5);
        ordersToPrepareBtn_6->setObjectName(QString::fromUtf8("ordersToPrepareBtn_6"));

        horizontalLayout_11->addWidget(ordersToPrepareBtn_6);

        ordersToCollectBtn_6 = new QPushButton(layoutWidget_5);
        ordersToCollectBtn_6->setObjectName(QString::fromUtf8("ordersToCollectBtn_6"));

        horizontalLayout_11->addWidget(ordersToCollectBtn_6);

        ordersHistoryBtn_6 = new QPushButton(layoutWidget_5);
        ordersHistoryBtn_6->setObjectName(QString::fromUtf8("ordersHistoryBtn_6"));

        horizontalLayout_11->addWidget(ordersHistoryBtn_6);


        verticalLayout_6->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        restaurantProfileBtn_6 = new QPushButton(layoutWidget_5);
        restaurantProfileBtn_6->setObjectName(QString::fromUtf8("restaurantProfileBtn_6"));

        horizontalLayout_12->addWidget(restaurantProfileBtn_6);

        restaurantMenuBtn_6 = new QPushButton(layoutWidget_5);
        restaurantMenuBtn_6->setObjectName(QString::fromUtf8("restaurantMenuBtn_6"));

        horizontalLayout_12->addWidget(restaurantMenuBtn_6);

        restaurantStatsBtn_6 = new QPushButton(layoutWidget_5);
        restaurantStatsBtn_6->setObjectName(QString::fromUtf8("restaurantStatsBtn_6"));
        restaurantStatsBtn_6->setFont(font);
        restaurantStatsBtn_6->setAutoDefault(false);
        restaurantStatsBtn_6->setFlat(true);

        horizontalLayout_12->addWidget(restaurantStatsBtn_6);

        logoutBtn_6 = new QPushButton(layoutWidget_5);
        logoutBtn_6->setObjectName(QString::fromUtf8("logoutBtn_6"));

        horizontalLayout_12->addWidget(logoutBtn_6);


        verticalLayout_6->addLayout(horizontalLayout_12);

        RestaurantInterface->addWidget(Stats);

        retranslateUi(RestaurantGUI);

        ordersToPrepareBtn->setDefault(true);
        ordersToCollectBtn_2->setDefault(true);
        ordersHistoryBtn_3->setDefault(true);
        restaurantProfileBtn_4->setDefault(true);
        restaurantMenuBtn_5->setDefault(true);
        restaurantStatsBtn_6->setDefault(true);


        QMetaObject::connectSlotsByName(RestaurantGUI);
    } // setupUi

    void retranslateUi(QDialog *RestaurantGUI)
    {
        RestaurantGUI->setWindowTitle(QCoreApplication::translate("RestaurantGUI", "RestaurantGUI", nullptr));
        QTableWidgetItem *___qtablewidgetitem = ordersToPrepareList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RestaurantGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = ordersToPrepareList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RestaurantGUI", "User", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = ordersToPrepareList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RestaurantGUI", "Total", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = ordersToPrepareList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("RestaurantGUI", "Status", nullptr));
        readyToCollectBtn->setText(QCoreApplication::translate("RestaurantGUI", "Ready to collect", nullptr));
        readyToCollectLabel->setText(QString());
        ordersToPrepareBtn->setText(QCoreApplication::translate("RestaurantGUI", "Orders to prepare", nullptr));
        ordersToCollectBtn->setText(QCoreApplication::translate("RestaurantGUI", "Orders to collect", nullptr));
        ordersHistoryBtn->setText(QCoreApplication::translate("RestaurantGUI", "Orders history", nullptr));
        restaurantProfileBtn->setText(QCoreApplication::translate("RestaurantGUI", "Profile", nullptr));
        restaurantMenuBtn->setText(QCoreApplication::translate("RestaurantGUI", "Restaurant Menu", nullptr));
        restaurantStatsBtn->setText(QCoreApplication::translate("RestaurantGUI", "Stats", nullptr));
        logoutBtn->setText(QCoreApplication::translate("RestaurantGUI", "Logout", nullptr));
        ordersToPrepareBtn_2->setText(QCoreApplication::translate("RestaurantGUI", "Orders to prepare", nullptr));
        ordersToCollectBtn_2->setText(QCoreApplication::translate("RestaurantGUI", "Orders to collect", nullptr));
        ordersHistoryBtn_2->setText(QCoreApplication::translate("RestaurantGUI", "Orders history", nullptr));
        restaurantProfileBtn_2->setText(QCoreApplication::translate("RestaurantGUI", "Profile", nullptr));
        restaurantMenuBtn_2->setText(QCoreApplication::translate("RestaurantGUI", "Restaurant Menu", nullptr));
        restaurantStatsBtn_2->setText(QCoreApplication::translate("RestaurantGUI", "Stats", nullptr));
        logoutBtn_2->setText(QCoreApplication::translate("RestaurantGUI", "Logout", nullptr));
        collectetLabel->setText(QString());
        collectedBtn->setText(QCoreApplication::translate("RestaurantGUI", "Order collected", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = ordersToCollectList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("RestaurantGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = ordersToCollectList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("RestaurantGUI", "User", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = ordersToCollectList->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("RestaurantGUI", "Total", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = ordersToCollectList->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("RestaurantGUI", "Status", nullptr));
        ordersToPrepareBtn_3->setText(QCoreApplication::translate("RestaurantGUI", "Orders to prepare", nullptr));
        ordersToCollectBtn_3->setText(QCoreApplication::translate("RestaurantGUI", "Orders to collect", nullptr));
        ordersHistoryBtn_3->setText(QCoreApplication::translate("RestaurantGUI", "Orders history", nullptr));
        restaurantProfileBtn_3->setText(QCoreApplication::translate("RestaurantGUI", "Profile", nullptr));
        restaurantMenuBtn_3->setText(QCoreApplication::translate("RestaurantGUI", "Restaurant Menu", nullptr));
        restaurantStatsBtn_3->setText(QCoreApplication::translate("RestaurantGUI", "Stats", nullptr));
        logoutBtn_3->setText(QCoreApplication::translate("RestaurantGUI", "Logout", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = ordersHistoryList->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("RestaurantGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = ordersHistoryList->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("RestaurantGUI", "User", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = ordersHistoryList->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("RestaurantGUI", "Total", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = ordersHistoryList->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("RestaurantGUI", "Status", nullptr));
        ordersToPrepareBtn_4->setText(QCoreApplication::translate("RestaurantGUI", "Orders to prepare", nullptr));
        ordersToCollectBtn_4->setText(QCoreApplication::translate("RestaurantGUI", "Orders to collect", nullptr));
        ordersHistoryBtn_4->setText(QCoreApplication::translate("RestaurantGUI", "Orders history", nullptr));
        restaurantProfileBtn_4->setText(QCoreApplication::translate("RestaurantGUI", "Profile", nullptr));
        restaurantMenuBtn_4->setText(QCoreApplication::translate("RestaurantGUI", "Restaurant Menu", nullptr));
        restaurantStatsBtn_4->setText(QCoreApplication::translate("RestaurantGUI", "Stats", nullptr));
        logoutBtn_4->setText(QCoreApplication::translate("RestaurantGUI", "Logout", nullptr));
        profileLabel->setText(QCoreApplication::translate("RestaurantGUI", "Your Profile", nullptr));
        nameProfileLabel->setText(QCoreApplication::translate("RestaurantGUI", "Name", nullptr));
        addressProfileLabel->setText(QCoreApplication::translate("RestaurantGUI", "Address", nullptr));
        emailProfileLabel->setText(QCoreApplication::translate("RestaurantGUI", "Email", nullptr));
        pswProfileLabel->setText(QCoreApplication::translate("RestaurantGUI", "Password", nullptr));
        pswLineEdit->setInputMask(QString());
        pswLineEdit->setText(QString());
        phoneProfileLabel->setText(QCoreApplication::translate("RestaurantGUI", "Phone number", nullptr));
        errorProfileLabel->setText(QString());
        updateProfileBtn->setText(QCoreApplication::translate("RestaurantGUI", "Update data", nullptr));
        ordersToPrepareBtn_5->setText(QCoreApplication::translate("RestaurantGUI", "Orders to prepare", nullptr));
        ordersToCollectBtn_5->setText(QCoreApplication::translate("RestaurantGUI", "Orders to collect", nullptr));
        ordersHistoryBtn_5->setText(QCoreApplication::translate("RestaurantGUI", "Orders history", nullptr));
        restaurantProfileBtn_5->setText(QCoreApplication::translate("RestaurantGUI", "Profile", nullptr));
        restaurantMenuBtn_5->setText(QCoreApplication::translate("RestaurantGUI", "Restaurant Menu", nullptr));
        restaurantStatsBtn_5->setText(QCoreApplication::translate("RestaurantGUI", "Stats", nullptr));
        logoutBtn_5->setText(QCoreApplication::translate("RestaurantGUI", "Logout", nullptr));
        deleteDishBtn->setText(QCoreApplication::translate("RestaurantGUI", "Delete selected dish", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = dishesList->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("RestaurantGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = dishesList->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("RestaurantGUI", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = dishesList->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("RestaurantGUI", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = dishesList->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("RestaurantGUI", "Price", nullptr));
        addDishLabel->setText(QString());
        addDishBtn->setText(QCoreApplication::translate("RestaurantGUI", "Add dish to menu", nullptr));
        createDishLabel->setText(QCoreApplication::translate("RestaurantGUI", "Create a new dish", nullptr));
        dishNameLabel->setText(QCoreApplication::translate("RestaurantGUI", "Name", nullptr));
        dishTypeLabel->setText(QCoreApplication::translate("RestaurantGUI", "Type", nullptr));
        dishTypeBox->setItemText(0, QCoreApplication::translate("RestaurantGUI", "Appetizer", nullptr));
        dishTypeBox->setItemText(1, QCoreApplication::translate("RestaurantGUI", "First Course", nullptr));
        dishTypeBox->setItemText(2, QCoreApplication::translate("RestaurantGUI", "Second Course", nullptr));
        dishTypeBox->setItemText(3, QCoreApplication::translate("RestaurantGUI", "Dessert", nullptr));
        dishTypeBox->setItemText(4, QCoreApplication::translate("RestaurantGUI", "Drink", nullptr));

        dishPriceLabel->setText(QCoreApplication::translate("RestaurantGUI", "Price", nullptr));
        deleteDishLabel->setText(QString());
        ordersToPrepareBtn_6->setText(QCoreApplication::translate("RestaurantGUI", "Orders to prepare", nullptr));
        ordersToCollectBtn_6->setText(QCoreApplication::translate("RestaurantGUI", "Orders to collect", nullptr));
        ordersHistoryBtn_6->setText(QCoreApplication::translate("RestaurantGUI", "Orders history", nullptr));
        restaurantProfileBtn_6->setText(QCoreApplication::translate("RestaurantGUI", "Profile", nullptr));
        restaurantMenuBtn_6->setText(QCoreApplication::translate("RestaurantGUI", "Restaurant Menu", nullptr));
        restaurantStatsBtn_6->setText(QCoreApplication::translate("RestaurantGUI", "Stats", nullptr));
        logoutBtn_6->setText(QCoreApplication::translate("RestaurantGUI", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantGUI: public Ui_RestaurantGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTGUI_H
