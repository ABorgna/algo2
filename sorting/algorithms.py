from list_algorithms import presentar
import random

grupo= 'elegir nombre copado'

# ATENCION: dejar solamente las implementaciones de los algoritmos a entregar


def insertion_sort(a):
    return a


def selection_sort(a):
    return a

def swap(a, i1, i2):
    a[i1], a[i2] = a[i2], a[i1]

def max3(a, b, c):
    if a > b:
        if b > c:
            return b
        if a > c:
            return c
        return a
    else:
        if c > b:
            return b
        if c > a:
            return c
        return a


@presentar
def quicksort(a):
    if len(a) <= 1:
        return a
    if len(a) == 2:
        if a[0] > a[1]:
            swap(a, 0, 1)
        return a

    debug = False

    i2 = int(len(a)/2)
    m1, m2, m3 = a[0], a[i2], a[-1]
    p = max3(m1, m2, m3)
    pi = 0
    if p == m2:
        pi = i2
    elif p == m3:
        pi = len(a)-1
    
    swap(a, pi, 0)

    left = False
    li = 1
    l = a[li]
    ri = len(a)-1
    r = a[ri]
    for iteracion in range(len(a)-2):
        if debug: print "debug:", a, left, li, ri
        if left:
            if l < p:
                li += 1
                l = a[li]
            else:
                swap(a, li, ri)
                l = r
                ri -= 1
                r = a[ri]
                left = False
        else:
            if r > p:
                ri -= 1
                r = a[ri]
            else:
                swap(a, li, ri)
                r = l
                li += 1
                l = a[li]
                left = True
    if debug: print "debug:", a

    if l > p:
        swap(a, 0, li-1)
        li -= 1
    else:
        swap(a, 0, li)
    if debug: print "debug:", a

    a[:li] = quicksort(a[:li])
    a[li+1:] = quicksort(a[li+1:])
    if debug: print "debug:", a, "r" 
    return a
        

@presentar
def heapsort(a):
    length = len(a)

    heapify(a, length)

    heapLength = length
    oldRoot = a[0] if length else None
    for i in range(length-1, 0, -1):
        newRoot = a[i]

        a[0] = newRoot
        a[i] = oldRoot

        heapLength -= 1

        oldRoot = heapBalance(a,0,heapLength,newRoot)

    return a

def heapify(a, length):

    for i in range(((int)(length/2))-1,-1,-1):
        heapBalance(a,i,length)

def heapBalance(a, i, length, eRoot=None, eLeft=None, eRight=None):
    eRoot, eLeft, eRight = heapElems(a,i,length,eRoot,eLeft,eRight)

    newRoot = eRoot

    maxElem = 'root'

    if eLeft is not None and eRoot < eLeft:
        maxElem = 'left'
        if eRight is not None and eLeft < eRight:
            maxElem = 'right'
    elif eRight is not None and eRoot < eRight:
        maxElem = 'right'

    if maxElem == 'left':
        a[i] = eLeft
        a[heapChildL(i)] = eRoot

        heapBalance(a, heapChildL(i), length, eRoot, None, None)

        newRoot = eLeft

    elif maxElem == 'right':
        a[i] = eRight
        a[heapChildR(i)] = eRoot

        heapBalance(a, heapChildR(i), length, eRoot, None, None)

        newRoot = eRight

    return newRoot

def heapChildL(i):
    return i * 2 + 1

def heapChildR(i):
    return i * 2 + 2

def heapParent(i):
    return (int) ((i - 1) / 2)

def heapElems(a, i, length, eRoot=None, eLeft=None, eRight=None):
    if eRoot is None:
        eRoot = a[i]

    if eLeft is None and heapChildL(i) < length:
        eLeft = a[heapChildL(i)]

    if eRight is None and heapChildR(i) < length:
        eRight = a[heapChildR(i)]

    return eRoot, eLeft, eRight

@presentar
def mergesort(a):
    length = len(a)
    middle = (int) (length / 2)

    if length <= 1:
        return a

    # Divide
    l = mergesort(a[:middle])
    r = mergesort(a[middle:])

    # Conquer (merge)
    i = 0
    left_i = 0
    right_i = 0

    left_e = l[0] if middle else None
    right_e = r[0] if (length - middle) else None

    while i < length and left_i < middle and right_i < (length - middle):
        if right_e < left_e:
            a[i] = right_e

            right_i += 1
            right_e = r[right_i] if right_i < (length - middle) else None

        else:
            a[i] = left_e

            left_i += 1
            left_e = l[left_i] if left_i < middle else None

        i += 1

    while left_i < middle:
        a[i] = left_e

        left_i += 1
        left_e = l[left_i] if left_i < middle else None

        i += 1

    while right_i < (length - middle):
        a[i] = right_e

        right_i += 1
        right_e = r[right_i] if right_i < (length - middle) else None

        i += 1

    return a

