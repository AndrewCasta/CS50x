import sqlite3
# from cs50 import SQL
# db = SQL("sqlite:///test.db")

con = sqlite3.connect('test.db')
con.row_factory = sqlite3.Row # set the row_factory, gives added row
db = con.cursor()



# users = db.execute("SELECT id, firstName, lastName, email FROM people")
users = db.execute("SELECT * FROM people")

print(users.fetchall()) # list of objects, not very useful

# get at a single row (this will be first row)
one = users.fetchone()
print(dict(one)) # prints just the first row as a dict.
print(one[0]) # prints column 0 (id) of this row
print(one["id"]) # prints column id of this row


# get at all rows
# for row in users:
    # print(row) #prints object pointers. Not useful.
    # print(row.keys()) # prints keys
    # print(dict(row)) #prints key : value

