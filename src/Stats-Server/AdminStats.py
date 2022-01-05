import pymongo
from datetime import datetime, date
from flask import Response
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
import numpy as np
import io
import json

connectionToMongo = pymongo.MongoClient("mongodb://localhost:27017/")
softwareStartDate = date(2021, 12, 7)
baseUrl = "C:/Users/danie/Desktop/definitivo/APL-DinerHub-2021-2022/src/Stats-Server/"
subFolder = "images/"


from __main__ import app
#all customer in application
@app.route('/adminStats/allUsers')
def show_users():
    Database = connectionToMongo["dinerhub"]
    collection = Database["User"]
    critery = {"IsAdmin": False}
    data = {}
    count = collection.count_documents(critery)
    data["count"] = count
    return data

#count total order all time
@app.route('/adminStats/totalOrder')
def show_totalOrder():
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    data = {}
    count = collection.count_documents({})
    data["count"] = count
    return data

#count total order price
@app.route('/adminStats/totals')
def show_totals():
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    totals = 0
    data = {}
    count = collection.count_documents({})
    if count == 0:
        data["total"] = 0
        return data
    for element in collection.find():
        totals = totals + element["Totals"]
    data["total"] = totals
    return data

#avg daily orders
@app.route('/adminStats/dailyOrders')
def show_dailyOrders():
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    data = {}
    count = collection.count_documents({})
    date_object = date.today()
    daysOfActivity = date_object - softwareStartDate
    daysCount = daysOfActivity.days
    average = count / daysCount
    data["average"] = int(average)
    return data

#customer who spend much money
@app.route('/adminStats/bestCustomer')
def show_bestCustomer():
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    users = Database["User"]
    ID = 0
    maxTotals = 0
    data = {}
    check = users.count_documents({})
    if check == 0:
        data["name"] = ""
        return data
    for element in users.find():
        idCustomer = element["UserId"]
        critery = {"UserId": idCustomer}
        checkTwo = users.count_documents(critery)
        if checkTwo == 0:
            data["name"] = ""
            return data
        count = 0
        for x in orders.find(critery):
            count = count + x["Totals"]
        if count > maxTotals:
            maxTotals = count
            ID = idCustomer
    bestCustomerID = {"UserId": ID}
    bestCustomer = users.find_one(bestCustomerID)
    data["name"] = bestCustomer["Name"]
    return data

@app.route('/adminStats/bestCustomerOfMonth')
def show_bestCustomerMonth():
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    users = Database["User"]
    date_object = date.today()
    currentMonth = date_object.month
    ID = 0
    maxTotals = 0
    data = {}
    check = users.count_documents({})
    if check == 0:
        data["name"] = ""
        return data
    for element in users.find():
        idCustomer = element["UserId"]
        critery = {"UserId": idCustomer}
        count = 0
        checkTwo = orders.count_documents(critery)
        if checkTwo == 0:
            data["name"] = ""
            return data
        for order in orders.find(critery):
            today = order["date"]
            month = today.month
            if month == currentMonth:
                count = count + order["Totals"]
                if count > maxTotals:
                    maxTotals = count
                    ID = idCustomer
    bestCustomerID = {"UserId": ID}
    bestCustomer = users.find_one(bestCustomerID)
    print(bestCustomer)
    data["name"] = bestCustomer["Name"]
    return data


@app.route('/adminStats/topgrossing')
def show_topGrossing():
    Database = connectionToMongo["dinerhub"]
    collection = Database["Restaurant"]
    ID = 0
    maxTotals = 0
    data = {}
    check = collection.count_documents({})
    if check == 0:
        data["name"] = ""
        return data
    for element in collection.find():
        idRestaurant = element["RestaurantId"]
        order = Database["Order"]
        critery = {"RestaurantId": idRestaurant}
        checkTwo = order.count_documents(critery)
        if checkTwo == 0:
            data["name"] = ""
            return data
        count = 0
        for x in order.find(critery):
            count = count + x["Totals"]
        if count > maxTotals:
            maxTotals = count
            ID = idRestaurant
    bestRestaurant = {"RestaurantId": ID}
    Restaurant = collection.find_one(bestRestaurant)
    name = Restaurant["Name"]
    data["name"] = name
    return data
import base64

@app.route('/adminStats/plotOrdersForHour')
def show_plotOrderForHour():
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    data = {}
    countOne, countTwo, countThree, countFour, countFive, countSix = 0, 0, 0, 0, 0, 0
    check = orders.count_documents({})
    if check == 0:
        data["link"] = baseUrl + subFolder + "loading.png"
        return data
    for element in orders.find():
        date = element["date"]
        hour = date.hour
        if hour == 18:
            countOne = countOne + 1
        elif hour == 19:
            countTwo = countTwo + 1
        elif hour == 20:
            countThree = countThree + 1
        elif hour == 21:
            countFour = countFour + 1
        elif hour == 22:
            countFive = countFive + 1
        elif hour == 23:
            countSix = countSix + 1
    x = np.arange(6)
    countOrder = [countOne, countTwo, countThree, countFour, countFive, countSix]
    fig, ax = plt.subplots()
    plt.bar(x, countOrder)
    plt.xticks(x, ('18', '19', '20', '21', '22', '23'))
    link = 'plotOrdersForHour.png'
    plt.savefig(subFolder + link, dpi = 50)
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    data["link"] = baseUrl + subFolder + link
    #my_stringIObytes = io.BytesIO()
    #plt.savefig(my_stringIObytes, format='jpg')
    #my_stringIObytes.seek(0)
    #my_base64_jpgData = base64.b64encode(my_stringIObytes.read())
    #data = {}
    #data["test"] = my_base64_jpgData
    #return my_base64_jpgData
   # return Response(output.getvalue(), mimetype='image/png')
    return data
# Age Customer
@app.route('/adminStats/plotAge')
def show_plotAge():
    # 18-24 25-35 36-50 over50
    Database = connectionToMongo["dinerhub"]
    collection = Database["User"]
    critery = {"IsAdmin": False}
    data = {}
    count = collection.count_documents(critery)
    if count == 0:
        data["link"] = baseUrl + subFolder + "loading.png"
        return data
    countOne, countTwo, countThree, countFour, CountFive = 0, 0, 0, 0, 0
    for element in collection.find(critery):
        birthday = element["BirthDate"]
        date_object = date.today()
        age = date_object.year - birthday.year
        if age < 24:
            countOne = countOne + 1
        elif age >= 25 and age <= 35:
            countTwo = countTwo + 1
        elif age >= 36 and age <= 50:
            countThree = countThree + 1
        else:
            countFour = countFour + 1
    x = [countOne, countTwo, countThree, countFour]
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