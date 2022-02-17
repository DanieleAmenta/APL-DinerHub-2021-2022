import pymongo
import os
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
import numpy as np
import io
import variables

connectionToMongo = pymongo.MongoClient("mongodb://localhost:27017/")

path = os.getcwd()
baseUrl = path.replace("\\", r'/') + '/'
subFolder = "UserStats/"
isExist = os.path.exists(baseUrl + subFolder)
if not isExist:
    os.mkdir("UserStats")
print(isExist)

from __main__ import app


#
# API /userStats/countOrder/<user_id>
# Returns the number of orders placed by an users
#
@app.route('/userStats/countOrder/<user_id>')
@variables.token_required_user
def show_count_order(user_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    users = database["User"]
    data = {}
    id = int(user_id)
    critery = {"UserId": id}

    check = users.count_documents({})
    # if number of users is zero, return an empty value
    if check == 0:
        data["name"] = ""
        return data

    count = orders.count_documents(critery)
    data["count"] = count
    return data


#
# API /userStats/totalOrder/<user_id>
# Returns money spent by a customer
#
@app.route('/userStats/totalOrder/<user_id>')
@variables.token_required_user
def show_count_total(user_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    users = database["User"]
    data = {}

    id = int(user_id)
    critery = {"UserId": id}
    count = 0

    # if number of orders is zero or user not exists, return an empty value
    check = orders.count_documents(critery)
    second_check = users.count_documents(critery)
    if check == 0 and second_check == 0:
        data["count"] = 0
        return data
    for order in orders.find(critery):
        count = count + order["Total"]

    data["count"] = 'E. ' + str(count)
    return data


#
# API /userStats/favoriteRestaurant/<user_id>
# Returns a customer's favorite restaurant
#
@app.route('/userStats/favoriteRestaurant/<user_id>')
@variables.token_required_user
def show_favorite_restaurant(user_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    restaurants = database["Restaurant"]

    id = int(user_id)
    max = 0
    data = {}
    found_restaurant = False

    check = restaurants.count_documents({})
    # if number of restaurants is zero, return an empty value
    if check == 0:
        data["name"] = ""
        return data

    for restaurant in restaurants.find():
        id_restaurant = restaurant["RestaurantId"]
        critery = {"UserId": id, "RestaurantId": id_restaurant}
        count = orders.count_documents(critery)
        # if number of orders is zero, return an empty value
        if count == 0:
            continue
        if count > max:
            # we found a new customer's favorite restaurant
            favorite_restaurant_id = id_restaurant
            found_restaurant = True

    if found_restaurant:
        critery_id = {"RestaurantId": favorite_restaurant_id}
        restaurant = restaurants.find_one(critery_id)
        data["name"] = restaurant["Name"]
    else:
        data["name"] = ""

    return data

#
# API /userStats/orderfordayofweek/<user_id>
# Returns a graph showing the orders for day of week
#
@app.route('/userStats/orderfordayofweek/<user_id>')
@variables.token_required_user
def show_order_for_day_of_week(user_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    data = {}

    id = int(user_id)
    critery = {"UserId": id}

    # check if the system contains orders
    check = orders.count_documents(critery)
    if check == 0:
        # return a generic image
        data["link"] = baseUrl + "static/loading.png"
        return data

    count_monday, count_tuesday, count_wednesday, count_thursday = 0, 0, 0, 0
    count_friday, count_saturday, count_sunday = 0, 0, 0

    for element in orders.find(critery):
        date = element["Date"]
        day = date.weekday()
        i = date.day
        if day == 0:
            count_monday = count_monday + 1
        elif day == 1:
            count_tuesday = count_tuesday + 1
        elif day == 2:
            count_wednesday = count_wednesday + 1
        elif day == 3:
            count_thursday = count_thursday + 1
        elif day == 4:
            count_friday = count_friday + 1
        elif day == 5:
            count_saturday = count_saturday + 1
        elif day == 6:
            count_sunday = count_sunday + 1

    # plot the graph
    x = np.arange(7)
    count_order = [count_monday, count_tuesday, count_wednesday, count_thursday, count_friday, count_saturday,
                   count_sunday]
    fig, ax = plt.subplots()
    plt.bar(x, count_order)
    plt.xticks(x, ('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday'))
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    # return Response(output.getvalue(), mimetype='image/png')
    data = {}
    link = "orderfordayofweek" + user_id + ".png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data


#
# API /userStats/orderCost/<user_id>
# Returns a graph showing the comparison between the order total
#
@app.route('/userStats/orderCost/<user_id>')
@variables.token_required_user
def show_cost_order(user_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    data = {}

    customer_id = int(user_id)
    critery = {"UserId": customer_id}
    x = []
    y = []
    i = 0

    # check if the system contains orders
    check = orders.count_documents(critery)
    if check == 0:
        # return a generic image
        data["link"] = baseUrl + "static/loading.png"
        return data

    for element in orders.find(critery):
        i = i + 1
        x.append(i)
        y.append(element["Total"])

    # plot the graph
    fig = plt.figure(figsize=(6, 4))
    ax = fig.add_axes([0.1, 0.1, 0.6, 0.8])
    ax.set_xlabel('Orders')
    ax.set_ylabel('Orders Totals')
    ax.plot(x, y)
    output = io.BytesIO()

    FigureCanvas(fig).print_png(output)
    # return Response(output.getvalue(), mimetype='image/png')
    data = {}
    link = "orderCost" + user_id + ".png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data


#
# API /userStats/bestDish/<user_id>
# Returns the dish most ordered by a user
#
@app.route('/userStats/bestDish/<user_id>')
@variables.token_required_user
def show_best_user_dish(user_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    dish_collection = database["Dish"]

    id = int(user_id)
    critery = {"UserId": id}
    count_dish = 0
    best_dish = 0
    dish_dictionary = {}
    data = {}

    # check if the system contains orders
    count = orders.count_documents(critery)
    if count == 0:
        # return an empty value
        data["id"] = ""
        return data

    for element in orders.find(critery):
        order_dishes = element["Dishes"]
        for dishes in order_dishes:
            # adds up the quantities of dishes bought
            dish = dishes["Dish"]
            dish_id = dish["DishId"]
            quantity = dishes["quantity"]
            check = dish_id in dish_dictionary
            if check:
                dish_dictionary[dish_id] = dish_dictionary[dish_id] + quantity
            else:
                dish_dictionary[dish_id] = quantity

    # find the dish most ordered by the user
    for key in dish_dictionary.keys():
        if dish_dictionary[key] > count_dish:
            count_dish = dish_dictionary[key]
            critery_dish = {"DishId": key}
            best_dish = dish_collection.find_one(critery_dish)

    data["name"] = best_dish["Name"]
    return data
