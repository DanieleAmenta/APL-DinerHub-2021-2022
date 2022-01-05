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

@app.route('/restaurantStats/orderReceived/<RestaurantId>')
def show_orderReceived(RestaurantId):
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    restaurantId = int(RestaurantId)
    critery = {"RestaurantId": restaurantId}
    array = []
    data = {}
    count = collection.count_documents(critery)
    #json_data = json.dumps(data, sort_keys=True, indent=3)
    #print(json_data)
    data["count"] = count
    return data

@app.route('/restaurantStats/totalOrder/<RestaurantId>')
def show_calculateTotal(RestaurantId):
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    totals = 0
    data = {}
    restaurantId = int(RestaurantId)
    critery = {"RestaurantId": restaurantId}
    count = collection.count_documents(critery)
    if count == 0:
        data["totalOrder"] = 0
        return data
    for element in collection.find(critery):
        totals = totals + element["Totals"]
    data["totalOrder"] = totals
    #json_data = json.dumps(data, sort_keys=True, indent=3)
    #print(json_data)
    return data

@app.route('/restaurantStats/bestCustomer/<RestaurantId>')
def show_restaurantBestCustomer(RestaurantId):
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    users = Database["User"]
    id = int(RestaurantId)
    ID = 0
    maxTotals = 0
    data = {}
    for element in users.find():
        idCustomer = element["UserId"]
        critery = {"UserId": idCustomer, "RestaurantId": id}
        count = 0
        check = orders.count_documents(critery)
        if check == 0:
            data["Name"] = ""
            data["Surname"] = ""
            return data
        for x in orders.find(critery):
            count = count + x["Totals"]
        if count > maxTotals:
            maxTotals = count
            ID = idCustomer
    bestCustomerID = {"UserId": ID}
    bestCustomer = users.find_one(bestCustomerID)
    data["Name"] = bestCustomer["Name"]
    data["Surname"] = bestCustomer["Surname"]
    return data

@app.route('/restaurantStats/plotAge/<RestaurantId>')
def show_plotAgeCustomer(RestaurantId):
    Database = connectionToMongo["dinerhub"]
    collection = Database["User"]
    orders = Database["Order"]
    id = int(RestaurantId)
    countOne, countTwo, countThree, countFour = 0, 0, 0, 0
    criteryTwo = {"RestaurantId": id}
    array = []
    data = {}
    count = orders.count_documents(criteryTwo)
    if count == 0:
        data["link"] = baseUrl + subFolder + "loading.png"
        return data
    for element in orders.find(criteryTwo):
        userId = element["UserId"]
        condition = userId in array
        if condition == False:
            array.append(userId)

    for id in array:
        # toDo controllare se esiste
        criteryOne = {"UserId": id}
        element = collection.find_one(criteryOne)
        birthday = element["BirthDate"]
        date_object = date.today()
        age = date_object.year - birthday.year
        # todo fare con switch
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
    #return Response(output.getvalue(), mimetype='image/png')

    link = "plotAge" + RestaurantId + ".png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data
@app.route('/restaurantStats/plotOrderForHour/<RestaurantId>')
def show_plotOrderForHourRestaurant(RestaurantId):
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    id = int(RestaurantId)
    critery = {"RestaurantId": id}
    countOne, countTwo, countThree, countFour, countFive, countSix = 0, 0, 0, 0, 0, 0
    for element in orders.find(critery):
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
    #return Response(output.getvalue(), mimetype='image/png')
    data = {}
    link = "plotOrderForHour" + RestaurantId + ".png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data
@app.route('/restaurantStats/customer/<RestaurantId>')
def show_customer(RestaurantId):
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    id = int(RestaurantId)
    critery = {"RestaurantId": id}
    array = []
    data = {}
    check = collection.count_documents(critery)
    if check == 0:
        data["Customers"] = 0
        return data
    for element in collection.find(critery):
        userId = element["UserId"]
        condition = userId in array
        if condition == False:
            array.append(userId)
    customers = len(array)
    data["Customers"] = customers
    return data

@app.route('/restaurantStats/bestDish/<RestaurantId>')
def show_bestDish(RestaurantId):
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    collectionDishes = Database["Dish"]
    id = int(RestaurantId)
    critery = {"RestaurantId": id}
    countDish = 0
    bestDish = 0
    dishDictionary = {}
    data = {}
    count = collection.count_documents(critery)
    if count == 0:
        data["id"] = ""
        return data
    for element in collection.find(critery):
       orderDishes = element["Dishes"]
       print(orderDishes)
       for dishes in orderDishes:
          dish = dishes["Dish"]
          dishId = dish["DishId"]
          quantity = dishes["quantity"]
          check = dishId in dishDictionary
          if check == True:
              dishDictionary[dishId] = dishDictionary[dishId] + quantity
          else:
              dishDictionary[dishId] = quantity
    for key in dishDictionary.keys():
        if dishDictionary[key] > countDish:
            countDish = dishDictionary[key]
            criteryDish = {"DishId" : key}
            bestDish = collectionDishes.find_one(criteryDish)
    data["id"] = bestDish["DishId"]
    return data