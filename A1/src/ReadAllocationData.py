## @file readAllocationData.py
#  @author Donisius Wigie
#  @brief A module to perform calculations on a list of students
#  @date 2019-01-12

## @brief Returns a list of dictionaries of student information
#  @details Each dictionary in the list corresponds to one student
#  @param s Corresponds to a filename containing student information
def readStdnts(s):
    dictList = []
    file = open(s, "r")
    file.seek(0)
    numberOfLines = sum(1 for line in file)
    file.seek(0)
    for i in range(numberOfLines - 1):
        stdntInfo = {'macid': None, 'fname': None, 'lname': None,
                 'gender': None, 'gpa': None, 'choices': None }
        temp = file.readline()
        temp2 = temp.split(" ")
        choices = [temp2[5], temp2[6], temp2[7].replace("\n", "").replace("\r", "")]
        stdntInfo['macid'] = temp2[0]
        stdntInfo['fname'] = temp2[1]
        stdntInfo['lname'] = temp2[2]
        stdntInfo['gender'] = temp2[3]
        stdntInfo['gpa'] = float(temp2[4])
        stdntInfo['choices'] = choices
        dictList.append(stdntInfo)
    file.close()
    return dictList

## @brief Returns a list of strings, where each entry in the list corresponds to the macid of a student with free choices
#  @param s Corresponds to a filename containing the macids of students who have free choice
def readFreeChoice(s):
    file = open(s, "r")
    temp = file.readline()
    freeChoice = temp.split(" ")
    file.close()
    return freeChoice

## @brief Returns a dictionary where the key value pairs are {'dept': integer}
#  @details The dictionary contains the capacity of each Department
#  @param s Corresponds to a filename containing the capacities for each department
def readDeptCapacity(s):
    deptCap = {}
    file = open(s, "r")
    numberOfLines = sum(1 for line in file)
    file.seek(0)
    for i in range(numberOfLines):
        temp = file.readline()
        temp2 = temp.split(" ")
        deptCap[temp2[0]] = int(temp2[1].replace("\n", ""))
    file.close()
    return deptCap
