from flask import Flask, render_template, request, redirect

app = Flask(__name__)

# Variable to hold list of tasks
taskList = []

@app.route("/")
def tasks():
    return render_template("tasks.html", taskList=taskList)

# the /add page is responsible for the add task page (GET req) & handling the new task data (POST req)
# add GET & POST methods to route
@app.route("/add", methods=["GET", "POST"])
def add():
    # if GET method, user is trying to visit page, so serve the default page
    if request.method == "GET":
        return render_template("add.html")
    # else POST method, user it trying to add data
    else:
        # add data to tasks list, use form for form POST method
        task = request.form.get("task")
        taskList.append(task)
        # redirect to tasks page
        return redirect("/")

@app.route("/delete", methods=["POST"])
def delete():
    task = request.form.get("task")
    taskList.remove(task)
    return redirect("/")