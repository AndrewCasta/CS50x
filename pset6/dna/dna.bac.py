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

people = {}
csvFile = open(db, newline='')
csvReader = csv.DictReader(csvFile)
next(csvReader)
for row in csvReader:
    people[row['name']] = {
    'name': row['name'],
    'AGATC': row['AGATC'],
    'AATG': row['AATG'],
    'TATC': row['TATC']}



# AGATC,TTTTTTCT,AATG,TCTAG,GATA,TATC,GAAA,TCTG


# next(csvReader)
# for row in csvReader:
#     people[row['name']] = {
#     'name': row['name'],
#     'AGATC': row['AGATC'],
#     'TTTTTTCT': row['TTTTTTCT'],
#     'AATG': row['AATG'],
#     'TCTAG': row['TCTAG'],
#     'GATA': row['GATA'],
#     'TATC': row['TATC'],
#     'GAAA': row['GAAA'],
#     'TCTG': row['TCTG']}
# print(people)



# open dna sequence and read into memory
dnaFile = open(dnatext)
dna = dnaFile.read()
# len(dna)
# dna[i:j]


# for each of the STRs in dna, compute longest consecutive
AGATC_cnt_list = []
AATG_cnt_list = []
TATC_cnt_list = []

for i in range(len(dna)):
    if dna[i:i+5] == 'AGATC':
        AGATCcnt = 1
        for j in range(i + 5, len(dna), 5):
            if dna[j:j+5 ] == 'AGATC':
                AGATCcnt += 1
            else:
                AGATC_cnt_list.append(AGATCcnt)
                break
    if dna[i:i+4] == 'AATG':
        AATGcnt = 1
        for j in range(i + 4, len(dna), 4):
            if dna[j:j+4] == 'AATG':
                AATGcnt += 1
            else:
                AATG_cnt_list.append(AATGcnt)
                break
    if dna[i:i+4] == 'TATC':
        TATCcnt = 1
        for j in range(i + 4, len(dna), 4):
            if dna[j:j+4] == 'TATC':
                TATCcnt += 1
            else:
                TATC_cnt_list.append(TATCcnt)
                break


AGATC_cnt_list.sort(reverse=True)
if AGATC_cnt_list != []:
    AGATC = str(AGATC_cnt_list[0])
else:
    AGATC = ''
AATG_cnt_list.sort(reverse=True)
if AATG_cnt_list != []:
    AATG = str(AATG_cnt_list[0])
else:
    AATG = ''
TATC_cnt_list.sort(reverse=True)
if TATC_cnt_list != []:
    TATC = str(TATC_cnt_list[0])
else:
    TATC = ''

dnaFile.close()

# compare STR counts with individuals in csv
match = ''
# loop through people
for x in people:
    # print(people[x])
    # print(people[x]['AGATC'], people[x]['AATG'], people[x]['TATC'])
    if AGATC == people[x]['AGATC'] and AATG == people[x]['AATG'] and TATC == people[x]['TATC']:
        match = people[x]['name']

if match == '':
    print('no match')
else:
    print(match)

# print match or no match



# ===================================================================================================

# read out the database
# this might be better to do later via a dict read <<<<<<<<<<<<<<<

# csvFile = open(db, newline='')
# csvReader = csv.DictReader(csvFile)
# AGATC,TTTTTTCT,AATG,TCTAG,GATA,TATC,GAAA,TCTG

# for row in csvReader:
#     people.append(row)
# print(people)
# print(people[0])
# print(people[0][1])







#     if dna[i:i+4] == 'AATG':
#         AATGcnt = 1
#         for j in range(i + 4, len(dna), 4):
#             if dna[j:j+4] == 'AATG':
#                 AATGcnt += 1
#             else:
#                 AATG_cnt_list.append(AATGcnt)
#                 break
#     if dna[i:i+4] == 'TATC':
#         TATCcnt = 1
#         for j in range(i + 4, len(dna), 4):
#             if dna[j:j+4] == 'TATC':
#                 TATCcnt += 1
#             else:
#                 TATC_cnt_list.append(TATCcnt)
#                 break

# fuck this off <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# AGATC_cnt_list.sort(reverse=True)
# if AGATC_cnt_list != []:
#     AGATC = str(AGATC_cnt_list[0])
# else:
#     AGATC = ''
# AATG_cnt_list.sort(reverse=True)
# if AATG_cnt_list != []:
#     AATG = str(AATG_cnt_list[0])
# else:
#     AATG = ''
# TATC_cnt_list.sort(reverse=True)
# if TATC_cnt_list != []:
#     TATC = str(TATC_cnt_list[0])
# else:
#     TATC = ''




# refactor this to not rely on hard coded values <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# compare STR counts with individuals in csv
# match = ''
# loop through people
# for x in people:
#     # print(people[x])
#     # print(people[x]['AGATC'], people[x]['AATG'], people[x]['TATC'])
#     if AGATC == people[x]['AGATC'] and AATG == people[x]['AATG'] and TATC == people[x]['TATC']:
#         match = people[x]['name']

# if match == '':
#     print('no match')
# else:
#     print(match)

# print match or no match