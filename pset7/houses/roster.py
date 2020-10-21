# TODO
import csv
import cs50
import sys

if len(sys.argv) != 2:
    print("error")
    sys.exit(1)

house = sys.argv[1]
db = cs50.SQL("sqlite:///students.db")

students = db.execute("select first, middle, last, birth from students where house = ? order by last, first", house)

for student in students:
    if student['middle'] == None:
        print(f"{student['first']} {student['last']}, born {student['birth']}")
    else:
        print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")


# select first, middle, last, birth from students where house = 'Gryffindor' order by last, first;