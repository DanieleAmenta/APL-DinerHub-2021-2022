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

@app.route('/userStats/countOrder/<UserId>')
def show_countOrder(UserId):
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    data = {}
    id = int(UserId)
    critery = {"UserId": id}
    count = orders.count_documents(critery)
    data["count"] = count
    return data

@app.route('/userStats/totalOrder/<UserId>')
def show_countTotal(UserId):
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    data = {}
    id = int(UserId)
    critery = {"UserId": id}
    count = 0
    check = orders.count_documents(critery)
    if check == 0:
        data["count"] = 0
        return data
    for order in orders.find(critery):
        count = count + order["Totals"]
    data["count"] = count
    return data

@app.route('/userStats/favoriteRestaurant/<UserId>')
def show_favoriteRestaurant(UserId):
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    restaurants = Database["Restaurant"]
    id = int(UserId)
    max = 0
    data = {}
    for restaurant in restaurants.find():
        count = 0
        idRestaurant = restaurant["RestaurantId"]
        critery = {"UserId": id, "RestaurantId": idRestaurant}
        count = orders.count_documents(critery)
        if count == 0:
            data["name"] = ""
            return data
        if count > max:
            favoriteRestaurantId = idRestaurant

    criteryId = {"RestaurantId": favoriteRestaurantId}
    Restaurant = restaurants.find_one(criteryId)
    data["name"] = Restaurant["Name"]
    return data

@app.route('/userStats/orderfordayofweek/<UserId>')
def show_orderfordayofweek(UserId):
    Database = connectionToMongo["dinerhub"]
    orders = Database["Order"]
    id = int(UserId)
    critery = {"UserId": id}
    countOne, countTwo, countThree, countFour, countFive, countSix, countSeven = 0, 0, 0, 0, 0, 0, 0
    check = orders.count_documents(critery)
    if check == 0:
        data["link"] = baseUrl + subFolder + "loading.png"
        return data
    for element in orders.find(critery):
        date = element["date"]
        day = date.weekday()
        i = date.day
        if day == 0:
            countOne = countOne + 1
        elif day == 1:
            countTwo = countTwo + 1
        elif day == 2:
            countThree = countThree + 1
        elif day == 3:
            countFour = countFour + 1
        elif day == 4:
            countFive = countFive + 1
        elif day == 5:
            countSix = countSix + 1
        elif day == 6:
            countSeven = countSeven + 1
    x = np.arange(7)
    countOrder = [countOne, countTwo, countThree, countFour, countFive, countSix, countSeven]
    fig, ax = plt.subplots()
    plt.bar(x, countOrder)
    plt.xticks(x, ('Lunedì', 'Martedì', 'Mercoledì', 'Giovedì', 'Venerdì', 'Sabato', 'Domenica'))
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    #return Response(output.getvalue(), mimetype='image/png')
    data = {}
    link = "orderfordayofweek" + UserId + ".png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data
@app.route('/userStats/orderCost/<UserId>')
def show_costOrder(UserId):
    connectionToMongo = pymongo.MongoClient("mongodb://localhost:27017/")
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    customerId = int(UserId)
    critery = {"UserId": customerId}
    x = []
    y = []
    i = 0
    check = collection.count_documents(critery)
    if check == 0:
        data["link"] = baseUrl + subFolder + "loading.png"
        return data
    for element in collection.find(critery):
        i = i + 1
        x.append(i)
        y.append(element["Totals"])

    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_axes([0.1, 0.1, 0.6, 0.8])
    ax.set_xlabel('Ordini')
    ax.set_ylabel('Costo Ordini')
    ax.plot(x, y)
    output = io.BytesIO()

    FigureCanvas(fig).print_png(output)
    #return Response(output.getvalue(), mimetype='image/png')
    data = {}
    link = "orderCost" + UserId + ".png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data
@app.route('/userStats/bestDish/<UserId>')
def show_bestUserDish(UserId):
    Database = connectionToMongo["dinerhub"]
    collection = Database["Order"]
    collectionDishes = Database["Dish"]
    id = int(UserId)
    critery = {"UserId": id}
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