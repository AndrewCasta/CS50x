import csv
import sys

# take two CLAs (CSV data, text DNA)
# handle incorrect CLA

# =============== done. turned off for testing <<<<<<<<<<<<<<<

if len(sys.argv) != 3:
    print('error')
    # sys.exit(1)

# csv database
db = sys.argv[1]
# text dna
dnatext = sys.argv[2]


# open csv file & read into memory
# assume first row is headers

csvFile = open(db, newline='')
csvReader = csv.reader(csvFile)
# store the STR values from the header
STRs = next(csvReader)
# print(STRs)


# create dict of STR:count
STR = {}
for n in STRs[1:]:
    STR[n] = 1

# print(STR['AGATC'])

# open dna sequence and read into memory
dnaFile = open(dnatext)
dna = dnaFile.read()
# len(dna)
# dna[i:j]


# refactor this to be a helper fucntion that just returns max as a number <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# for each of the STRs in dna, compute longest consecutive

# STR[1]+

# for each STR check for a match
for seq in STR:
    # print(seq)
    # print(len(seq))
    # print(STR[seq])

    # check every index in string
    for i in range(len(dna)):
        # check a match, for every STR
        if dna[i: i + len(seq)] == seq:
            cnt = 1
            cntMax = 0
            # if match, check consecutive strings
            for j in range(i + len(seq), len(dna), len(seq)):
                # if consecutive, increase counter
                if dna[j: j + len(seq)] == seq:
                    cnt += 1
                # when it doesn't match, append number to the list
                else:
                    if cnt > STR[seq]:
                        STR[seq] = cnt
                    # break for further checking (this greatly increases speed!)
                    break
# print(STR)
# print(len(STR))

match = 'No match'

# people = {}
csvFile = open(db, newline='')
csvPeople = csv.DictReader(csvFile)
for row in csvPeople:
    # print(row)
    matchcnt = 0
    for item in STR:
        # print(row[item])
        # print(STR[item])

        if int(row[item]) == STR[item]:
            matchcnt += 1
        if matchcnt == len(STR):
            match = (row['name'])

print(match)

dnaFile.close()

