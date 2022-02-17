from flask import Flask

app = Flask(__name__)

import RestaurantStats
import UserStats
import AdminStats


# pip install pyjwt
@app.route('/ping')
def show_online():
    hello = "Hello DinerHub is online, Enjoy!"
    return f'{hello}'


if __name__ == "__main__":
    app.run()
