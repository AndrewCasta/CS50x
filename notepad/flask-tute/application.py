import random # imported for random numbers, not related to flask.

#########
# Setup
#########
# https://flask.palletsprojects.com/en/1.1.x/

from flask import Flask, render_template, request, redirect
# Flask - need to import the basic flask functions
# render-template - allows the use of html templates
# request - gives access to the request arguments
# redirect - provides re-direct function

# declare app as a variable
app = Flask(__name__)

################
# Routing pages
################
# "/" is the first page a user lands on.
# Routing defines a function, that returns something.

@app.route("/goodbye")
def bye():
    # this returns plain text in the body tag.
    return "Goodbye!"

##########################
# Routing > HTML templates
##########################
# uses Jinja2 template engine
# https://flask.palletsprojects.com/en/1.1.x/templating/

@app.route("/hello-world")
def hello_world():
    # this returns a 'rendered' html doc. See ./templates.
    return render_template("hello-world.html")

# -----------------
# template arguments

@app.route("/name")
def name():
    # this returns a 'rendered' html doc, that has taken arguments and inserted in the html template.
    # in the html template, arguments are accessed using {{ name }}
    return render_template("name.html", name="Andrew")

@app.route("/variable")
def variable():
    # You can delcare a variable in python, & pass to the template. Doesn't have to match.
    randNumber = random.randint(0, 1)
    return render_template("variable.html", number=randNumber)

# -------------------
# Template statements
# https://jinja.palletsprojects.com/en/2.11.x/templates/#list-of-control-structures

# if statement in template - see variable.html
    # {% if number == 1 %}
    #     Your coin flip is HEADS.
    # {% else %}
    #     Your coin flip is TAILS.
    # {% endif %}

############################
# Routing incoming arguments
############################
# e.g. web form

# this page simply takes a name from a form and fires a simple GET 'action'
@app.route("/form")
def form():
    return render_template("form.html")

# >> Form directs to /hello-form?name=Andrew

# Server then this takes an argument from the address and uses it to render a page dynamically
@app.route("/hello-borm")
def hello_borm():
    name = request.args.get("name")
    return render_template("hello-form.html", name=name)

# you can use the variable with regular python logic to handle the request
# this adds error handling if name is empty
@app.route("/hello-form")
def hello_form():
    name = request.args.get("name")
    if not name:
        return render_template("form-fail.html")
    else:
        return render_template("hello-form.html", name=name)

#######################
# Template inheritence
#######################
# https://jinja.palletsprojects.com/en/2.11.x/templates/#template-inheritance

# Base layout & child pages
# Layout.html contains the main file, with block body
# Child page 'extends' the layout, and specifies it's own content in those blocks

# see templates/layout.html & form.html


###############
# Task list app
###############

# Variable to hold list of tasks
taskList = []

@app.route("/global")
def tasks_gbl():
    return render_template("tasks-gbl.html", taskList=taskList)

# the /add page is responsible for the add task page (GET req) & handling the new task data (POST req)
# add GET & POST methods to route
@app.route("/add-global", methods=["GET", "POST"])
def add_gbl():
    # if GET method, user is trying to visit page, so serve the default page
    if request.method == "GET":
        return render_template("add-gbl.html")
    # else POST method, user it trying to add data
    else:
        # add data to tasks list, use form for form POST method
        task = request.form.get("task")
        taskList.append(task)
        # redirect to tasks page
        return redirect("/global")

# GET vs POST and handling request method data
# https://www.w3schools.com/tags/ref_httpmethods.asp
# https://www.digitalocean.com/community/tutorials/processing-incoming-request-data-in-flask


###########
# Sessions
###########

# the above app stores todos on the global application variable, which accessable by all.
# sessions allow the users to have their own 'session' using cookies

from flask import session
from flask_session import Session

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"

# gives access to a python dict called session
# access information which is local to the current users interaction with the webpage
Session(app)


@app.route("/")
def tasks():
    # Check if the user has NOT a key in the dict for "todo", then add key with value as empty list
    if "taskList" not in session:
        session["taskList"] = []
    # Then pass this session taskList to the page
    return render_template("tasks.html", taskList=session["taskList"])


@app.route("/add", methods=["GET", "POST"])
def add():
    if request.method == "GET":
        return render_template("add.html")
    else:
        task = request.form.get("task")
        # add the task to this session taskList
        session["taskList"].append(task)
        return redirect("/")