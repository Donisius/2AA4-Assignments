## @file SALst.py
#  @author Donisius Wigie
#  @date 2019-02-09
from StdntAllocTypes import *
from AALst import *
from DCapALst import *


## @brief This class represents the student allocation processes.
#  @details This class contains a list of the students with their info.
class SALst:

    ## @brief Initiator for SALst.
    #  @details Creates an empty list that will hold student info.
    @staticmethod
    def init():
        SALst.s = []

    ## @brief Function to add a student into SALst.
    #  @param m String containing the macID of a student.
    #  @param i SeqADT containing the information of the student.
    @staticmethod
    def add(m, i):
        if(isinstance(i, SInfoT)):
            SALst.s.append([m, i])
        else:
            raise Exception(KeyError)

    ## @brief Function to remove student and student information from SALst.
    #  @param m String containing the macID of a student.
    @staticmethod
    def remove(m):
        for i in range(SALst.s.__len__()):
            if(SALst.s[i][0] is m):
                del SALst.s[i]
                return
        raise Exception(KeyError)

    ## @brief Function to check if a student is present in SALst.
    #  @param m String containing the macID of a student.
    #  @return True if the student is in SALst and False if student is not in SALst.
    @staticmethod
    def elm(m):
        for i in range(SALst.s.__len__()):
            if(SALst.s[i][0] is m):
                return True
        return False

    ## @brief Function that returns a student's information
    #  @param m String containing the macID of a student.
    #  @return SeqADT containing the information of the student.
    @staticmethod
    def info(m):
        for i in range(SALst.s.__len__()):
            if(SALst.s[i][0] is m):
                return SALst.s[i][1]
        raise Exception(KeyError)

    ## @brief Function which sorts students according to gpa in descending order.
    #  @param f Function that filters which students will be returned in the list of students.
    #  @return Returns a list of stduents in descending order based on gpa, filtered by f.
    @staticmethod
    def sort(f):
        seq_str = []
        for i in range(SALst.s.__len__()):
            for j in range(i + 1, SALst.s.__len__()):
                if(SALst.s[i][1].gpa < SALst.s[j][1].gpa):
                    SALst.s[i], SALst.s[j] = SALst.s[j], SALst.s[i]
        for i in range(SALst.s.__len__()):
            if(f(SALst.s[i][1]) is True):
                seq_str.append(SALst.s[i][0])
        return seq_str

    ## @brief Function that gets the gpa average of all males or all females.
    #  @param f GenT gender of the students.
    #  @return Float value which is the gpa of all males or all females.
    @staticmethod
    def average(f):
        total = 0
        num_fset = 0
        for i in range(SALst.s.__len__()):
            if(f(SALst.s[i][1])):
                total += SALst.s[i][1].gpa
                num_fset += 1
        if(num_fset != 0):
            return float(total / num_fset)
        else:
            raise Exception('Runtime Error')

    ## @brief Function that allocates students into departments.
    #  @details Sorts students who have freechoice before those who dont.
    #  @details Students who are not put into their first choice get put to next choices.
    @staticmethod
    def allocate():
        AALst.init()
        free = SALst.sort(lambda t: t.freechoice and t.gpa >= 4.0)
        for m in free:
            ch = SALst.info(m).choices
            AALst.add_stdnt(ch.next(), m)
        stud = SALst.sort(lambda t: not(t.freechoice) and t.gpa >= 4.0)
        for m in stud:
            ch = SALst.info(m).choices
            alloc = False
            while(not(alloc) and not(ch.end())):
                d = ch.next()
                if(AALst.num_alloc(d) < DCapALst.capacity(d)):
                    AALst.add_stdnt(d, m)
                    alloc = True
            if(not(alloc)):
                raise Exception(RuntimeError)

    @staticmethod
    def get_gpa(m, s):
        for i in range(s.__len__()):
            if(m == s[i][0]):
                return s[i][1].gpa
