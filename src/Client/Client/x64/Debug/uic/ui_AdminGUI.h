/********************************************************************************
** Form generated from reading UI file 'AdminGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINGUI_H
#define UI_ADMINGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
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

class Ui_AdminGUI
{
public:
    QStackedWidget *AdminInterface;
    QWidget *UserList;
    QTableWidget *userList;
    QPushButton *deleteUserBtn;
    QLabel *userListErrorLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *userListTab;
    QPushButton *restaurantListTab;
    QPushButton *profileTab;
    QPushButton *statsTab;
    QPushButton *logoutTab;
    QWidget *RestaurantList;
    QLabel *createRestaurantLabel;
    QFrame *line;
    QTableWidget *restaurantList;
    QPushButton *deleteRestaurantBtn;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *userListTab_2;
    QPushButton *restaurantListTab_2;
    QPushButton *profileTab_2;
    QPushButton *statsTab_2;
    QPushButton *logoutTab_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QLabel *restaurantNameLabel;
    QLineEdit *restaurantName;
    QLabel *restaurantAddLabel;
    QLineEdit *restaurantAdd;
    QLabel *restaurantPhoneLabel;
    QLineEdit *restaurantPhone;
    QLabel *restaurantEmailLabel;
    QLineEdit *restaurantEmail;
    QLabel *restaurantPswLabel;
    QLineEdit *restaurantPsw;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QLabel *createRestaurantError;
    QPushButton *createRestaurantBtn;
    QLabel *deleteRestaurantLabel;
    QWidget *Profile;
    QLabel *label;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *userListTab_3;
    QPushButton *restaurantListTab_3;
    QPushButton *profileTab_3;
    QPushButton *statsTab_3;
    QPushButton *logoutTab_3;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_3;
    QLabel *emailProfileLabel;
    QLineEdit *emailLineEdit;
    QLabel *pswProfileLabel;
    QLineEdit *pswLineEdit;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_4;
    QLabel *updateProfileError;
    QPushButton *updateProfileBtn;
    QWidget *Stats;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *userListTab_4;
    QPushButton *restaurantListTab_4;
    QPushButton *profileTab_4;
    QPushButton *statsTab_4;
    QPushButton *logoutTab_4;

    void setupUi(QDialog *AdminGUI)
    {
        if (AdminGUI->objectName().isEmpty())
            AdminGUI->setObjectName(QString::fromUtf8("AdminGUI"));
        AdminGUI->resize(800, 630);
        AdminInterface = new QStackedWidget(AdminGUI);
        AdminInterface->setObjectName(QString::fromUtf8("AdminInterface"));
        AdminInterface->setGeometry(QRect(10, 10, 781, 611));
        UserList = new QWidget();
        UserList->setObjectName(QString::fromUtf8("UserList"));
        userList = new QTableWidget(UserList);
        if (userList->columnCount() < 6)
            userList->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        userList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        userList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        userList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        userList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        userList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        userList->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        userList->setObjectName(QString::fromUtf8("userList"));
        userList->setGeometry(QRect(0, 50, 781, 521));
        deleteUserBtn = new QPushButton(UserList);
        deleteUserBtn->setObjectName(QString::fromUtf8("deleteUserBtn"));
        deleteUserBtn->setGeometry(QRect(610, 580, 171, 28));
        userListErrorLabel = new QLabel(UserList);
        userListErrorLabel->setObjectName(QString::fromUtf8("userListErrorLabel"));
        userListErrorLabel->setGeometry(QRect(420, 580, 191, 31));
        layoutWidget = new QWidget(UserList);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 10, 781, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        userListTab = new QPushButton(layoutWidget);
        userListTab->setObjectName(QString::fromUtf8("userListTab"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        userListTab->setFont(font);
        userListTab->setAutoDefault(false);
        userListTab->setFlat(true);

        horizontalLayout->addWidget(userListTab);

        restaurantListTab = new QPushButton(layoutWidget);
        restaurantListTab->setObjectName(QString::fromUtf8("restaurantListTab"));

        horizontalLayout->addWidget(restaurantListTab);

        profileTab = new QPushButton(layoutWidget);
        profileTab->setObjectName(QString::fromUtf8("profileTab"));

        horizontalLayout->addWidget(profileTab);

        statsTab = new QPushButton(layoutWidget);
        statsTab->setObjectName(QString::fromUtf8("statsTab"));

        horizontalLayout->addWidget(statsTab);

        logoutTab = new QPushButton(layoutWidget);
        logoutTab->setObjectName(QString::fromUtf8("logoutTab"));

        horizontalLayout->addWidget(logoutTab);

        AdminInterface->addWidget(UserList);
        RestaurantList = new QWidget();
        RestaurantList->setObjectName(QString::fromUtf8("RestaurantList"));
        createRestaurantLabel = new QLabel(RestaurantList);
        createRestaurantLabel->setObjectName(QString::fromUtf8("createRestaurantLabel"));
        createRestaurantLabel->setGeometry(QRect(20, 80, 361, 31));
        QFont font1;
        font1.setPointSize(20);
        createRestaurantLabel->setFont(font1);
        line = new QFrame(RestaurantList);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(380, 50, 20, 541));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        restaurantList = new QTableWidget(RestaurantList);
        if (restaurantList->columnCount() < 4)
            restaurantList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        restaurantList->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        restaurantList->setObjectName(QString::fromUtf8("restaurantList"));
        restaurantList->setGeometry(QRect(390, 50, 391, 491));
        deleteRestaurantBtn = new QPushButton(RestaurantList);
        deleteRestaurantBtn->setObjectName(QString::fromUtf8("deleteRestaurantBtn"));
        deleteRestaurantBtn->setGeometry(QRect(390, 570, 391, 28));
        layoutWidget1 = new QWidget(RestaurantList);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 10, 781, 30));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        userListTab_2 = new QPushButton(layoutWidget1);
        userListTab_2->setObjectName(QString::fromUtf8("userListTab_2"));

        horizontalLayout_2->addWidget(userListTab_2);

        restaurantListTab_2 = new QPushButton(layoutWidget1);
        restaurantListTab_2->setObjectName(QString::fromUtf8("restaurantListTab_2"));
        restaurantListTab_2->setFont(font);
        restaurantListTab_2->setAutoDefault(false);
        restaurantListTab_2->setFlat(true);

        horizontalLayout_2->addWidget(restaurantListTab_2);

        profileTab_2 = new QPushButton(layoutWidget1);
        profileTab_2->setObjectName(QString::fromUtf8("profileTab_2"));

        horizontalLayout_2->addWidget(profileTab_2);

        statsTab_2 = new QPushButton(layoutWidget1);
        statsTab_2->setObjectName(QString::fromUtf8("statsTab_2"));

        horizontalLayout_2->addWidget(statsTab_2);

        logoutTab_2 = new QPushButton(layoutWidget1);
        logoutTab_2->setObjectName(QString::fromUtf8("logoutTab_2"));

        horizontalLayout_2->addWidget(logoutTab_2);

        layoutWidget2 = new QWidget(RestaurantList);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 130, 201, 291));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        restaurantNameLabel = new QLabel(layoutWidget2);
        restaurantNameLabel->setObjectName(QString::fromUtf8("restaurantNameLabel"));

        verticalLayout->addWidget(restaurantNameLabel);

        restaurantName = new QLineEdit(layoutWidget2);
        restaurantName->setObjectName(QString::fromUtf8("restaurantName"));

        verticalLayout->addWidget(restaurantName);

        restaurantAddLabel = new QLabel(layoutWidget2);
        restaurantAddLabel->setObjectName(QString::fromUtf8("restaurantAddLabel"));

        verticalLayout->addWidget(restaurantAddLabel);

        restaurantAdd = new QLineEdit(layoutWidget2);
        restaurantAdd->setObjectName(QString::fromUtf8("restaurantAdd"));

        verticalLayout->addWidget(restaurantAdd);

        restaurantPhoneLabel = new QLabel(layoutWidget2);
        restaurantPhoneLabel->setObjectName(QString::fromUtf8("restaurantPhoneLabel"));

        verticalLayout->addWidget(restaurantPhoneLabel);

        restaurantPhone = new QLineEdit(layoutWidget2);
        restaurantPhone->setObjectName(QString::fromUtf8("restaurantPhone"));

        verticalLayout->addWidget(restaurantPhone);

        restaurantEmailLabel = new QLabel(layoutWidget2);
        restaurantEmailLabel->setObjectName(QString::fromUtf8("restaurantEmailLabel"));

        verticalLayout->addWidget(restaurantEmailLabel);

        restaurantEmail = new QLineEdit(layoutWidget2);
        restaurantEmail->setObjectName(QString::fromUtf8("restaurantEmail"));

        verticalLayout->addWidget(restaurantEmail);

        restaurantPswLabel = new QLabel(layoutWidget2);
        restaurantPswLabel->setObjectName(QString::fromUtf8("restaurantPswLabel"));

        verticalLayout->addWidget(restaurantPswLabel);

        restaurantPsw = new QLineEdit(layoutWidget2);
        restaurantPsw->setObjectName(QString::fromUtf8("restaurantPsw"));

        verticalLayout->addWidget(restaurantPsw);

        layoutWidget3 = new QWidget(RestaurantList);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 440, 371, 53));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        createRestaurantError = new QLabel(layoutWidget3);
        createRestaurantError->setObjectName(QString::fromUtf8("createRestaurantError"));

        verticalLayout_2->addWidget(createRestaurantError);

        createRestaurantBtn = new QPushButton(layoutWidget3);
        createRestaurantBtn->setObjectName(QString::fromUtf8("createRestaurantBtn"));

        verticalLayout_2->addWidget(createRestaurantBtn);

        deleteRestaurantLabel = new QLabel(RestaurantList);
        deleteRestaurantLabel->setObjectName(QString::fromUtf8("deleteRestaurantLabel"));
        deleteRestaurantLabel->setGeometry(QRect(400, 550, 371, 20));
        AdminInterface->addWidget(RestaurantList);
        Profile = new QWidget();
        Profile->setObjectName(QString::fromUtf8("Profile"));
        label = new QLabel(Profile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(310, 70, 171, 31));
        label->setFont(font1);
        layoutWidget4 = new QWidget(Profile);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(0, 10, 781, 30));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        userListTab_3 = new QPushButton(layoutWidget4);
        userListTab_3->setObjectName(QString::fromUtf8("userListTab_3"));

        horizontalLayout_3->addWidget(userListTab_3);

        restaurantListTab_3 = new QPushButton(layoutWidget4);
        restaurantListTab_3->setObjectName(QString::fromUtf8("restaurantListTab_3"));

        horizontalLayout_3->addWidget(restaurantListTab_3);

        profileTab_3 = new QPushButton(layoutWidget4);
        profileTab_3->setObjectName(QString::fromUtf8("profileTab_3"));
        profileTab_3->setFont(font);
        profileTab_3->setAutoDefault(false);
        profileTab_3->setFlat(true);

        horizontalLayout_3->addWidget(profileTab_3);

        statsTab_3 = new QPushButton(layoutWidget4);
        statsTab_3->setObjectName(QString::fromUtf8("statsTab_3"));

        horizontalLayout_3->addWidget(statsTab_3);

        logoutTab_3 = new QPushButton(layoutWidget4);
        logoutTab_3->setObjectName(QString::fromUtf8("logoutTab_3"));

        horizontalLayout_3->addWidget(logoutTab_3);

        layoutWidget5 = new QWidget(Profile);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(270, 130, 261, 121));
        verticalLayout_3 = new QVBoxLayout(layoutWidget5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        emailProfileLabel = new QLabel(layoutWidget5);
        emailProfileLabel->setObjectName(QString::fromUtf8("emailProfileLabel"));

        verticalLayout_3->addWidget(emailProfileLabel);

        emailLineEdit = new QLineEdit(layoutWidget5);
        emailLineEdit->setObjectName(QString::fromUtf8("emailLineEdit"));

        verticalLayout_3->addWidget(emailLineEdit);

        pswProfileLabel = new QLabel(layoutWidget5);
        pswProfileLabel->setObjectName(QString::fromUtf8("pswProfileLabel"));

        verticalLayout_3->addWidget(pswProfileLabel);

        pswLineEdit = new QLineEdit(layoutWidget5);
        pswLineEdit->setObjectName(QString::fromUtf8("pswLineEdit"));

        verticalLayout_3->addWidget(pswLineEdit);

        layoutWidget6 = new QWidget(Profile);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(230, 360, 341, 53));
        verticalLayout_4 = new QVBoxLayout(layoutWidget6);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        updateProfileError = new QLabel(layoutWidget6);
        updateProfileError->setObjectName(QString::fromUtf8("updateProfileError"));

        verticalLayout_4->addWidget(updateProfileError);

        updateProfileBtn = new QPushButton(layoutWidget6);
        updateProfileBtn->setObjectName(QString::fromUtf8("updateProfileBtn"));

        verticalLayout_4->addWidget(updateProfileBtn);

        AdminInterface->addWidget(Profile);
        Stats = new QWidget();
        Stats->setObjectName(QString::fromUtf8("Stats"));
        layoutWidget7 = new QWidget(Stats);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(0, 10, 781, 30));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        userListTab_4 = new QPushButton(layoutWidget7);
        userListTab_4->setObjectName(QString::fromUtf8("userListTab_4"));

        horizontalLayout_4->addWidget(userListTab_4);

        restaurantListTab_4 = new QPushButton(layoutWidget7);
        restaurantListTab_4->setObjectName(QString::fromUtf8("restaurantListTab_4"));

        horizontalLayout_4->addWidget(restaurantListTab_4);

        profileTab_4 = new QPushButton(layoutWidget7);
        profileTab_4->setObjectName(QString::fromUtf8("profileTab_4"));

        horizontalLayout_4->addWidget(profileTab_4);

        statsTab_4 = new QPushButton(layoutWidget7);
        statsTab_4->setObjectName(QString::fromUtf8("statsTab_4"));
        statsTab_4->setFont(font);
        statsTab_4->setAutoDefault(false);
        statsTab_4->setFlat(true);

        horizontalLayout_4->addWidget(statsTab_4);

        logoutTab_4 = new QPushButton(layoutWidget7);
        logoutTab_4->setObjectName(QString::fromUtf8("logoutTab_4"));

        horizontalLayout_4->addWidget(logoutTab_4);

        AdminInterface->addWidget(Stats);

        retranslateUi(AdminGUI);

        AdminInterface->setCurrentIndex(1);
        userListTab->setDefault(true);
        restaurantListTab_2->setDefault(true);
        profileTab_3->setDefault(true);
        statsTab_4->setDefault(true);


        QMetaObject::connectSlotsByName(AdminGUI);
    } // setupUi

    void retranslateUi(QDialog *AdminGUI)
    {
        AdminGUI->setWindowTitle(QCoreApplication::translate("AdminGUI", "AdminGUI", nullptr));
        QTableWidgetItem *___qtablewidgetitem = userList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AdminGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = userList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AdminGUI", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = userList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AdminGUI", "Surname", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = userList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AdminGUI", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = userList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AdminGUI", "Phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = userList->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("AdminGUI", "Balance", nullptr));
        deleteUserBtn->setText(QCoreApplication::translate("AdminGUI", "Delete selected user", nullptr));
        userListErrorLabel->setText(QString());
        userListTab->setText(QCoreApplication::translate("AdminGUI", "User List", nullptr));
        restaurantListTab->setText(QCoreApplication::translate("AdminGUI", "Restaurant List", nullptr));
        profileTab->setText(QCoreApplication::translate("AdminGUI", "Profile", nullptr));
        statsTab->setText(QCoreApplication::translate("AdminGUI", "Stats", nullptr));
        logoutTab->setText(QCoreApplication::translate("AdminGUI", "Logout", nullptr));
        createRestaurantLabel->setText(QCoreApplication::translate("AdminGUI", "Create a new restaurant", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = restaurantList->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("AdminGUI", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = restaurantList->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("AdminGUI", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = restaurantList->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("AdminGUI", "Address", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = restaurantList->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("AdminGUI", "Phone", nullptr));
        deleteRestaurantBtn->setText(QCoreApplication::translate("AdminGUI", "Delete selected restaurant", nullptr));
        userListTab_2->setText(QCoreApplication::translate("AdminGUI", "User List", nullptr));
        restaurantListTab_2->setText(QCoreApplication::translate("AdminGUI", "Restaurant List", nullptr));
        profileTab_2->setText(QCoreApplication::translate("AdminGUI", "Profile", nullptr));
        statsTab_2->setText(QCoreApplication::translate("AdminGUI", "Stats", nullptr));
        logoutTab_2->setText(QCoreApplication::translate("AdminGUI", "Logout", nullptr));
        restaurantNameLabel->setText(QCoreApplication::translate("AdminGUI", "Name", nullptr));
        restaurantAddLabel->setText(QCoreApplication::translate("AdminGUI", "Address", nullptr));
        restaurantPhoneLabel->setText(QCoreApplication::translate("AdminGUI", "Phone", nullptr));
        restaurantEmailLabel->setText(QCoreApplication::translate("AdminGUI", "Email", nullptr));
        restaurantPswLabel->setText(QCoreApplication::translate("AdminGUI", "Password", nullptr));
        createRestaurantError->setText(QString());
        createRestaurantBtn->setText(QCoreApplication::translate("AdminGUI", "Create restaurant", nullptr));
        deleteRestaurantLabel->setText(QString());
        label->setText(QCoreApplication::translate("AdminGUI", "Your Profile", nullptr));
        userListTab_3->setText(QCoreApplication::translate("AdminGUI", "User List", nullptr));
        restaurantListTab_3->setText(QCoreApplication::translate("AdminGUI", "Restaurant List", nullptr));
        profileTab_3->setText(QCoreApplication::translate("AdminGUI", "Profile", nullptr));
        statsTab_3->setText(QCoreApplication::translate("AdminGUI", "Stats", nullptr));
        logoutTab_3->setText(QCoreApplication::translate("AdminGUI", "Logout", nullptr));
        emailProfileLabel->setText(QCoreApplication::translate("AdminGUI", "Email", nullptr));
        pswProfileLabel->setText(QCoreApplication::translate("AdminGUI", "Password", nullptr));
        updateProfileError->setText(QString());
        updateProfileBtn->setText(QCoreApplication::translate("AdminGUI", "Update data", nullptr));
        userListTab_4->setText(QCoreApplication::translate("AdminGUI", "User List", nullptr));
        restaurantListTab_4->setText(QCoreApplication::translate("AdminGUI", "Restaurant List", nullptr));
        profileTab_4->setText(QCoreApplication::translate("AdminGUI", "Profile", nullptr));
        statsTab_4->setText(QCoreApplication::translate("AdminGUI", "Stats", nullptr));
        logoutTab_4->setText(QCoreApplication::translate("AdminGUI", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminGUI: public Ui_AdminGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINGUI_H
