# from cs50 import SQL
# db = SQL("sqlite:///test.db")


import sqlite3
from flask import Flask, render_template, request, redirect

conn = sqlite3.connect('test.db')
conn.row_factory = sqlite3.Row
db = conn.cursor()
app = Flask(__name__)

@app.route("/")
def index():
    users = db.execute("SELECT * FROM people")
    return render_template("index.html", users=users)

@app.route("/add", methods = ["GET", "POST"])
def add():
    if request.method == "GET":
        return redirect("/")
    else:
        user = ['','','','']
        user[0] = request.form.get("firstName")
        user[1] = request.form.get("LastName")
        user[2] = request.form.get("email")
        user[3] = request.form.get("password")
        print(user[0])
        db.execute("INSERT INTO people (firstName, lastName, email, password) VALUES (?, ?, ?, ?)", (user[0], user[1], user[2], user[3]))
        conn.commit()
        return redirect("/")



# seeing what the db execute returns, trying to inspect
# users = db.execute("SELECT * FROM people")
# for user in users.fetchall():
#         print(user[0])



# tesing the sqlite db execute. Needs to conn (connect) and commit conn.commit() to save changes.
# user = ['a','b','c','d']
# db.execute("INSERT INTO people (firstName, lastName, email, password) VALUES (?, ?, ?, ?)", (user[0], user[1], user[2], user[3]))
# conn.commit()

# # db.execute("INSERT INTO people (firstName, lastName, email, password) VALUES (?, ?, ?, ?)", ('a','b','c','d'))
# db.execute("INSERT INTO people (firstName, lastName, email, password) VALUES ('a','b','c','d')")


