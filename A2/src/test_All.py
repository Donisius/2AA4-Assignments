import pytest
from AALst import *
from DCapALst import *
from SALst import *
from SeqADT import *
from StdntAllocTypes import *


# Tests for DCapALst
DCapALst.init()


# Tests to see if elm will return false is a department is not in DCapALst
def test_elm_empty():
    assert DCapALst.elm(DeptT.chemical) is False


# Tests if add works and if capacity works when capacity is 0
def test_capacity_empty():
    DCapALst.add(DeptT.chemical, 0)
    assert DCapALst.capacity(DeptT.chemical) == 0


# Tests to see if remove function works and if capacity will raise an exception if
# department info is not present
def test_remove_capacity():
    DCapALst.remove(DeptT.chemical)
    with pytest.raises(Exception):
        DCapALst.capacity(DeptT.chemical)


# Tests to see if add works for normal cases and if elm will work for normal cases
def test_add_elm():
    DCapALst.add(DeptT.software, 50)
    assert DCapALst.elm(DeptT.software) is True


def test_add_except():
    with pytest.raises(Exception):
        DCapALst.add(DeptT.software, 0)


# Tests for SALst
SALst.init()
DCapALst.init()


def test_remove_nothing():
    with pytest.raises(Exception):
        SALst.remove('wigied')


def test_add():
    sinfo1 = SInfoT("first", "last", GenT.male, 12.0,
                    SeqADT([DeptT.civil, DeptT.chemical]), True)
    SALst.add('wigied', sinfo1)
    assert SALst.elm('wigied') is True


def test_remove_elm():
    SALst.remove('wigied')
    assert SALst.elm('wigied') is False


def test_remove_nonexist():
    with pytest.raises(Exception):
        SALst.remove('pintos')


def test_info():
    sinfo1 = SInfoT("first", "last", GenT.male, 12.0,
                    SeqADT([DeptT.civil, DeptT.chemical]), True)
    SALst.add('wigied', sinfo1)
    assert isinstance(SALst.info('wigied'), SInfoT)
    assert SALst.info('wigied').gender == GenT.male
    assert SALst.info('wigied').fname == "first"
    SALst.remove('wigied')


def test_sort():
    sinfo2 = SInfoT("first", "last", GenT.male, 11.0,
                    SeqADT([DeptT.software, DeptT.chemical]), True)
    sinfo3 = SInfoT("first", "last", GenT.male, 10.0,
                    SeqADT([DeptT.electrical, DeptT.chemical]), True)
    sinfo4 = SInfoT("first", "last", GenT.male, 6.0,
                    SeqADT([DeptT.engphys, DeptT.chemical]), True)
    sinfo5 = SInfoT("first", "last", GenT.male, 3.0,
                    SeqADT([DeptT.chemical, DeptT.civil]), True)
    sinfo6 = SInfoT("first", "last", GenT.male, 12.0,
                    SeqADT([DeptT.mechanical, DeptT.chemical]), False)
    SALst.add('wigied2', sinfo2)
    SALst.add('wigied3', sinfo3)
    SALst.add('wigied4', sinfo4)
    SALst.add('wigied5', sinfo5)
    SALst.add('wigied6', sinfo6)
    sort_list = SALst.sort(lambda t: t.freechoice and t.gpa >= 4.0)
    assert sort_list == ['wigied2', 'wigied3', 'wigied4']


def test_sort_notfc():
    sort_list = SALst.sort(lambda t: not(t.freechoice) and t.gpa >= 4.0)
    assert sort_list == ['wigied6']


def test_average():
    average_males = SALst.average(lambda x: x.gender == GenT.male)
    assert average_males == 8.4


def test_average_excep():
    with pytest.raises(Exception):
        SALst.average(lambda x: x.gender == GenT.female)


def test_allocate_no_deps():
    with pytest.raises(Exception):
        SALst.allocate()
    SALst.remove('wigied2')
    SALst.remove('wigied3')
    SALst.remove('wigied4')
    SALst.remove('wigied5')
    SALst.remove('wigied6')


def test_allocate():
    sinfo2 = SInfoT("first", "last", GenT.male, 11.0,
                    SeqADT([DeptT.software, DeptT.chemical]), True)
    sinfo3 = SInfoT("first", "last", GenT.male, 10.0,
                    SeqADT([DeptT.electrical, DeptT.chemical]), True)
    sinfo4 = SInfoT("first", "last", GenT.male, 6.0,
                    SeqADT([DeptT.engphys, DeptT.chemical]), True)
    sinfo5 = SInfoT("first", "last", GenT.male, 3.0,
                    SeqADT([DeptT.chemical, DeptT.civil]), True)
    sinfo6 = SInfoT("first", "last", GenT.male, 12.0,
                    SeqADT([DeptT.mechanical, DeptT.chemical]), False)
    SALst.add('wigied2', sinfo2)
    SALst.add('wigied3', sinfo3)
    SALst.add('wigied4', sinfo4)
    SALst.add('wigied5', sinfo5)
    SALst.add('wigied6', sinfo6)
    DCapALst.add(DeptT.civil, 5)
    DCapALst.add(DeptT.electrical, 5)
    DCapALst.add(DeptT.engphys, 1)
    DCapALst.add(DeptT.chemical, 5)
    DCapALst.add(DeptT.mechanical, 0)
    SALst.allocate()
    assert AALst.lst_alloc(DeptT.chemical) == ['wigied6']


def test_allocate_no_space():
    sinfo7 = SInfoT("first", "last", GenT.male, 10.0,
                    SeqADT([DeptT.mechanical]), False)
    SALst.add('wigied7', sinfo7)
    with pytest.raises(Exception):
        SALst.allocate()


# Tests for SeqADT
def test_constructor():
    constructor_test = SeqADT([DeptT.software, DeptT.electrical, DeptT.engphys])
    assert isinstance(constructor_test, SeqADT)


def test_next():
    constructor_test = SeqADT([DeptT.software, DeptT.electrical, DeptT.engphys])
    next_test = constructor_test.next()
    assert next_test is DeptT.software


def test_next_except():
    constructor_test = SeqADT([DeptT.software, DeptT.electrical, DeptT.engphys])
    constructor_test.next()
    constructor_test.next()
    constructor_test.next()
    with pytest.raises(Exception):
        constructor_test.next()


def test_end():
    constructor_test = SeqADT([DeptT.software, DeptT.electrical, DeptT.engphys])
    assert constructor_test.end() is False


def test_end_2():
    constructor_test = SeqADT([DeptT.software, DeptT.electrical, DeptT.engphys])
    constructor_test.next()
    constructor_test.next()
    constructor_test.next()
    assert constructor_test.end() is True
