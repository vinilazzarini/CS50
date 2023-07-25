import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

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
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    username = username[0]['username']

    rows = db.execute("SELECT * FROM totals WHERE username = ?", username)

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]['cash']
    sum = cash

    for row in rows:
        quote = lookup(row['symbol'])
        row['name'] = quote['name']
        row['price'] = quote['price']
        row['total'] = quote['price'] * row['shares']

    return render_template("index.html", rows=rows, cash=cash, sum=sum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("Invalid Symbol", 403)

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares < 0:
            return apology("Give a positive share number", 403)

        total = quote['price'] * shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]['cash']
        username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
        username = username[0]['username']

        if cash < total:
            return apology("insufficient funds", 403)

        cash = cash - total
        db.execute("UPDATE users SET cash = ? WHERE username = ?", cash, username)

        data_e_hora_atuais = datetime.now()
        time = data_e_hora_atuais.strftime("%d/%m/%Y %H:%M")

        db.execute("INSERT INTO portifolio (username, symbol, price, shares, time) VALUES (?,?,?,?,?)", username, symbol, quote["price"], shares, time)
        total_shares = db.execute("SELECT shares FROM totals WHERE username = ?", username)
        if total_shares == None:
            db.execute("INSERT INTO totals (username, symbol, shares) VALUES (?,?,?)", username, symbol, shares)
        else:
            total_shares = int(total_shares[0]['shares']) + shares
            db.execute("UPDATE totals SET shares = ? WHERE username = ? AND symbol = ?", total_shares , username, symbol)

        return render_template("/index.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    """Show portfolio of stocks"""
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    username = username[0]['username']

    rows = db.execute("SELECT * FROM portifolio WHERE username = ?", username)

    return render_template("index.html", rows=rows)

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

    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        print(quote)
        if quote == None:
            return apology("Invalid Symbol")
        else:
            return render_template("quoted.html", name = quote["name"], symbol = quote["symbol"], price = quote["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif not request.form.get("confirmation"):
            return apology("must provide password confimation", 403)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 403)

        # Query database for username

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))


        # Ensure username exists
        if len(rows) != 0:
            return apology("username already exists", 403)

        db.execute("INSERT INTO users (username, hash) VALUES (?,?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Redirect to Login
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")

    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("Invalid Symbol", 403)

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if shares < 0:
            return apology("Give a positive share number", 403)
        username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
        username = username[0]['username']
        total_shares = db.execute("SELECT shares FROM totals WHERE username = ? AND symbol = ?", username, symbol)

        if total_shares < shares:
            return apology("Insufficient shares", 403)

        total = quote['price'] * shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]['cash']

        cash = cash + total
        db.execute("UPDATE users SET cash = ? WHERE username = ?", cash, username)

        data_e_hora_atuais = datetime.now()
        time = data_e_hora_atuais.strftime("%d/%m/%Y %H:%M")
        shares = shares * -1

        db.execute("INSERT INTO portifolio (username, symbol, price, shares, time) VALUES (?,?,?,?,?)", username, symbol, quote["price"], shares, time)

        return render_template("index.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
