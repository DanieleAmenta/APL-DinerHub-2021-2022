#include "Client.h"

Client::Client(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //TODO: ping ai server !!
}

void Client::on_loginButton_clicked()
{
    boolean error = false;
    ui.emailError->setText(QString::fromStdString(""));
    ui.pswError->setText(QString::fromStdString(""));

    QString email = ui.emailField->text();
    QString password = ui.pswField->text();

    string sEmail = email.toStdString();
    string pswToValidate = password.toStdString();

    if (!regex_match(sEmail, regex(R"(([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+))"))) {
        ui.emailError->setText(QString::fromStdString("Insert a valid email!"));
        error = true;
    }
    if (!regex_match(pswToValidate, regex(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d\w\W]{8,})"))) {
        ui.pswError->setText(QString::fromStdString("Insert a valid password!"));
        error = true;
    }

    if (!error) {
        string sPsw = sha256(pswToValidate);

        cpr::Response r = cpr::Post(cpr::Url{ serverUrl + "/user/login" },
            cpr::Parameters{ {"email", sEmail}, {"psw", sPsw} });

        if (r.status_code == 200) {
            json j = json::parse(r.text);

            if (j.contains("isAdmin")) {
                bool isAdmin = j["isAdmin"];

                if (isAdmin) {
                    adminGUI = new AdminGUI(this);

                    ui.emailField->setText(QString::fromStdString(""));
                    ui.pswField->setText(QString::fromStdString(""));

                    // Set session variable
                    adminGUI->setAdminId(j["userId"]);

                    adminGUI->show();
                }
                else {
                    userGUI = new UserGUI(this);

                    ui.emailField->setText(QString::fromStdString(""));
                    ui.pswField->setText(QString::fromStdString(""));

                    // Set session variable
                    userGUI->setUserId(j["userId"]);

                    userGUI->show();
                }
            }
            else if (j.contains("isRestaurant")) {
                // All restaurants have isRestaurant set to true, but we do a double check
                bool isRestaurant = j["isRestaurant"];

                if (isRestaurant) {
                    restaurantGUI = new RestaurantGUI(this);

                    ui.emailField->setText(QString::fromStdString(""));
                    ui.pswField->setText(QString::fromStdString(""));

                    // Set session variable
                    restaurantGUI->setRestaurantId(j["restaurantId"]);

                    restaurantGUI->show();
                }
            }
        }
        else {
            ui.pswError->setText(QString::fromStdString("Email or password not valid!"));
        }
    }
}

void Client::on_registerButton_clicked() {
    registerGUI = new RegisterGUI();

    ui.emailField->setText(QString::fromStdString(""));
    ui.pswField->setText(QString::fromStdString(""));

    registerGUI->show();
}
