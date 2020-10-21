import csv
import sys


csvFile = open('databases/small.csv', newline='')
csvPeople = csv.DictReader(csvFile)
for row in csvPeople:
    print(row)