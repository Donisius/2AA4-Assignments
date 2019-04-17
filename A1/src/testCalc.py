## @file testCalc.py
#  @Donisius Wigie
#  @A module to test CalcModule.py
#  @2019-01-12

from CalcModule import *
from ReadAllocationData import *
#A function to test if the sort function actually sorted the Students
def testSort(S):
    i = 0
    for i in range(S.__len__() - 1):
        if(S[i + 1]['gpa'] > S[i]['gpa']):
            print('The list is not sorted properly - FAILED')
            return 0
    print('The list is sorted properly - PASSED')
    return 1
#A function to obtain a list of macid's who have a gpa < 4.0, takes
#List of dictionaries produced by readStdnts
sample = readStdnts("studentInfo.txt")
sortedSample = sort(sample)
def failures(S):
    failureList = []
    for students in range(S.__len__()):
        if(S[students]['gpa'] < 4.0):
            failureList.append(S[students]['macid'])
    return failureList

freeChoice = readFreeChoice("freeChoice.txt")
dictList = readStdnts("studentInfo.txt")
deptCap = readDeptCapacity("deptCapacity.txt")
test = allocate(dictList, freeChoice, deptCap)
fails = failures(sample)

print('REGULAR INPUTS: ')
print('*****************************************************************************')
sortedSample = sort(sample)
test0 = testSort(sortedSample)
#A function to test whether or not the students who failed were allocated
#Takes dictionary of allocations and failure list
#Returns 1 if pass 0 if not
def belongOrNot(A, F):
    #allocate the students who belong
    for i in F:
        for j in range(A['civil'].__len__()):
            if(A['civil'][j] == i):
                print('belongOrNot test failed')
                return 0
        for j in range(A['chemical'].__len__()):
            if(A['chemical'][j] == i):
                print('belongOrNot test failed')
                return 0
        for j in range(A['electrical'].__len__()):
            if(A['electrical'][j] == i):
                print('belongOrNot test failed')
                return 0
        for j in range(A['mechanical'].__len__()):
            if(A['mechanical'][j] == i):
                print('belongOrNot test failed')
                return 0
        for j in range(A['software'].__len__()):
            if(A['software'][j] == i):
                print('belongOrNot test failed')
                return 0
        for j in range(A['materials'].__len__()):
            if(A['materials'][j] == i):
                print('belongOrNot test failed')
                return 0
        for j in range(A['engphys'].__len__()):
            if(A['engphys'][j] == i):
                print('belongOrNot test failed')
                return 0
        print('Students who have below 4.0 were not allocated - PASSED')
        return 1
print ('Students with below a 4.0 gpa: ', fails)
firstTest = belongOrNot(test, fails)
dictList = readStdnts("studentInfo.txt")

#A function to determine the first choice of the first choice students
def firstChoices(F, S):
    firstChoices = []
    for i in range(F.__len__()):
        for j in range(S.__len__()):
            if(F[i] == S[j]['macid'] and S[j]['gpa'] >= 4.0):
                firstChoices.append([F[i], S[j]['choices'][0]])
    return firstChoices

fcList = firstChoices(freeChoice, dictList)
try:
    test1 = allocate(dictList, freeChoice, deptCap)
    test1 = 1
    print('Regular inputs for allocate - PASSED')
except Exception as e:
    log.error("there was an exception %s", str(e))
    test1 = 0

print ('Inputs for average function: Regular inputs, ie. supplied files/binary genders')
try:
    test2 = average(dictList, 'male')
    test2 = average(dictList, 'female')
    test2 = 1
    print('Average function test - PASSED')
except Exception as e:
    log.error("there was an exception %s", str(e))
    test2 = 0

#A funtion to check if everyone who had free choice got
#first choice pick; takes dictionary of allocations and first choice list
def fcAllocated(A, fc):
    counter = fc.__len__()
    for i in range(fc.__len__()):
        for j in range(A['civil'].__len__()):
            if(fc[i][1] == 'civil' and fc[i][0] == A['civil'][j]):
                counter -= 1
        for j in range(A['chemical'].__len__()):
            if(fc[i][1] == 'chemical' and fc[i][0] == A['chemical'][j]):
                counter -= 1
        for j in range(A['electrical'].__len__()):
            if(fc[i][1] == 'electrical' and fc[i][0] == A['electrical'][j]):
                counter -= 1
        for j in range(A['mechanical'].__len__()):
            if(fc[i][1] == 'mechanical' and fc[i][0] == A['mechanical'][j]):
                counter -= 1
        for j in range(A['software'].__len__()):
            if(fc[i][1] == 'software' and fc[i][0] == A['software'][j]):
                counter -= 1
        for j in range(A['materials'].__len__()):
            if(fc[i][1] == 'materials' and fc[i][0] == A['materials'][j]):
                counter -= 1
        for j in range(A['engphys'].__len__()):
            if(fc[i][1] == 'engphys' and fc[i][0] == A['engphys'][j]):
                counter -= 1
    if(counter == 0):
        print('All free choices were granted to those who had free choice - PASSED')
        return 1
    print('fcAllocated test failed')
    return 0
print ('First choice students: ', fcList)
test3 = fcAllocated(test, fcList)

print('BOUNDARY CASES: ')
print('*****************************************************************************')
#Allocate function with empty department capacity file
deptCap = {}
print ('Input for Empty department test: ', deptCap, 'expected to not crash')
try:
    test4 = allocate(dictList, freeChoice, deptCap)
    test4 = 1
    print('Empty Department Test - PASSED')
except Exception as e:
    log.error("there was an exception %s", str(e))
    test4 = 0

#Allocate function with empty student list
dictList = []
print ('Input for Empty Student List Test: ', dictList, 'expected to not crash')
try:
    test5 = allocate(dictList, freeChoice, deptCap)
    test5 = 1
    print('Empty Student List Test - PASSED')
except Eception as e:
    log.error("there was an exception %s", str(e))
    test5 = 0

#Average function with a non-male/female gender Input
dictList = readStdnts("studentInfo.txt")
gender = 'apache attack helicopter'
print ('Input for gender - average function: ', gender, 'expected to not crash')
try:
    test6 = average(dictList, gender)
    test6 = 1
    print('Not A Real Gender Test - PASSED')
except Exception as e:
    log.error("there was an exception %s", str(e))
    test6 = 0
testInput = 'This is some random nonsense'

print ('input for allocation function: ', testInput, 'expected to not crash')
try:
    test7 = allocate(testInput, freeChoice, deptCap)
    test7 = 1
    print('Nonsense test 1 for allocate - PASSED')
except Exception as e:
    log.error("there was an exception %s", str(e))
    test7 = 0
#This is a test to see if the allocation function can handle students with negative gpa
print('Negative gpa test: ')
studentList = [{'macid': 'wigied', 'fname': 'Donisius', 'lname': 'Wigie', 'gender': 'male', 'gpa': -6.0, 'choices': ['software', 'electrical', 'engphys']}]
print('Input for studentList = ', studentList)
freeC = ['wigied']
try:
    test8 = allocate(studentList, freeC, deptCap)
    test8 = 1
    print('Negative gpa test for allocate - PASSED')
except Exception as e:
    log.error("there was an exception %s", str(e))
    test8 = 0
#This is a test to see if the allocation function can handle students with a gpa above 12
print('Excessively high gpa test: ')
studentList = [{'macid': 'wigied', 'fname': 'Donisius', 'lname': 'Wigie', 'gender': 'male', 'gpa': 77.0, 'choices': ['software', 'electrical', 'engphys']}]
print('Input for studentList = ', studentList)
freeC = ['wigied']
try:
    test9 = allocate(studentList, freeC, deptCap)
    test9 = 1
    print('Excessively high gpa test for allocate - PASSED')
except Exception as e:
    log.error("there was an exception %s", str(e))
    test9 = 0
print('Empty list parameter for average function: ')
print('Input for average function: ', [])
try:
    test10 = average([], 'male')
    test10 = 1
    print('Empty list parameter for average function - PASSED')
except Exception as e:
    log.error("there was an exception %s", str(e))
    test10 = 0

total = test0 + test1 + test2 + test3 + test4 + test5 + test6 + test7 + test8 + test9 + test10
print('*****************************************************************************')
print('The total score is: ',total, 'out of', 11, 'tests passed: ', float((total/11) * 100), '%')
