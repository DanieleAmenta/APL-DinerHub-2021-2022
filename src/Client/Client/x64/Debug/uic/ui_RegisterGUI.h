/********************************************************************************
** Form generated from reading UI file 'RegisterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERGUI_H
#define UI_REGISTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterGUI
{
public:
    QLabel *registerLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *registerBtn;
    QPushButton *backToLoginBtn;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QLabel *nameErrorLabel;
    QLabel *surnameErrorLabel;
    QLabel *emaiLErrorLabel;
    QLabel *pswErrorLabel;
    QLabel *phoneErrorLabel;
    QLabel *dateErrorLabel;
    QWidget *layoutWidget_3;
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
    QDateEdit *dateEdit;

    void setupUi(QDialog *RegisterGUI)
    {
        if (RegisterGUI->objectName().isEmpty())
            RegisterGUI->setObjectName(QString::fromUtf8("RegisterGUI"));
        RegisterGUI->resize(577, 431);
        registerLabel = new QLabel(RegisterGUI);
        registerLabel->setObjectName(QString::fromUtf8("registerLabel"));
        registerLabel->setGeometry(QRect(240, 0, 121, 41));
        QFont font;
        font.setPointSize(20);
        registerLabel->setFont(font);
        layoutWidget = new QWidget(RegisterGUI);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 390, 561, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        registerBtn = new QPushButton(layoutWidget);
        registerBtn->setObjectName(QString::fromUtf8("registerBtn"));

        horizontalLayout->addWidget(registerBtn);

        backToLoginBtn = new QPushButton(layoutWidget);
        backToLoginBtn->setObjectName(QString::fromUtf8("backToLoginBtn"));

        horizontalLayout->addWidget(backToLoginBtn);

        layoutWidget_2 = new QWidget(RegisterGUI);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(270, 50, 301, 321));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nameErrorLabel = new QLabel(layoutWidget_2);
        nameErrorLabel->setObjectName(QString::fromUtf8("nameErrorLabel"));

        verticalLayout->addWidget(nameErrorLabel);

        surnameErrorLabel = new QLabel(layoutWidget_2);
        surnameErrorLabel->setObjectName(QString::fromUtf8("surnameErrorLabel"));

        verticalLayout->addWidget(surnameErrorLabel);

        emaiLErrorLabel = new QLabel(layoutWidget_2);
        emaiLErrorLabel->setObjectName(QString::fromUtf8("emaiLErrorLabel"));

        verticalLayout->addWidget(emaiLErrorLabel);

        pswErrorLabel = new QLabel(layoutWidget_2);
        pswErrorLabel->setObjectName(QString::fromUtf8("pswErrorLabel"));

        verticalLayout->addWidget(pswErrorLabel);

        phoneErrorLabel = new QLabel(layoutWidget_2);
        phoneErrorLabel->setObjectName(QString::fromUtf8("phoneErrorLabel"));

        verticalLayout->addWidget(phoneErrorLabel);

        dateErrorLabel = new QLabel(layoutWidget_2);
        dateErrorLabel->setObjectName(QString::fromUtf8("dateErrorLabel"));

        verticalLayout->addWidget(dateErrorLabel);

        layoutWidget_3 = new QWidget(RegisterGUI);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 50, 241, 319));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        nameProfileLabel = new QLabel(layoutWidget_3);
        nameProfileLabel->setObjectName(QString::fromUtf8("nameProfileLabel"));

        verticalLayout_2->addWidget(nameProfileLabel);

        nameLineEdit = new QLineEdit(layoutWidget_3);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        verticalLayout_2->addWidget(nameLineEdit);

        surnameProfileLabel = new QLabel(layoutWidget_3);
        surnameProfileLabel->setObjectName(QString::fromUtf8("surnameProfileLabel"));

        verticalLayout_2->addWidget(surnameProfileLabel);

        surnameLineEdit = new QLineEdit(layoutWidget_3);
        surnameLineEdit->setObjectName(QString::fromUtf8("surnameLineEdit"));

        verticalLayout_2->addWidget(surnameLineEdit);

        emailProfileLabel = new QLabel(layoutWidget_3);
        emailProfileLabel->setObjectName(QString::fromUtf8("emailProfileLabel"));

        verticalLayout_2->addWidget(emailProfileLabel);

        emailLineEdit = new QLineEdit(layoutWidget_3);
        emailLineEdit->setObjectName(QString::fromUtf8("emailLineEdit"));
        emailLineEdit->setEnabled(true);

        verticalLayout_2->addWidget(emailLineEdit);

        pswProfileLabel = new QLabel(layoutWidget_3);
        pswProfileLabel->setObjectName(QString::fromUtf8("pswProfileLabel"));

        verticalLayout_2->addWidget(pswProfileLabel);

        pswLineEdit = new QLineEdit(layoutWidget_3);
        pswLineEdit->setObjectName(QString::fromUtf8("pswLineEdit"));
        pswLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(pswLineEdit);

        phoneProfileLabel = new QLabel(layoutWidget_3);
        phoneProfileLabel->setObjectName(QString::fromUtf8("phoneProfileLabel"));

        verticalLayout_2->addWidget(phoneProfileLabel);

        phoneLineEdit = new QLineEdit(layoutWidget_3);
        phoneLineEdit->setObjectName(QString::fromUtf8("phoneLineEdit"));

        verticalLayout_2->addWidget(phoneLineEdit);

        dateProfileLabel = new QLabel(layoutWidget_3);
        dateProfileLabel->setObjectName(QString::fromUtf8("dateProfileLabel"));

        verticalLayout_2->addWidget(dateProfileLabel);

        dateEdit = new QDateEdit(layoutWidget_3);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        verticalLayout_2->addWidget(dateEdit);


        retranslateUi(RegisterGUI);

        QMetaObject::connectSlotsByName(RegisterGUI);
    } // setupUi

    void retranslateUi(QDialog *RegisterGUI)
    {
        RegisterGUI->setWindowTitle(QCoreApplication::translate("RegisterGUI", "RegisterGUI", nullptr));
        registerLabel->setText(QCoreApplication::translate("RegisterGUI", "Register", nullptr));
        registerBtn->setText(QCoreApplication::translate("RegisterGUI", "Register", nullptr));
        backToLoginBtn->setText(QCoreApplication::translate("RegisterGUI", "Back to login", nullptr));
        nameErrorLabel->setText(QString());
        surnameErrorLabel->setText(QString());
        emaiLErrorLabel->setText(QString());
        pswErrorLabel->setText(QString());
        phoneErrorLabel->setText(QString());
        dateErrorLabel->setText(QString());
        nameProfileLabel->setText(QCoreApplication::translate("RegisterGUI", "Name", nullptr));
        surnameProfileLabel->setText(QCoreApplication::translate("RegisterGUI", "Surname", nullptr));
        emailProfileLabel->setText(QCoreApplication::translate("RegisterGUI", "Email", nullptr));
        pswProfileLabel->setText(QCoreApplication::translate("RegisterGUI", "Password", nullptr));
        pswLineEdit->setInputMask(QString());
        pswLineEdit->setText(QString());
        phoneProfileLabel->setText(QCoreApplication::translate("RegisterGUI", "Phone number", nullptr));
        dateProfileLabel->setText(QCoreApplication::translate("RegisterGUI", "Birth date", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterGUI: public Ui_RegisterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERGUI_H
