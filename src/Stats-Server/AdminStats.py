import pymongo
import os
from datetime import date
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
import numpy as np
import io
import variables

connectionToMongo = pymongo.MongoClient("mongodb://localhost:27017/")
softwareStartDate = date(2021, 12, 7)

path = os.getcwd()
baseUrl = path.replace("\\", r'/') + '/'
subFolder = "AdminStats/"
isExist = os.path.exists(baseUrl + subFolder)
if not isExist:
    os.mkdir("AdminStats")
print(isExist)

from __main__ import app


#
# API /adminStats/allUsers
# Returns the number of users registered on the platform
#
@app.route('/adminStats/allUsers')
@variables.token_required_admin
def show_users():
    database = connectionToMongo["dinerhub"]
    collection = database["User"]
    critery = {"IsAdmin": False}

    data = {}
    count = collection.count_documents(critery)

    data["count"] = count
    return data


#
# API /adminStats/totalOrder
# Returns the number of orders placed since the beginning
#
@app.route('/adminStats/totalOrder')
@variables.token_required_admin
def show_total_order():
    database = connectionToMongo["dinerhub"]
    collection = database["Order"]
    data = {}
    count = collection.count_documents({})
    data["count"] = count
    return data


#
# API /adminStats/totals
# Returns the total revenue obtained from the platform
#
@app.route('/adminStats/totals')
@variables.token_required_admin
def show_totals():
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    totals = 0
    data = {}
    count = orders.count_documents({})

    # if number of orders is zero, return an empty value
    if count == 0:
        data["total"] = 0
        return data
    for element in orders.find():
        totals = totals + element["Total"]

    data["total"] = 'E. ' + str(totals)
    return data


#
# API /adminStats/dailyOrders
# Returns the average of daily orders
#
@app.route('/adminStats/dailyOrders')
@variables.token_required_admin
def show_daily_orders():
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    data = {}  # value to return
    count = orders.count_documents({})

    date_object = date.today()
    days_of_Activity = date_object - softwareStartDate
    days_count = days_of_Activity.days

    average = count / days_count
    data["average"] = int(average)
    return data


#
# API /adminStats/bestCustomer
# Returns the user who spent the most money
#
@app.route('/adminStats/bestCustomer')
@variables.token_required_admin
def show_best_customer():
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    users = database["User"]
    id = 0
    max_totals = 0
    data = {}
    check = users.count_documents({})
    # if number of users is zero, return an empty value
    if check == 0:
        data["name"] = ""
        return data

    for element in users.find():
        # if number of users is different from zero, calculate the result
        id_customer = element["UserId"]
        critery = {"UserId": id_customer}
        count = 0

        # for each order, adds the total to the counter
        for x in orders.find(critery):
            count = count + x["Total"]
        if count > max_totals:
            # we found a new user who spent the most
            max_totals = count
            id = id_customer

    # return the name of the best customer
    best_customer_id = {"UserId": id}
    best_customer = users.find_one(best_customer_id)
    data["name"] = best_customer["Name"] + ' ' + best_customer["Surname"]
    return data


#
# API /adminStats/bestCustomerOfMonth
# Returns the user who spent the most money in this month
#
@app.route('/adminStats/bestCustomerOfMonth')
@variables.token_required_admin
def show_best_customer_of_month():
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    users = database["User"]

    # get information about the current month
    date_object = date.today()
    current_month = date_object.month
    id = 0
    max_totals = 0
    data = {}
    check = users.count_documents({})
    # if number of users is zero, return an empty value
    if check == 0:
        data["name"] = ""
        return data

    for element in users.find():
        # if number of users is different from zero, calculate the result
        id_customer = element["UserId"]
        critery = {"UserId": id_customer}
        count = 0

        # for each order, adds the total to the counter
        for order in orders.find(critery):
            today = order["Date"]
            month = today.month
            if month == current_month:
                count = count + order["Total"]
                if count > max_totals:
                    # we found a new user who spent the most
                    max_totals = count
                    id = id_customer

    best_customer_id = {"UserId": id}
    best_customer = users.find_one(best_customer_id)
    # print(best_customer)
    data["name"] = best_customer["Name"] + ' ' + best_customer["Surname"]
    return data


#
# API /adminStats/topgrossing
# Returns the highest grossing restaurant
#
@app.route('/adminStats/topgrossing')
@variables.token_required_admin
def show_top_grossing():
    database = connectionToMongo["dinerhub"]
    collection = database["Restaurant"]
    id = 0
    max_totals = 0
    data = {}
    check = collection.count_documents({})

    # if restaurant number is zero, return an empty value
    if check == 0:
        data["name"] = ""
        return data

    for element in collection.find():
        # if restaurant number is different from zero, calculate the result
        id_restaurant = element["RestaurantId"]
        order = database["Order"]
        critery = {"RestaurantId": id_restaurant}
        count = 0

        for x in order.find(critery):
            count = count + x["Total"]
        if count > max_totals:
            # we found a new highest grossing restaurant
            max_totals = count
            id = id_restaurant

    best_restaurant = {"RestaurantId": id}
    restaurant = collection.find_one(best_restaurant)
    name = restaurant["Name"]
    data["name"] = name
    return data


import base64


#
# API /adminStats/plotOrdersForHour
# Returns a graph showing the orders for hours
# Time slots analyzed: 18-19 / 19-20 / 20-21 / 21-22 / 22-23 / 23-00
#
@app.route('/adminStats/plotOrdersForHour')
@variables.token_required_admin
def show_plot_order_for_hour():
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    data = {}

    # check if the system contains orders
    check = orders.count_documents({})
    if check == 0:
        # return a generic image
        data["link"] = baseUrl + "static/loading.png"
        return data

    # count_one :   18-19
    # count_two :   19-20
    # count_three : 20-21
    # count_four  : 21-22
    # count_five  : 22-23
    # count_six   : 23-00
    count_one, count_two, count_three, count_four, count_five, count_six = 0, 0, 0, 0, 0, 0

    for element in orders.find():
        date = element["Date"]
        hour = date.hour
        if hour == 18:
            count_one = count_one + 1
        elif hour == 19:
            count_two = count_two + 1
        elif hour == 20:
            count_three = count_three + 1
        elif hour == 21:
            count_four = count_four + 1
        elif hour == 22:
            count_five = count_five + 1
        elif hour == 23:
            count_six = count_six + 1

    # plot the graph
    x = np.arange(6)
    count_order = [count_one, count_two, count_three, count_four, count_five, count_six]
    fig, ax = plt.subplots()
    plt.bar(x, count_order)
    plt.xticks(x, ('18', '19', '20', '21', '22', '23'))
    link = 'plotOrdersForHour.png'
    plt.savefig(subFolder + link, dpi=50)
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    data["link"] = baseUrl + subFolder + link
    # my_stringIObytes = io.BytesIO()
    # plt.savefig(my_stringIObytes, format='jpg')
    # my_stringIObytes.seek(0)
    # my_base64_jpgData = base64.b64encode(my_stringIObytes.read())
    # data = {}
    # data["test"] = my_base64_jpgData
    # return my_base64_jpgData
    # return Response(output.getvalue(), mimetype='image/png')
    return data


#
# API /adminStats/plotAge
# Returns a graph showing the average ave of customers
# Age groups considered: 18-24 / 25-35 / 36-50 / over50
#
@app.route('/adminStats/plotAge')
@variables.token_required_admin
def show_plot_age():
    database = connectionToMongo["dinerhub"]
    users = database["User"]
    critery = {"IsAdmin": False}
    data = {}

    # check if the system contains users
    count = users.count_documents(critery)
    if count == 0:
        # return a generic image
        data["link"] = baseUrl + "static/loading.png"
        return data

    # count_one :   18-24
    # count_two :   25-35
    # count_three : 36-50
    # count_four  : over50
    count_one, count_two, count_three, count_four = 0, 0, 0, 0

    for element in users.find(critery):
        birthday = element["BirthDate"]
        date_object = date.today()
        age = date_object.year - birthday.year
        if 18 <= age <= 24:
            count_one = count_one + 1
        elif 25 <= age <= 35:
            count_two = count_two + 1
        elif 36 <= age <= 50:
            count_three = count_three + 1
        else:
            count_four = count_four + 1

    # plot the graph
    x = [count_one, count_two, count_three, count_four]
    label = ["18-24", "25-35", "36-50", "Over50"]

    fig = plt.figure(figsize=(6, 6))
    ax = fig.add_axes([0.1, 0.1, 0.8, 0.8])
    explode = (0, 0.05, 0, 0)

    pies = ax.pie(x, explode=explode, labels=label, autopct='%1.1f%%')

    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    link = "plotAge.png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data
## return Response(output.getvalue(), mimetype='image/png')
