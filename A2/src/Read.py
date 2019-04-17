from StdntAllocTypes import *
from DCapALst import *
from SALst import *


def load_stdnt_data(s):

    d = {'civil': DeptT.civil,
         'chemical': DeptT.chemical,
         'electrical': DeptT.electrical,
         'mechanical': DeptT.mechanical,
         'software': DeptT.software,
         'materials': DeptT.materials,
         'engphys': DeptT.engphys}
    SALst.init()
    file = open(s, "r")
    file.seek(0)
    number_of_lines = sum(1 for line in file)
    file.seek(0)
    for i in range(number_of_lines):
        temp = file.readline()
        temp2 = temp.strip().split(", ")
        temp2[5] = temp2[5][1:]
        temp2[-2] = temp2[-2][:-1]
        if(temp[3] == 'male'):
            gender = GenT.male
        else:
            gender = GenT.female
        top_choices = []
        for i in temp2[5:-1]:
            top_choices.append(d[i])
        free_choice = ''
        if(temp2[-1] == 'True'):
            free_choice = True
        else:
            free_choice = False
        sinfo = SInfoT(temp2[1], temp2[2], gender,
                       float(temp2[4]), SeqADT(top_choices), free_choice)
        SALst.add(temp2[0], sinfo)


def load_dcap_data(s):

    d = {'civil': DeptT.civil,
         'chemical': DeptT.chemical,
         'electrical': DeptT.electrical,
         'mechanical': DeptT.mechanical,
         'software': DeptT.software,
         'materials': DeptT.materials,
         'engphys': DeptT.engphys}
    DCapALst.init()
    file = open(s, "r")
    file.seek(0)
    number_of_lines = sum(1 for line in file)
    dept = ''
    file.seek(0)
    for i in range(number_of_lines):
        temp = file.readline()
        temp2 = temp.strip().split(", ")
        dept = d[temp2[0]]
        DCapALst.add(dept, int(temp2[1]))
