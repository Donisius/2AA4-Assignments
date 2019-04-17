## @file DCapLst.py
#  @author Donisius Wigie
#  @date 2019-02-09


## @brief This class represents the department capacities.
#  @details This class contains the capacities of each of the departments
class DCapALst:

    ## @brief Initiator for DCapLst
    #  @details Creates an empty list that will contain the departments and
    #  associated capacities.
    @staticmethod
    def init():
        DCapALst.s = []

    ## @brief Adds a department and the capacity
    #  @details Appends a tuple of the department and its capacity to DCapALst.s
    #  @param d DeptT containing the department name
    #  @param n Integer value of the capacity of the department
    @staticmethod
    def add(d, n):
        for i in range(DCapALst.s.__len__()):
            if(DCapALst.s[i][0] == d):
                raise Exception(KeyError)
        DCapALst.s.append((d, n))

    ## @brief Removes a department and its capacity from DCapLst.s
    #  @param d DeptT containing the department name
    @staticmethod
    def remove(d):
        for i in range(DCapALst.s.__len__()):
            if(DCapALst.s[i][0] is d):
                del DCapALst.s[i]
                return
        raise Exception(KeyError)

    ## @brief Checks to see if a department is in DCapLst.s
    #  @param d DeptT containing the department name
    #  @return Returns True if the department is in DCapLst.s
    @staticmethod
    def elm(d):
        for i in range(DCapALst.s.__len__()):
            if(DCapALst.s[i][0] is d):
                return True
        return False

    ## @brief Returns the capacity of a departments
    #  @param d DeptT containing the department name
    #  @return Returns the department d capacity
    @staticmethod
    def capacity(d):
        for i in range(DCapALst.s.__len__()):
            if(DCapALst.s[i][0] is d):
                return DCapALst.s[i][1]
        raise Exception(KeyError)
