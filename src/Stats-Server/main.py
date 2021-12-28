from flask import Flask
app = Flask(__name__)
import RestaurantStats
import UserStats
import AdminStats

@app.route('/')
def show_Online():
    hello = "Hello DinerHub is online!,Enjoy"
    return f'{hello}'

if __name__ == "__main__":
    app.run()