## @file SeqADT.py
#  @author Donisius Wigie
#  @date 2019-02-09


## @brief This class stores the top choices of the students.
#  @details It will store a list of the DeptT top choices.
class SeqADT:
    ## @brief Constructor for the class SeqADT.
    #  @details Initiates the index for the choices list of top choices.
    def __init__(self, t):
        self.t = t
        self.i = 0

    ## @brief Sets the index back to 0
    def start(self):
        self.i = 0

    ## @brief Adds one to the index and returns the previous top choice.
    #  @return Returns the previous top choice before moving index.
    def next(self):
        temp = self.i
        if (self.i < self.t.__len__()):
            self.i += 1
        elif (self.i >= self.t.__len__()):
            raise Exception(StopIteration)
        return self.t[temp]

    ## @brief Checks to see if there are no more top choices.
    #  @return Returns True if there are no more choices and False if there is.
    def end(self):
        if(self.i >= self.t.__len__()):
            return True
        else:
            return False
