import csv, sys, re

def compare(user_count, header, sequence, name, FILE):
    x = header * int(user_count)
    fnd = re.findall(x, sequence)
    FILE.write(f"\nName: " + name)
    FILE.write(f"\tCount of {header}: " + str(len(fnd)))
    if len(fnd) == 1:
        return True
    return False

if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py database sequence")

# Read into file for use
FILE_DB = open(sys.argv[1], 'r')  # Database
FILE_SQ = open(sys.argv[2], 'r')  # Sequences

# File for writing
FILE_WR = open('results.txt', 'w')

SEQUENCE = FILE_SQ.read()

# Set up csv.DictReader & variables related to DictReader
DATABASE = csv.DictReader(FILE_DB)
DATABASE_H = DATABASE.fieldnames

# print(DATABASE_H)

totalLst = len(DATABASE_H)
# print(totalLst)

# print(DATABASE_H[1:totalLst])

lstnoName = DATABASE_H[1:totalLst]
lenLst = len(lstnoName)

hitLst = []

for i in DATABASE:
    dumpLst = []
    for x in lstnoName:
        result = compare(i[x], x, SEQUENCE, i['name'], FILE_WR)
        dumpLst.append(result)
    # print(dumpLst)
    if all(dumpLst):
        hitLst.append(i['name'])

if len(hitLst) > 0:
    for i in hitLst:
        print(i)
else:
    print('No match')

FILE_SQ.close()
FILE_DB.close()
FILE_WR.close()