import pymongo
import os
from datetime import date
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
import numpy as np
import io
import variables

connectionToMongo = pymongo.MongoClient("mongodb://localhost:27017/")

path = os.getcwd()
baseUrl = path.replace("\\", r'/') + '/'
subFolder = "RestaurantStats/"
isExist = os.path.exists(baseUrl + subFolder)
if not isExist:
    os.mkdir("RestaurantStats")
print(isExist)

from __main__ import app


#
# API /restaurantStats/orderReceived/<restaurant_id>
# Returns the number of orders receveid by a restaurant
#
@app.route('/restaurantStats/orderReceived/<restaurant_id>')
@variables.token_required_restaurant
def show_order_received(restaurant_id):
    database = connectionToMongo["dinerhub"]
    collection = database["Order"]
    restaurant_id_int = int(restaurant_id)
    critery = {"RestaurantId": restaurant_id_int}

    data = {}
    count = collection.count_documents(critery)

    # json_data = json.dumps(data, sort_keys=True, indent=3)
    # print(json_data)
    data["count"] = count
    return data


#
# API /restaurantStats/totalOrder/<restaurant_id>
# Returns the total revenue of a restaurant
#
@app.route('/restaurantStats/totalOrder/<restaurant_id>')
@variables.token_required_restaurant
def show_calculate_total(restaurant_id):
    database = connectionToMongo["dinerhub"]
    collection = database["Order"]
    totals = 0

    data = {}
    restaurant_id_int = int(restaurant_id)
    critery = {"RestaurantId": restaurant_id_int}
    count = collection.count_documents(critery)

    # if number of restaurants is zero, return a total cleared
    if count == 0:
        data["totalOrder"] = 0
        return data
    for element in collection.find(critery):
        totals = totals + element["Total"]

    data["totalOrder"] = 'E. ' + str(totals)
    # json_data = json.dumps(data, sort_keys=True, indent=3)
    # print(json_data)
    return data


#
# API /restaurantStats/bestCustomer/<restaurant_id>
# Returns the user who spent the most money in a restaurant
#
@app.route('/restaurantStats/bestCustomer/<restaurant_id>')
@variables.token_required_restaurant
def show_restaurant_best_customer(restaurant_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    users = database["User"]

    restaurant_id_int = int(restaurant_id)
    id = 0
    max_totals = 0
    data = {}
    customer_found = False

    check = users.count_documents({})
    # if number of users is zero, return an empty value
    if check == 0:
        data["Name"] = ""
        return data

    for element in users.find():
        id_customer = element["UserId"]
        critery = {"UserId": id_customer, "RestaurantId": restaurant_id_int}
        count = 0
        check = orders.count_documents(critery)

        # if number of orders is zero, skip to next iteration
        if check == 0:
            continue

        for x in orders.find(critery):
            count = count + x["Total"]
        if count > max_totals:
            # we found a new user who spent the most
            max_totals = count
            id = id_customer
            customer_found = True

    if customer_found:
        best_customer_id = {"UserId": id}
        best_customer = users.find_one(best_customer_id)
        data["Name"] = best_customer["Name"] + ' ' + best_customer["Surname"]
    else:
        data["Name"] = ""
    return data


#
# API /restaurantStats/plotAge/<restaurant_id>
# Returns a graph showing the average age of customers of a restaurant
#
@app.route('/restaurantStats/plotAge/<restaurant_id>')
@variables.token_required_restaurant
def show_plot_age_customer(restaurant_id):
    database = connectionToMongo["dinerhub"]
    users = database["User"]
    orders = database["Order"]
    restaurant_id_int = int(restaurant_id)
    critery = {"RestaurantId": restaurant_id_int}
    array = []
    data = {}
    count = orders.count_documents(critery)

    # check if this restaurant has orders
    if count == 0:
        # return a generic image
        data["link"] = baseUrl + "static/loading.png"
        return data
    for element in orders.find(critery):
        # put orders in an array if not already there
        user_id = element["UserId"]
        condition = user_id in array
        if not condition:
            array.append(user_id)

    # count_one :   18-24
    # count_two :   25-35
    # count_three : 36-50
    # count_four  : over50
    count_one, count_two, count_three, count_four = 0, 0, 0, 0

    for id in array:
        critery_one = {"UserId": id}

        # check if user exist
        count = users.count_documents(critery_one)
        if count == 0:
            continue

        user = users.find_one(critery_one)
        birthday = user["BirthDate"]
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
    # return Response(output.getvalue(), mimetype='image/png')

    link = "plotAge" + restaurant_id + ".png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data


#
# API /restaurantStats/plotOrderForHour/<restaurant_id>
# Returns a graph showing the time slot with the most receipts for a restaurant
# Time slots analyzed: 18-19 / 19-20 / 20-21 / 21-22 / 22-23 / 23-00
#
@app.route('/restaurantStats/plotOrderForHour/<restaurant_id>')
@variables.token_required_restaurant
def show_plot_order_for_hour_restaurant(restaurant_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    restaurant_id_int = int(restaurant_id)
    critery = {"RestaurantId": restaurant_id_int}
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

    for element in orders.find(critery):
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
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    # return Response(output.getvalue(), mimetype='image/png')
    data = {}
    link = "plotOrderForHour" + restaurant_id + ".png"
    plt.savefig(subFolder + link, dpi=50)
    data["link"] = baseUrl + subFolder + link
    return data


#
# API /restaurantStats/customer/<restaurant_id>
# Returns the number of customers who placed their order in a restaurant
#
@app.route('/restaurantStats/customer/<restaurant_id>')
@variables.token_required_restaurant
def show_customer(restaurant_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    id = int(restaurant_id)
    critery = {"RestaurantId": id}
    array = []
    data = {}

    # check if the system contains orders
    check = orders.count_documents(critery)
    if check == 0:
        # return a generic image
        data["Customers"] = 0
        return data

    for element in orders.find(critery):
        # put users in an array if not already there
        userId = element["UserId"]
        condition = userId in array
        if not condition:
            array.append(userId)

    customers = len(array)
    data["Customers"] = customers
    return data


#
# API /restaurantStats/bestDish/<restaurant_id>
# Returns the the best-selling dish of a restaurant
#
@app.route('/restaurantStats/bestDish/<restaurant_id>')
@variables.token_required_restaurant
def show_best_dish(restaurant_id):
    database = connectionToMongo["dinerhub"]
    orders = database["Order"]
    collection_dishes = database["Dish"]
    restaurant_id_int = int(restaurant_id)
    critery = {"RestaurantId": restaurant_id_int}

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
        # print(order_dishes)
        for dishes in order_dishes:
            # adds up the quantities of dishes sold
            dish = dishes["Dish"]
            dish_id = dish["DishId"]
            quantity = dishes["quantity"]
            check = dish_id in dish_dictionary
            if check:
                dish_dictionary[dish_id] = dish_dictionary[dish_id] + quantity
            else:
                dish_dictionary[dish_id] = quantity

    # find the best-selling product
    for key in dish_dictionary.keys():
        if dish_dictionary[key] > count_dish:
            count_dish = dish_dictionary[key]
            critery_dish = {"DishId": key}
            best_dish = collection_dishes.find_one(critery_dish)

    data["name"] = best_dish["Name"]
    return data
