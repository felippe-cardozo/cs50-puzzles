from cs50 import SQL
from passlib.apps import custom_app_context as pwd_context
from helpers import *
from application import *


db = SQL("sqlite:///finance.db")


def valid_username(username):
    if len(username.strip()) == 0:
        return False
    rows = db.execute("SELECT * FROM users WHERE username = :name",
                      name=username)
    return len(rows) != 1


def valid_pass(pwd, confirm):
    return pwd == confirm


def user_create(username, pwd):
    pwd = pwd_context.hash(pwd)
    db.execute("INSERT INTO users(username, hash) VALUES (:user, :password)",
               user=username, password=pwd)


def current_user():
    user = db.execute("SELECT * FROM users WHERE id = :id",
                      id=session["user_id"])
    return user[0]


def add_transaction(user_id, quote_name, n_of_shares, price):
    if n_of_shares > 0:
        t = 'bought'
    else:
        t = 'sold'
    db.execute("INSERT INTO transactions (user_id, quote, shares, price, type)\
               VALUES (:user, :quote, :shares, :p, :t)",
               user=user_id, quote=quote_name, shares=n_of_shares, p=price, t=t)


def charge(user, price):
    cash = user["cash"] - price
    db.execute("UPDATE users SET cash = :cash WHERE id = :id", id=user["id"], cash=cash)


def load_transactions(user, quote='all'):
    if quote == 'all':
        return db.execute("SELECT * FROM transactions WHERE user_id = :id", id=user["id"])
    return db.execute("SELECT * FROM transactions WHERE user_id = :id and quote = :quote",
                      id=user["id"], quote=quote)


def update_portfolio(user, quote, shares):
    portifolio = db.execute("SELECT * FROM portfolios WHERE user_id = :id and quote = :quote",
                            id=user["id"], quote=quote)
    if not portifolio:
        db.execute("INSERT INTO PORTFOLIOS (user_id, quote, shares) VALUES (:user, :quote, :shares)",
                   user=user["id"], quote=quote, shares=shares)
        return
    shares_sum = portifolio["shares"] + shares
    db.execute("UPDATE portfolios SET shares = :shares WHERE user_id = :user and quote = :quote",
               user=user["id"], quote=quote, shares=shares_sum)


def load_portfolios(user):
    return db.execute("SELECT * FROM portfolios WHERE user_id = :id",
                      id=user["id"])


def set_prices(port):
    prices = dict()
    for i in port:
        l = lookup(i['quote'])
        prices[i['quote']] = l['price']
    return prices


def sell_stock(user, stock, n):
    price = lookup(stock)['price']
    add_transaction(user["id"], stock, n * -1, price)
    remove_portfolio(user, stock, n)
    add_cache(user, price * n)


def add_cache(user, value):
    cash = user["cash"] + value
    db.execute("UPDATE users SET cash = :cash WHERE user_id = :id",
               cash=cash, id=user["id"])


def remove_portfolio(user, stock, n):
    port = db.execute("SELECT * FROM portfolios WHERE user_id = :user and quote = :quote",
                      user=user["id"], quote=stock)
    if port[0]["shares"] == n:
        db.execute("DELETE FROM portfolios WHERE user_id = :user and quote = :quote",
                   user=user["id"], quote=stock)
        return
    if port[0]["shares"] > n:
        new_shares = port[0]["shares"] - n
        db.execute("UPDATE portfolios SET shares = :shares\
                   WHERE user_id = :user and quote = :quote",
                   shares=new_shares, user=user["id"], quote=stock)
        return
