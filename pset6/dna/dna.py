import csv
import sys

# this program will read a dna sequence (text) and count the consecutive STRs and store them in a number of variables. then it will compore the numbers with
# the dna database and find out whose dna sequence it is

# 3 command line arguments, the name of csv file (database) and the text file (dna sequence) respectively
if len(sys.argv) != 3:
    sys.exit('Error 1')


myArray = []

with open(sys.argv[1], newline='') as csvfile1:
     reader = csv.DictReader(csvfile1)

     for row in reader:
         # print('row',row)

         # for each ordered dict in reader, convert it to a normal dict
         row = dict(row)
         # and append the dict into a list called myArray, which will contain the list of dicts. each dict will have the str_data about only one person
         myArray.append(row)

#print(myArray)


# open the csv file
csvfile = open(sys.argv[1], 'r')
#read the csv file row by row into a series of lists
database2 = csv.reader(csvfile)


textfile = open(sys.argv[2], 'r')
#read the text file into a long string
dna_buffer = textfile.read()

#print('dna',dna_buffer)

# creating my own list of STRs that i can call on
strlist = list()
for x in database2:
    #print(x)
    if x[1].isdigit():
        continue
    else:
        # y will take the range of 8 (0 is not included)
        # and will decrement by 1, until it reaches, but does not include 0
        for y in range(len(x)-1, 0, -1):
            strlist.append(x[y])


#print('strlist',strlist)



dnaseq_data = dict()

# for every STR in the str list,
for STR in strlist:

    # variables i will be using
    i = 0
    str_count = 1
    tmp = -9
    longest_str_count = 1
    str_found = STR in dna_buffer

    while True:
        if dna_buffer[i : i + len(STR)] == STR:

            #if the last found STR is too far away, forget about that one and that tmp to this new tmp
            #in other words, this marks the start of any seq of STRs. as long as i is out of range from the next tmp, means it is no longer consec
            #set str_count back to the starting number, 1
            if i - tmp > len(STR):
                tmp = i
                str_count = 1

            #if i and tmp is in range, can be considered that they r consec
            elif i - tmp == len(STR):
                #start the consec count
                str_count += 1
                #if STR == 'AATG':
                    #print(i, tmp, str_count)

                if str_count > longest_str_count:
                    longest_str_count = str_count
                tmp = i


        if i+4 == len(dna_buffer):
            if str_found == False:
                longest_str_count = 0
            #when end of the string is reached, store the longest_str_count(value) into the respective STR(key) in my new dict
            dnaseq_data[STR] = str(longest_str_count)
            break
        i += 1

            
    #print(longest_str_count)
    dnaseq_data[STR] = str(longest_str_count)



for STR, number in dnaseq_data.items():
    print(STR, number)

for dic in myArray:
    #for each dictionary in myArray of dictionary, if the new dict (dnaseq_data) is a subset of any dict in myArray, print dic['name']
    #order does not matter since there is the use of same keys in the dicts
    if dnaseq_data.items() <= dic.items():
        print(dic['name'])
        break

# if the for loop has completed without terminating permaturely, show that there is no match
else:
    print("no match")


