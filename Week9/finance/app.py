import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if session.get("user_id"):
        stocks = db.execute("SELECT symbol, name, shares, price, total FROM stocks WHERE user_id = ?", session["user_id"])
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if not stocks:
            return render_template("index.html", stocks=[], cash=usd(cash), Total=usd(cash))
        for i in range(len(stocks)):
            stocks[i]["price"] = usd(stocks[i]["price"])
            stocks[i]["total"] = usd(stocks[i]["total"])
        Total = db.execute("SELECT user_id, SUM(total) AS Total FROM stocks WHERE user_id = ? GROUP BY user_id", session["user_id"])[0]["Total"]

        return render_template("index.html", stocks=stocks, cash=usd(cash), Total=usd(Total + cash))
    return redirect("/login")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Symbol is blank.")
        if not lookup(symbol):
            return apology("Symbol doesn't exist.")

        def check_integer():
            for i in shares:
                if not i.isdigit():
                    return False
            if int(shares) == 0:
                return False
            return True

        if not check_integer():
            return apology("Enter a positive Integer in shares.")

        shares = int(shares)
        look_up = lookup(symbol)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if cash < look_up["price"] * shares:
            return apology("Cash is not enough to buy stocks.")

        cash -= look_up["price"] * shares

        now = datetime.now()
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        db.execute("INSERT INTO history (user_id, type, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], "buy", look_up["symbol"], shares, look_up["price"],
        now.strftime("%Y/%m/%d %H:%M:%S"))
        symbols = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = ?", session["user_id"])

        def check_symbol():
            for i in symbols:
                if i["symbol"] == look_up["symbol"]:
                    return i
            return False

        if check_symbol():
            db.execute("UPDATE stocks SET name = ?, shares = ?, price = ?, total = ? WHERE user_id = ? AND symbol = ?", look_up["name"], shares + check_symbol()["shares"], look_up["price"], look_up["price"] * (shares + check_symbol()["shares"]),
            session["user_id"], look_up["symbol"])
        else:
            db.execute("INSERT INTO stocks (user_id, symbol, name, shares, price, total) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], look_up["symbol"], look_up["name"], shares, look_up["price"], shares * look_up["price"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE user_id = ? ORDER BY id DESC", session["user_id"])
    return render_template("history.html", history=history)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("symbol is blank")
        if not lookup(symbol):
            return apology("symbol doesn't exist")

        look_up = lookup(symbol)
        return render_template("quoted.html", name=look_up["name"], price=usd(look_up["price"]), symbol=look_up["symbol"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        usernames = db.execute("SELECT username FROM users")
        if not username:
            return apology("Username is blank")
        for user in usernames:
            if username == user["username"]:
                return apology("Username already exists")

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not password or not confirmation:
            return apology("Password is blank")
        if password != confirmation:
            return apology("Password is not same with second input")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("You didn't enter the symbol.")
        if not shares:
            return apology("You didn't enter shares.")

        def check_integer():
            for i in shares:
                if not i.isdigit():
                    return False
            if int(shares) == 0:
                return False
            return True

        if not check_integer():
            return apology("Shares are not a valid number or Shares are zero.")

        shares = int(shares)
        actual_shares = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["shares"]
        if actual_shares == 0:
            return apology("The stock shares are zero")
        if shares > actual_shares:
            return apology("There aren't enough shares of that stock.")

        stock = lookup(symbol)
        now = datetime.now()
        db.execute("UPDATE stocks SET shares = ?, total = ? WHERE user_id = ? AND symbol = ?", actual_shares - shares, stock["price"] * (actual_shares - shares), session["user_id"], stock["symbol"])
        db.execute("INSERT INTO history (user_id, type, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], "sell", stock["symbol"], shares, stock["price"],
        now.strftime("%Y/%m/%d %H:%M:%S"))
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + shares * stock["price"], session["user_id"])
        return redirect("/")
    else:
        symbols = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", symbols=symbols)