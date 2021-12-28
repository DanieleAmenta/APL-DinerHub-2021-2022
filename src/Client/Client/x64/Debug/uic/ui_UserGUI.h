/********************************************************************************
** Form generated from reading UI file 'UserGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERGUI_H
#define UI_USERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserGUI
{
public:
    QStackedWidget *UserInterface;
    QWidget *Order;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *restaurantList;
    QTableWidget *dishList;
    QLabel *errorsLabel;
    QPushButton *submitOrderBtn;
    QSplitter *splitter;
    QPushButton *orderTab;
    QPushButton *summaryTab;
    QPushButton *profileTab;
    QPushButton *statsTab;
    QPushButton *logoutTab;
    QWidget *OrdersSummary;
    QSplitter *splitter_2;
    QPushButton *orderTab_2;
    QPushButton *summaryTab_2;
    QPushButton *profileTab_2;
    QPushButton *statsTab_2;
    QPushButton *logoutTab_2;
    QTableWidget *orderList;
    QWidget *Profile;
    QSplitter *splitter_3;
    QPushButton *orderTab_3;
    QPushButton *summaryTab_3;
    QPushButton *profileTab_3;
    QPushButton *statsTab_3;
    QPushButton *logoutTab_3;
    QFrame *line;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *balanceCount;
    QDoubleSpinBox *balanceSpinBox;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *errorProfileBalanceLabel;
    QPushButton *updateBalanceBtn;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *nameProfileLabel;
    QLineEdit *nameLineEdit;
    QLabel *surnameProfileLabel;
    QLineEdit *surnameLineEdit;
    QLabel *emailProfileLabel;
    QLineEdit *emailLineEdit;
    QLabel *pswProfileLabel;
    QLineEdit *pswLineEdit;
    QLabel *phoneProfileLabel;
    QLineEdit *phoneLineEdit;
    QLabel *dateProfileLabel;
    QLineEdit *dateLineEdit;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_4;
    QLabel *errorProfileLabel;
    QPushButton *updateProfileBtn;
    QWidget *Stats;
    QSplitter *splitter_4;
    QPushButton *orderTab_4;
    QPushButton *summaryTab_4;
    QPushButton *profileTab_4;
    QPushButton *statsTab_4;
    QPushButton *logoutTab_4;

    void setupUi(QDialog *UserGUI)
    {
        if (UserGUI->objectName().isEmpty())
            UserGUI->setObjectName(QString::fromUtf8("UserGUI"));
        UserGUI->resize(800, 630);
        UserGUI->setFocusPolicy(Qt::StrongFocus);
        UserInterface = new QStackedWidget(UserGUI);
        UserInterface->setObjectName(QString::fromUtf8("UserInterface"));
        UserInterface->setGeometry(QRect(10, 10, 781, 611));
        Order = new QWidget();
        Order->setObjectName(QString::fromUtf8("Order"));
        layoutWidget = new QWidget(Order);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 50, 781, 551));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        restaurantList = new QTableWidget(layoutWidget);
        if (restaurantList->columnCount() < 5)
            restaurantList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        restaurantList->setObjectName(QString::fromUtf8("restaurantList"));
        restaurantList->setEnabled(true);
        restaurantList->setLineWidth(1);
        restaurantList->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        restaurantList->setShowGrid(true);

        verticalLayout->addWidget(restaurantList);

        dishList = new QTableWidget(layoutWidget);
        if (dishList->columnCount() < 5)
            dishList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        dishList->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        dishList->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        dishList->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        dishList->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        dishList->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        dishList->setObjectName(QString::fromUtf8("dishList"));

        verticalLayout->addWidget(dishList);

        errorsLabel = new QLabel(layoutWidget);
        errorsLabel->setObjectName(QString::fromUtf8("errorsLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        errorsLabel->setFont(font);

        verticalLayout->addWidget(errorsLabel);

        submitOrderBtn = new QPushButton(layoutWidget);
        submitOrderBtn->setObjectName(QString::fromUtf8("submitOrderBtn"));

        verticalLayout->addWidget(submitOrderBtn);

        splitter = new QSplitter(Order);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(0, 10, 781, 28));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Plain);
        splitter->setOrientation(Qt::Horizontal);
        orderTab = new QPushButton(splitter);
        orderTab->setObjectName(QString::fromUtf8("orderTab"));
        orderTab->setEnabled(true);
        QFont font1;
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        orderTab->setFont(font1);
        orderTab->setFocusPolicy(Qt::ClickFocus);
        orderTab->setAutoFillBackground(false);
        orderTab->setCheckable(false);
        orderTab->setChecked(false);
        orderTab->setAutoDefault(false);
        orderTab->setFlat(true);
        splitter->addWidget(orderTab);
        summaryTab = new QPushButton(splitter);
        summaryTab->setObjectName(QString::fromUtf8("summaryTab"));
        splitter->addWidget(summaryTab);
        profileTab = new QPushButton(splitter);
        profileTab->setObjectName(QString::fromUtf8("profileTab"));
        splitter->addWidget(profileTab);
        statsTab = new QPushButton(splitter);
        statsTab->setObjectName(QString::fromUtf8("statsTab"));
        splitter->addWidget(statsTab);
        logoutTab = new QPushButton(splitter);
        logoutTab->setObjectName(QString::fromUtf8("logoutTab"));
        splitter->addWidget(logoutTab);
        UserInterface->addWidget(Order);
        OrdersSummary = new QWidget();
        OrdersSummary->setObjectName(QString::fromUtf8("OrdersSummary"));
        splitter_2 = new QSplitter(OrdersSummary);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(0, 10, 781, 28));
        splitter_2->setOrientation(Qt::Horizontal);
        orderTab_2 = new QPushButton(splitter_2);
        orderTab_2->setObjectName(QString::fromUtf8("orderTab_2"));
        QFont font2;
        font2.setUnderline(false);
        font2.setStrikeOut(false);
        orderTab_2->setFont(font2);
        orderTab_2->setFocusPolicy(Qt::StrongFocus);
        orderTab_2->setCheckable(false);
        orderTab_2->setChecked(false);
        splitter_2->addWidget(orderTab_2);
        summaryTab_2 = new QPushButton(splitter_2);
        summaryTab_2->setObjectName(QString::fromUtf8("summaryTab_2"));
        summaryTab_2->setFont(font);
        summaryTab_2->setCheckable(false);
        summaryTab_2->setChecked(false);
        summaryTab_2->setAutoDefault(false);
        summaryTab_2->setFlat(true);
        splitter_2->addWidget(summaryTab_2);
        profileTab_2 = new QPushButton(splitter_2);
        profileTab_2->setObjectName(QString::fromUtf8("profileTab_2"));
        splitter_2->addWidget(profileTab_2);
        statsTab_2 = new QPushButton(splitter_2);
        statsTab_2->setObjectName(QString::fromUtf8("statsTab_2"));
        splitter_2->addWidget(statsTab_2);
        logoutTab_2 = new QPushButton(splitter_2);
        logoutTab_2->setObjectName(QString::fromUtf8("logoutTab_2"));
        splitter_2->addWidget(logoutTab_2);
        orderList = new QTableWidget(OrdersSummary);
        if (orderList->columnCount() < 4)
            orderList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        orderList->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        orderList->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        orderList->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        orderList->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        orderList->setObjectName(QString::fromUtf8("orderList"));
        orderList->setGeometry(QRect(0, 50, 781, 551));
        orderList->setFrameShadow(QFrame::Sunken);
        orderList->setLineWidth(1);
        orderList->setMidLineWidth(-2);
        orderList->horizontalHeader()->setDefaultSectionSize(180);
        orderList->verticalHeader()->setMinimumSectionSize(30);
        orderList->verticalHeader()->setDefaultSectionSize(37);
        UserInterface->addWidget(OrdersSummary);
        Profile = new QWidget();
        Profile->setObjectName(QString::fromUtf8("Profile"));
        splitter_3 = new QSplitter(Profile);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(0, 10, 781, 28));
        splitter_3->setOrientation(Qt::Horizontal);
        orderTab_3 = new QPushButton(splitter_3);
        orderTab_3->setObjectName(QString::fromUtf8("orderTab_3"));
        orderTab_3->setFont(font2);
        orderTab_3->setFocusPolicy(Qt::StrongFocus);
        orderTab_3->setCheckable(false);
        orderTab_3->setChecked(false);
        splitter_3->addWidget(orderTab_3);
        summaryTab_3 = new QPushButton(splitter_3);
        summaryTab_3->setObjectName(QString::fromUtf8("summaryTab_3"));
        summaryTab_3->setCheckable(false);
        summaryTab_3->setChecked(false);
        splitter_3->addWidget(summaryTab_3);
        profileTab_3 = new QPushButton(splitter_3);
        profileTab_3->setObjectName(QString::fromUtf8("profileTab_3"));
        profileTab_3->setFont(font);
        profileTab_3->setCheckable(false);
        profileTab_3->setChecked(false);
        profileTab_3->setAutoDefault(false);
        profileTab_3->setFlat(true);
        splitter_3->addWidget(profileTab_3);
        statsTab_3 = new QPushButton(splitter_3);
        statsTab_3->setObjectName(QString::fromUtf8("statsTab_3"));
        splitter_3->addWidget(statsTab_3);
        logoutTab_3 = new QPushButton(splitter_3);
        logoutTab_3->setObjectName(QString::fromUtf8("logoutTab_3"));
        splitter_3->addWidget(logoutTab_3);
        line = new QFrame(Profile);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(380, 50, 31, 541));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(Profile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 70, 181, 41));
        QFont font3;
        font3.setPointSize(20);
        label->setFont(font3);
        label_2 = new QLabel(Profile);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(550, 70, 111, 41));
        label_2->setFont(font3);
        balanceCount = new QLineEdit(Profile);
        balanceCount->setObjectName(QString::fromUtf8("balanceCount"));
        balanceCount->setEnabled(false);
        balanceCount->setGeometry(QRect(550, 120, 113, 22));
        balanceSpinBox = new QDoubleSpinBox(Profile);
        balanceSpinBox->setObjectName(QString::fromUtf8("balanceSpinBox"));
        balanceSpinBox->setGeometry(QRect(560, 270, 101, 31));
        balanceSpinBox->setMinimum(-99.000000000000000);
        layoutWidget_2 = new QWidget(Profile);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(400, 450, 381, 53));
        verticalLayout_5 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        errorProfileBalanceLabel = new QLabel(layoutWidget_2);
        errorProfileBalanceLabel->setObjectName(QString::fromUtf8("errorProfileBalanceLabel"));

        verticalLayout_5->addWidget(errorProfileBalanceLabel);

        updateBalanceBtn = new QPushButton(layoutWidget_2);
        updateBalanceBtn->setObjectName(QString::fromUtf8("updateBalanceBtn"));

        verticalLayout_5->addWidget(updateBalanceBtn);

        layoutWidget1 = new QWidget(Profile);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 120, 241, 319));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        nameProfileLabel = new QLabel(layoutWidget1);
        nameProfileLabel->setObjectName(QString::fromUtf8("nameProfileLabel"));

        verticalLayout_2->addWidget(nameProfileLabel);

        nameLineEdit = new QLineEdit(layoutWidget1);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        verticalLayout_2->addWidget(nameLineEdit);

        surnameProfileLabel = new QLabel(layoutWidget1);
        surnameProfileLabel->setObjectName(QString::fromUtf8("surnameProfileLabel"));

        verticalLayout_2->addWidget(surnameProfileLabel);

        surnameLineEdit = new QLineEdit(layoutWidget1);
        surnameLineEdit->setObjectName(QString::fromUtf8("surnameLineEdit"));

        verticalLayout_2->addWidget(surnameLineEdit);

        emailProfileLabel = new QLabel(layoutWidget1);
        emailProfileLabel->setObjectName(QString::fromUtf8("emailProfileLabel"));

        verticalLayout_2->addWidget(emailProfileLabel);

        emailLineEdit = new QLineEdit(layoutWidget1);
        emailLineEdit->setObjectName(QString::fromUtf8("emailLineEdit"));
        emailLineEdit->setEnabled(true);

        verticalLayout_2->addWidget(emailLineEdit);

        pswProfileLabel = new QLabel(layoutWidget1);
        pswProfileLabel->setObjectName(QString::fromUtf8("pswProfileLabel"));

        verticalLayout_2->addWidget(pswProfileLabel);

        pswLineEdit = new QLineEdit(layoutWidget1);
        pswLineEdit->setObjectName(QString::fromUtf8("pswLineEdit"));
        pswLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(pswLineEdit);

        phoneProfileLabel = new QLabel(layoutWidget1);
        phoneProfileLabel->setObjectName(QString::fromUtf8("phoneProfileLabel"));

        verticalLayout_2->addWidget(phoneProfileLabel);

        phoneLineEdit = new QLineEdit(layoutWidget1);
        phoneLineEdit->setObjectName(QString::fromUtf8("phoneLineEdit"));

        verticalLayout_2->addWidget(phoneLineEdit);

        dateProfileLabel = new QLabel(layoutWidget1);
        dateProfileLabel->setObjectName(QString::fromUtf8("dateProfileLabel"));

        verticalLayout_2->addWidget(dateProfileLabel);

        dateLineEdit = new QLineEdit(layoutWidget1);
        dateLineEdit->setObjectName(QString::fromUtf8("dateLineEdit"));
        dateLineEdit->setEnabled(false);

        verticalLayout_2->addWidget(dateLineEdit);

        layoutWidget2 = new QWidget(Profile);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 450, 391, 53));
        verticalLayout_4 = new QVBoxLayout(layoutWidget2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        errorProfileLabel = new QLabel(layoutWidget2);
        errorProfileLabel->setObjectName(QString::fromUtf8("errorProfileLabel"));

        verticalLayout_4->addWidget(errorProfileLabel);

        updateProfileBtn = new QPushButton(layoutWidget2);
        updateProfileBtn->setObjectName(QString::fromUtf8("updateProfileBtn"));

        verticalLayout_4->addWidget(updateProfileBtn);

        UserInterface->addWidget(Profile);
        Stats = new QWidget();
        Stats->setObjectName(QString::fromUtf8("Stats"));
        splitter_4 = new QSplitter(Stats);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setGeometry(QRect(0, 10, 781, 28));
        splitter_4->setOrientation(Qt::Horizontal);
        orderTab_4 = new QPushButton(splitter_4);
        orderTab_4->setObjectName(QString::fromUtf8("orderTab_4"));
        orderTab_4->setFont(font2);
        orderTab_4->setFocusPolicy(Qt::StrongFocus);
        orderTab_4->setCheckable(false);
        orderTab_4->setChecked(false);
        splitter_4->addWidget(orderTab_4);
        summaryTab_4 = new QPushButton(splitter_4);
        summaryTab_4->setObjectName(QString::fromUtf8("summaryTab_4"));
        summaryTab_4->setCheckable(false);
        summaryTab_4->setChecked(false);
        splitter_4->addWidget(summaryTab_4);
        profileTab_4 = new QPushButton(splitter_4);
        profileTab_4->setObjectName(QString::fromUtf8("profileTab_4"));
        splitter_4->addWidget(profileTab_4);
        statsTab_4 = new QPushButton(splitter_4);
        statsTab_4->setObjectName(QString::fromUtf8("statsTab_4"));
        statsTab_4->setFont(font);
        statsTab_4->setCheckable(false);
        statsTab_4->setChecked(false);
        statsTab_4->setAutoDefault(false);
        statsTab_4->setFlat(true);
        splitter_4->addWidget(statsTab_4);
        logoutTab_4 = new QPushButton(splitter_4);
        logoutTab_4->setObjectName(QString::fromUtf8("logoutTab_4"));
        splitter_4->addWidget(logoutTab_4);
        UserInterface->addWidget(Stats);

        retranslateUi(UserGUI);

        UserInterface->setCurrentIndex(2);
        orderTab->setDefault(true);
        summaryTab_2->setDefault(true);
        profileTab_3->setDefault(true);
        statsTab_4->setDefault(true);


        QMetaObject::connectSlotsByName(UserGUI);
    } // setupUi

    void retranslateUi(QDialog *UserGUI)
    {
        UserGUI->setWindowTitle(QCoreApplication::translate("UserGUI", "UserGUI", nullptr));
        QTableWidgetItem *___qtablewidgetitem = restaurantList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UserGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = restaurantList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UserGUI", "Restaurant", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = restaurantList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserGUI", "Address", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = restaurantList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("UserGUI", "Phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = restaurantList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("UserGUI", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = dishList->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("UserGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = dishList->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("UserGUI", "Dish", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = dishList->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("UserGUI", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = dishList->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("UserGUI", "Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = dishList->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("UserGUI", "Quantity", nullptr));
        errorsLabel->setText(QString());
        submitOrderBtn->setText(QCoreApplication::translate("UserGUI", "Submit order", nullptr));
        orderTab->setText(QCoreApplication::translate("UserGUI", "Order", nullptr));
        summaryTab->setText(QCoreApplication::translate("UserGUI", "Orders Summary", nullptr));
        profileTab->setText(QCoreApplication::translate("UserGUI", "Profile", nullptr));
        statsTab->setText(QCoreApplication::translate("UserGUI", "Stats", nullptr));
        logoutTab->setText(QCoreApplication::translate("UserGUI", "Logout", nullptr));
        orderTab_2->setText(QCoreApplication::translate("UserGUI", "Order", nullptr));
        summaryTab_2->setText(QCoreApplication::translate("UserGUI", "Orders Summary", nullptr));
        profileTab_2->setText(QCoreApplication::translate("UserGUI", "Profile", nullptr));
        statsTab_2->setText(QCoreApplication::translate("UserGUI", "Stats", nullptr));
        logoutTab_2->setText(QCoreApplication::translate("UserGUI", "Logout", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = orderList->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("UserGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = orderList->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("UserGUI", "Restaurant", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = orderList->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("UserGUI", "Total", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = orderList->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("UserGUI", "Status", nullptr));
        orderTab_3->setText(QCoreApplication::translate("UserGUI", "Order", nullptr));
        summaryTab_3->setText(QCoreApplication::translate("UserGUI", "Orders Summary", nullptr));
        profileTab_3->setText(QCoreApplication::translate("UserGUI", "Profile", nullptr));
        statsTab_3->setText(QCoreApplication::translate("UserGUI", "Stats", nullptr));
        logoutTab_3->setText(QCoreApplication::translate("UserGUI", "Logout", nullptr));
        label->setText(QCoreApplication::translate("UserGUI", "Your Profile", nullptr));
        label_2->setText(QCoreApplication::translate("UserGUI", "Balance", nullptr));
        errorProfileBalanceLabel->setText(QString());
        updateBalanceBtn->setText(QCoreApplication::translate("UserGUI", "Update balance", nullptr));
        nameProfileLabel->setText(QCoreApplication::translate("UserGUI", "Name", nullptr));
        surnameProfileLabel->setText(QCoreApplication::translate("UserGUI", "Surname", nullptr));
        emailProfileLabel->setText(QCoreApplication::translate("UserGUI", "Email", nullptr));
        pswProfileLabel->setText(QCoreApplication::translate("UserGUI", "Password", nullptr));
        pswLineEdit->setInputMask(QString());
        pswLineEdit->setText(QString());
        phoneProfileLabel->setText(QCoreApplication::translate("UserGUI", "Phone number", nullptr));
        dateProfileLabel->setText(QCoreApplication::translate("UserGUI", "Birth date", nullptr));
        errorProfileLabel->setText(QString());
        updateProfileBtn->setText(QCoreApplication::translate("UserGUI", "Update data", nullptr));
        orderTab_4->setText(QCoreApplication::translate("UserGUI", "Order", nullptr));
        summaryTab_4->setText(QCoreApplication::translate("UserGUI", "Orders Summary", nullptr));
        profileTab_4->setText(QCoreApplication::translate("UserGUI", "Profile", nullptr));
        statsTab_4->setText(QCoreApplication::translate("UserGUI", "Stats", nullptr));
        logoutTab_4->setText(QCoreApplication::translate("UserGUI", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserGUI: public Ui_UserGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERGUI_H
