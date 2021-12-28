import pymongo
from datetime import datetime, date
from flask import Response
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
import numpy as np
import io
connectionToMongo = pymongo.MongoClient("mongodb://localhost:27017/")
softwareStartDate = date(2021, 12, 7)

from __main__ import app
#all customer in application
@app.route('/adminStats/allUsers')
def show_users():
    Database = connectionToMongo["dinerhub"]
    collection = Database["User"]
    critery = {"IsAdmin": False}
    count = collection.count_documents(critery)
    return f'{count}'

#count total order all time
@app.route('/adminStats/totalOrder')
def show_totalOrder():
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    count = collection.count_documents({})
    return f'{count}'

#count total order price
@app.route('/adminStats/totals')
def show_totals():
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    totals = 0
    for element in collection.find():
        totals = totals + element["Totals"]
    return str(totals)

#avg daily orders
@app.route('/adminStats/dailyOrders')
def show_dailyOrders():
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    count = collection.count_documents({})
    date_object = date.today()
    daysOfActivity = date_object - softwareStartDate
    daysCount = daysOfActivity.days
    average = count / daysCount
    return f'{int(average)}'

#customer who spend much money
@app.route('/adminStats/bestCustomer')
def show_bestCustomer():
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    users = Database["User"]
    ID = 0
    maxTotals = 0
    for element in users.find():
        idCustomer = element["UserId"]
        critery = {"UserId": idCustomer}
        count = 0
        for x in orders.find(critery):
            count = count + x["Totals"]
        if count > maxTotals:
            maxTotals = count
            ID = idCustomer
    bestCustomerID = {"UserId": ID}
    bestCustomer = users.find_one(bestCustomerID)

    return f'{bestCustomer}'

@app.route('/adminStats/bestCustomerOfMonth')
def show_bestCustomerMonth():
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    users = Database["User"]
    date_object = date.today()
    currentMonth = date_object.month
    ID = 0
    maxTotals = 0
    for element in users.find():
        idCustomer = element["UserId"]
        critery = {"UserId": idCustomer}
        count = 0
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

    return f'{bestCustomer}'


@app.route('/adminStats/topgrossing')
def show_topGrossing():
    Database = connectionToMongo["dinerhub"]
    collection = Database["Restaurant"]
    ID = 0
    maxTotals = 0
    for element in collection.find():
        idRestaurant = element["id"]
        order = Database["Order"]
        critery = {"RestaurantId": idRestaurant}
        count = 0
        for x in order.find(critery):
            count = count + x["Totals"]
        if count > maxTotals:
            maxTotals = count
            ID = idRestaurant
    bestRestaurant = {"id": ID}
    Restaurant = collection.find_one(bestRestaurant)
    name = Restaurant["name"]
    return f'{name}'

@app.route('/adminStats/plotOrdersForHour')
def show_plotOrderForHour():
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    countOne, countTwo, countThree, countFour, countFive, countSix = 0, 0, 0, 0, 0, 0
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
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    return Response(output.getvalue(), mimetype='image/png')

# Age Customer
@app.route('/adminStats/plotAge')
def show_plotAge():
    # 18-24 25-35 36-50 over50
    Database = connectionToMongo["dinerhub"]
    collection = Database["User"]
    critery = {"IsAdmin": False}
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
    return Response(output.getvalue(), mimetype='image/png')