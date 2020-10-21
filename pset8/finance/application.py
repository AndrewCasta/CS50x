import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from pprint import pprint

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # symbols (for sell)
    symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", session["user_id"])

    # API key for look-up
    api_key = os.environ.get("API_KEY")

    # cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # users transaction data
    statement = db.execute("SELECT user_id, symbol, SUM(shares)  FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    # AND TOTAL position
    total = cash
    # calc TOTAL & add extra data into statement dict for frontend
    for line in statement:
        line["name"] = lookup(line["symbol"]).get("name")
        line["price"] = lookup(line["symbol"]).get("price")
        line["total"] = round(line["price"] * line["SUM(shares)"],2)
        total +=  line["total"]

    return render_template("index.html", statement=statement, cash=round(cash,2), total=round(total,2), symbols=symbols, api_key=api_key)

# API call to get the symbol data from server
@app.route("/symbol")
@login_required
def get_symbol():
    symbol = request.args.get("symbol")
    print(symbol)

    return lookup(symbol)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Page where user user can buy stock
    if request.method == "GET":
        return render_template("buy.html")

    # execute purchase of shares

    # get symbol and amount of shares
    if request.method == "POST":
        symbol = request.form.get("symbol")
        symbol = lookup(symbol).get("symbol")
        shares = request.form.get("shares")
        price = lookup(symbol).get("price")

        # error if symbol is none
        if lookup(symbol) == None:
            return apology("Symbol doesn't exist, try again")

        # ensure positive int is input for shares
        if int(shares) < 1:
            return apology("must purchase at least 1 share")

        # check user's cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]["cash"]
        # calc cost of the transaction
        cost = int(shares) * price

        # check user has enough cash to purchase
        if cash < cost:
            return apology("need additional dollars bby")

        # update transactions
        # add row to db
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, shares, price)

        # update user cash
        balance = cash - cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])

        return redirect("/")





@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT symbol, shares, price, datetime FROM transactions WHERE user_id = ?", session["user_id"])

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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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

    # GET - form to request quote
    if request.method == "GET":
        return render_template("quote.html")

    # POST - submit form to lookup() and display results on page
    symbol = request.form.get("symbol")
    symbol = lookup(symbol)

    # Hadnle - return None, when value wasn't provided correctly
    if symbol == None:
        return apology("Symbol does not exist. Check https://iextrading.com/trading/eligible-symbols/ for more symbols")

    # return to quoted page
    return render_template("quoted.html", name=symbol["name"], symbol=symbol["symbol"], price=symbol["price"])





@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        # get username, password & checkpassword from the form
        username = request.form.get("username")
        password = request.form.get("password")
        passwordCheck = request.form.get("passwordCheck")

        # errors:
        # if fields not filled in
        if not username or not password or not passwordCheck:
            return apology("please provide all fields")
        # if username already taken (check db)
        userCheck = db.execute("SELECT * FROM users WHERE username = ? ", username)
        if len(userCheck) != 0:
            return apology("username already exists, please pick another")
        # if passwords don't match
        if password != passwordCheck:
            return apology("passwords don't match, please try again")

        # insert new user into db (generate_password_hash)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?) ", username, generate_password_hash(password))

        # log user in (check logged_in helper)
        userId = db.execute("SELECT id FROM users WHERE username = ? ", username)
        session["user_id"] = userId[0]["id"]

        # redirect to index
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # get - serve page
    if request.method == "GET":
        symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", session["user_id"])

        return render_template("sell.html", symbols=symbols)

    # post - handle selling of stock
    if request.method == "POST":

        symbol = request.form.get("symbol")
        symbol = lookup(symbol).get("symbol")
        shares = request.form.get("shares")
        shares = int(shares)
        price = lookup(symbol).get("price")

        # error if symbol is none
        if lookup(symbol) == None:
            return apology("Symbol doesn't exist, try again")

        # ensure positive int is input for shares
        if int(shares) < 1:
            return apology("must sell at least 1 share")

        # check user has enough shares
        sharesCheck = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        if sharesCheck[0]["SUM(shares)"] < shares:
            return apology("you cannot sell more shares than you own")

        # check user's cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]["cash"]
        # calc cost of the transaction
        cost = int(shares) * price

        # update transactions
        # add row to db
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, (int(shares) * -1), price)

        # update user cash
        balance = cash + cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
