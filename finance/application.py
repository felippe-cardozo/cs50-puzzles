from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *
from controller_helper import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    user = current_user()
    port = load_portfolios(user)
    if port:
        prices = set_prices(port)
        investment = sum([prices[k] for k, v in prices.items()])
        total = investment + int(user["cash"])
        return render_template("index.html",
                               port=port, user=user,
                               prices=prices, investment=investment,
                               total=total)
    return apology("You don't have any stocks yet!")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        quote = lookup(request.form.get("stock"))
        if not quote:
            return apology("Quote not found")
        try:
            shares = int(request.form.get("nshares"))
        except ValueError:
            return apology("Shares must be an integer")
        user = current_user()
        if user["cash"] < shares * quote["price"]:
            return apology("Not enough money")
        else:
            quote_symbol = request.form.get("stock")
            add_transaction(user["id"], quote_symbol, shares, quote["price"])
            charge(user, quote["price"] * shares)
            update_portfolio(user, quote_symbol, shares)
            return redirect(url_for("index"))

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    user = current_user()
    history = load_transactions(user)
    history = list(reversed(history))
    if history:
        return render_template("history.html", history=history)
    return apology("You dont have a history")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stock_symbol = request.form.get("stock")
        quote = lookup(stock_symbol)
        if not quote:
            return apology("Quote not found")
        return render_template("quoted.html", q=quote)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        password_con = request.form.get("password_confirmation")
        if valid_username(username) and valid_pass(password, password_con):
            user_create(username, password)
            user_row = db.execute("select * from users where username = :user",
                                  user=username)
            session["user_id"] = user_row[0]["id"]
            return redirect(url_for("index"))
        if not valid_username(username):
            return apology("Username already taken")
        return apology("Passwords don't match")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    user = current_user()
    port = load_portfolios(user)
    if not port:
        return apology("You do not have any stocks yet")
    prices = set_prices(port)
    investment = sum([prices[k] for k, v in prices.items()])
    total = investment + int(user["cash"])
    if request.method == "POST":
        stock = request.form.get("stock")
        quantity = request.form.get("quantity")
        try:
            quantity = int(quantity)
        except ValueError:
            return apology("Shares must be an integer")
        if quantity <= [i['shares'] for i in port if i['quote'] == stock][0]:
            sell_stock(user, stock, quantity)
            return redirect(url_for("sell"))
        else:
            return apology("You do not have that many shares")
    return render_template("sell.html",
                           user=user, port=port, prices=prices,
                           investment=investment, total=total)


