from list_algorithms import presentar
import random

grupo= 'elegir nombre copado'

# ATENCION: dejar solamente las implementaciones de los algoritmos a entregar


def insertion_sort(a):
    return a


def selection_sort(a):
    return a

@presentar
def quicksort(a):
    return a

@presentar
def heapsort(a):
    return a

@presentar
def mergesort(a):
    length = len(a)
    middle = (int) (length / 2)

    if length <= 1:
        return a

    # Divide
    l = mergesort(a[:middle])
    r = mergesort(a[middle:])

    # Conquer
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

