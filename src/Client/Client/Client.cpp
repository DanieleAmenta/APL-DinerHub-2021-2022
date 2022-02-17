#include "Client.h"
#include <QpixMap>
Client::Client(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    
    cpr::Response response = cpr::Get(cpr::Url{ serverPingUrl });
    if (response.status_code != 200) {
        QMessageBox::warning(this, "Fatal Error", "Server is not available. Please try later!");
    }
}

/**
* Flow to login a restaurant, an user or an admin
*/
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

            if (j.contains("IsAdmin")) {
                bool isAdmin = j["IsAdmin"];

                if (isAdmin) {
                    // Admin flow
                    adminGUI = new AdminGUI(this, j["UserId"], j["Token"]);

                    ui.emailField->setText(QString::fromStdString(""));
                    ui.pswField->setText(QString::fromStdString(""));

                    adminGUI->show();
                }
                else {
                    // User flow
                    userGUI = new UserGUI(this, j["UserId"], j["Token"]);

                    ui.emailField->setText(QString::fromStdString(""));
                    ui.pswField->setText(QString::fromStdString(""));

                    userGUI->show();
                }
            }
            else if (j.contains("IsRestaurant")) {
                // All restaurants have IsRestaurant set to true, but we do a double check
                bool isRestaurant = j["IsRestaurant"];

                if (isRestaurant) {
                    restaurantGUI = new RestaurantGUI(this, j["RestaurantId"], j["Token"]);

                    ui.emailField->setText(QString::fromStdString(""));
                    ui.pswField->setText(QString::fromStdString(""));

                    restaurantGUI->show();
                }
            }
        }
        else {
            ui.pswError->setText(QString::fromStdString("Email or password not valid!"));
        }
    }
}

/**
* Open RegisterGUI interface
*/
void Client::on_registerButton_clicked() {
    registerGUI = new RegisterGUI();

    ui.emailField->setText(QString::fromStdString(""));
    ui.pswField->setText(QString::fromStdString(""));

    registerGUI->show();
}
