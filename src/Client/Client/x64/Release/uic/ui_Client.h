/********************************************************************************
** Form generated from reading UI file 'Client.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientClass
{
public:
    QTextEdit *textEdit;
    QPushButton *loginButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *emailLabel;
    QLineEdit *emailField;
    QLabel *emailError;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pswLabel;
    QLineEdit *pswField;
    QLabel *pswError;
    QLabel *label_3;
    QLabel *label;

    void setupUi(QWidget *ClientClass)
    {
        if (ClientClass->objectName().isEmpty())
            ClientClass->setObjectName(QString::fromUtf8("ClientClass"));
        ClientClass->resize(349, 400);
        textEdit = new QTextEdit(ClientClass);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 331, 41));
        loginButton = new QPushButton(ClientClass);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(20, 340, 311, 28));
        layoutWidget = new QWidget(ClientClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 180, 311, 151));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        horizontalLayout->addLayout(horizontalLayout_2);

        emailLabel = new QLabel(layoutWidget);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));

        horizontalLayout->addWidget(emailLabel);

        emailField = new QLineEdit(layoutWidget);
        emailField->setObjectName(QString::fromUtf8("emailField"));

        horizontalLayout->addWidget(emailField);


        verticalLayout->addLayout(horizontalLayout);

        emailError = new QLabel(layoutWidget);
        emailError->setObjectName(QString::fromUtf8("emailError"));

        verticalLayout->addWidget(emailError);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pswLabel = new QLabel(layoutWidget);
        pswLabel->setObjectName(QString::fromUtf8("pswLabel"));

        horizontalLayout_3->addWidget(pswLabel);

        pswField = new QLineEdit(layoutWidget);
        pswField->setObjectName(QString::fromUtf8("pswField"));
        pswField->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(pswField);


        verticalLayout->addLayout(horizontalLayout_3);

        pswError = new QLabel(layoutWidget);
        pswError->setObjectName(QString::fromUtf8("pswError"));

        verticalLayout->addWidget(pswError);

        label_3 = new QLabel(ClientClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 370, 221, 16));
        label_3->setFocusPolicy(Qt::ClickFocus);
        label = new QLabel(ClientClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 100, 91, 16));

        retranslateUi(ClientClass);

        QMetaObject::connectSlotsByName(ClientClass);
    } // setupUi

    void retranslateUi(QWidget *ClientClass)
    {
        ClientClass->setWindowTitle(QCoreApplication::translate("ClientClass", "Client", nullptr));
        loginButton->setText(QCoreApplication::translate("ClientClass", "LOGIN", nullptr));
        emailLabel->setText(QCoreApplication::translate("ClientClass", "Email", nullptr));
        emailError->setText(QString());
        pswLabel->setText(QCoreApplication::translate("ClientClass", "Password", nullptr));
        pswError->setText(QString());
        label_3->setText(QCoreApplication::translate("ClientClass", "Not registered yet? Create an account!", nullptr));
        label->setText(QCoreApplication::translate("ClientClass", "LOGO DinerHub", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientClass: public Ui_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
