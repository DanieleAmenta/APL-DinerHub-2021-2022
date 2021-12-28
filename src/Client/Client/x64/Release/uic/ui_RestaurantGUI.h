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
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_RestaurantGUI
{
public:
    QLabel *label;

    void setupUi(QDialog *RestaurantGUI)
    {
        if (RestaurantGUI->objectName().isEmpty())
            RestaurantGUI->setObjectName(QString::fromUtf8("RestaurantGUI"));
        RestaurantGUI->resize(402, 300);
        label = new QLabel(RestaurantGUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 140, 181, 16));

        retranslateUi(RestaurantGUI);

        QMetaObject::connectSlotsByName(RestaurantGUI);
    } // setupUi

    void retranslateUi(QDialog *RestaurantGUI)
    {
        RestaurantGUI->setWindowTitle(QCoreApplication::translate("RestaurantGUI", "RestaurantGUI", nullptr));
        label->setText(QCoreApplication::translate("RestaurantGUI", "Sei un restaurant", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestaurantGUI: public Ui_RestaurantGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTAURANTGUI_H
