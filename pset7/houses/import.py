# TODO
import csv
import cs50
import sys

if len(sys.argv) != 2:
    print("error")
    sys.exit(1)

csvFile = sys.argv[1]

# CLA spreadsheet

db = cs50.SQL("sqlite:///students.db")

file = open(csvFile, newline='')
reader = csv.DictReader(file)

for row in reader:
    house = row["house"]
    birth = row["birth"]

    fullname = row["name"].split()
    first = fullname[0]
    if len(fullname) == 3:
        middle = fullname[1]
        last = fullname[2]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)
    else:
        last = fullname[1]
        db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)", first, last, house, birth)

    # print(first,middle,last, house, birth)

