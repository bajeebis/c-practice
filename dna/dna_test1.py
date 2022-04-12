import csv, sys, re
if len(sys.argv) != 2:
    sys.exit("Usage: python dna.py database sequence")

# Read into file for use
FILE_SQ = open(sys.argv[1], 'r')  # Sequences

SEQUENCE = FILE_SQ.read()
lst = []
for i in SEQUENCE:
    lst.append(i)

lst_h = ['AGATC', 'AATG', 'TATC']
word1 = lst_h[0]
x = 0

print()

FILE_SQ.close()
