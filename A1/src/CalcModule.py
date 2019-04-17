## @file CalcModule.py
#  @author Donisius Wigie
#  @brief A module to perform calculations on a list of students
#  @date 2019-01-12

from ReadAllocationData import *

## @brief Returns a list of student dictionaries in sorted order
#  @details Sorts students from highest to lowest gpa
#  @param S A list of the dictionaries created by function readStdnt(s)
def sort(S):
    for i in range(S.__len__()):
        for j in range(i + 1, S.__len__()):
            if(S[i]['gpa'] < S[j]['gpa']):
                S[i], S[j] = S[j], S[i]
    return S

## @brief Returns the average gpa of male or female students
#  @param L A list of the dictionaries created by function readStdnt(s)
#  @param g A string representing the gender (male or female)
def average(L, g):
    possible = ['male', 'female']
    if(g not in possible):
        return 4
    if(not L):
        return 5
    sum = 0
    total = 0;
    for i in range(L.__len__()):
        if(L[i]['gender'] == g):
            sum += L[i]['gpa']
            total += 1
    return sum/total

# test = average([], 'male')
# print(test)

## @brief Returns a dictionary with the department and list of students which have been allocated into each program
#  @details Students who are not allocated to any of their top 3 picks due to no space in those departments will be temporarily placed in a department with space
#  @param S A list of the dictionaries created by function readStdnt(s)
#  @param F A list of students with free choice created by function readFreeChoice(s)
#  @param C A dictionary of department capacities created by readDeptCapacity(s)
def allocate(S, F, C):
    stdntAllocations = {'civil': None, 'chemical': None, 'electrical': None,
                        'mechanical': None, 'software': None, 'materials': None,
                        'engphys': None}
    #Checks to make sure inputs are not nonsense
    if(not isinstance(S, list) or not isinstance(F, list) or not isinstance(C, dict)):
        print("Make sure student info and free choice is in list format and department capacity is in a dictionary")
        return
    totalSpace = sum(C.values())
    if(totalSpace < S.__len__()):
        print("Departments dont have enough space!")
        return
    if('civil' not in C or C['civil'] < 1):
        print('Department Capacity is missing "civil"' or C['civil'] < 1)
        return
    if('chemical' not in C or C['chemical'] < 1):
        print('Department Capacity is missing "chemical" or has less than 1 spot')
        return
    if('electrical' not in C or C['electrical'] < 1):
        print('Department Capacity is missing "electrical" or has less than 1 spot')
        return
    if('mechanical' not in C or C['mechanical'] < 1):
        print('Department Capacity is missing "mechanical" or has less than 1 spot')
        return
    if('software' not in C or C['software'] < 1):
        print('Department Capacity is missing "software" or has less than 1 spot')
        return
    if('materials' not in C or C['materials'] < 1):
        print('Department Capacity is missing "materials" or has less than 1 spot')
        return
    if('engphys' not in C or C['engphys'] < 1):
        print('Department Capacity is missing "engphys" or has less than 1 spot')
        return

    civil = []
    chemical = []
    electrical = []
    mechanical = []
    software = []
    materials = []
    engphys = []

    #allocate all first choice students if gpa is above 4.0
    for i in range(F.__len__()):
        for j in range(S.__len__()):
            if(F[i] == S[j]['macid'] and S[j]['gpa'] >= 4.0):
                if(S[j]['choices'][0] == 'civil'):
                    civil.append(S[j]['macid'])
                if(S[j]['choices'][0] == 'chemical'):
                    chemical.append(S[j]['macid'])
                if(S[j]['choices'][0] == 'electrical'):
                    electrical.append(S[j]['macid'])
                if(S[j]['choices'][0] == 'mechanical'):
                    mechanical.append(S[j]['macid'])
                if(S[j]['choices'][0] == 'software'):
                    software.append(S[j]['macid'])
                if(S[j]['choices'][0] == 'materials'):
                    materials.append(S[j]['macid'])
                if(S[j]['choices'][0] == 'engphys'):
                    engphys.append(S[j]['macid'])

    #sort the list in descending order based on gpa
    #then begin allocating the rest of the students
    #will create space for third choice if students dont get into any program but are above the cutoff
    sort(S)
    for j in range(S.__len__()):
        if(S[j]['macid'] not in F):
            for i in range(3):
                if(S[j]['choices'][i] == 'civil' and civil.__len__() < C['civil'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                    civil.append(S[j]['macid'])
                    break;
                if(S[j]['choices'][i] == 'chemical' and chemical.__len__() < C['chemical'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                    chemical.append(S[j]['macid'])
                    break;
                if(S[j]['choices'][i] == 'electrical' and electrical.__len__() < C['electrical'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                    electrical.append(S[j]['macid'])
                    break;
                if(S[j]['choices'][i] == 'mechanical' and mechanical.__len__() < C['mechanical'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                    mechanical.append(S[j]['macid'])
                    break;
                if(S[j]['choices'][i] == 'software' and software.__len__() < C['software'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                    software.append(S[j]['macid'])
                    break;
                if(S[j]['choices'][i] == 'materials' and materials.__len__() < C['materials'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                    materials.append(S[j]['macid'])
                    break;
                if(S[j]['choices'][i] == 'engphys' and engphys.__len__() < C['engphys'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                    engphys.append(S[j]['macid'])
                    break;
                #If the student has not been allocated into anything they will be put into a department that is not empty temporarily
                if(i == 2):
                    if(S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                        print('WARNING! ', S[j]['macid'], ' has not been able to be allocated into any their top 3 choices.', S[j]['macid'], ' will be placed in a temporary department.')
                    if(civil.__len__() < C['civil'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                        civil.append(S[j]['macid'])
                        break;
                    if(chemical.__len__() < C['chemical'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                        chemical.append(S[j]['macid'])
                        break;
                    if(electrical.__len__() < C['electrical'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                        electrical.append(S[j]['macid'])
                        break;
                    if(mechanical.__len__() < C['mechanical'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                        mechanical.append(S[j]['macid'])
                        break;
                    if(software.__len__() < C['software'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                        software.append(S[j]['macid'])
                        break;
                    if(materials.__len__() < C['materials'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                        materials.append(S[j]['macid'])
                        break;
                    if(engphys.__len__() < C['engphys'] and S[j]['gpa'] >= 4.0 and S[j]['gpa'] < 13):
                        engphys.append(S[j]['macid'])
                        break;

    stdntAllocations['civil'] = civil
    stdntAllocations['chemical'] = chemical
    stdntAllocations['electrical'] = electrical
    stdntAllocations['mechanical'] = mechanical
    stdntAllocations['software'] = software
    stdntAllocations['materials'] = materials
    stdntAllocations['engphys'] = engphys

    return stdntAllocations

freeChoice = readFreeChoice('freeChoice.txt')
deptCapacity = readDeptCapacity('deptCapacity.txt')
students = readStdnts('studentInfo.txt')

test = allocate(students, freeChoice, deptCapacity)
print(test)
