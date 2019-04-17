## @file AALst.py
#  @author Donisius Wigie
#  @date 2019-02-09
from StdntAllocTypes import *
## @brief This class represents the department allocations.
#  @details This class represents the departments and the list of students
#  who were allocated into each of the departments.


class AALst:

    ## @brief Initiator for AALst.
    #  @details Creates an empty dictionary with each department and an empty
    #  for each department where students can be allocated.
    @staticmethod
    def init():
        AALst.s = {DeptT.civil: [],
                   DeptT.chemical: [],
                   DeptT.electrical: [],
                   DeptT.mechanical: [],
                   DeptT.software: [],
                   DeptT.materials: [],
                   DeptT.engphys: []}

    ## @brief Adds a student to a department.
    #  @param dep DeptT containing the department name
    #  @param m String containing the macid of the student
    @staticmethod
    def add_stdnt(dep, m):
        AALst.s[dep].append(m)

    ## @brief Returns the list of students allocated into a department
    #  @param s DeptT containing the department name
    #  @return List of students allocated into a department
    @staticmethod
    def lst_alloc(d):
        return AALst.s[d]

    ## @brief Returns the number of students who are allocated in a specified department
    #  @param d DeptT containing the department name
    #  @return Integer value of number of students in a specified department
    @staticmethod
    def num_alloc(d):
        return sum(1 for i in AALst.s[d])
