from sys import argv 
from sys import stderr
from random import randint


def get_array(size):
    array = []
    for i in range(size):
        array.append(randint(0, 100000000) % 100 + 1) 
    return array


def show_array(array, size, message = None): 
    if message is not None:
        print(message)
    for i in range(size):
        print(array[i], end = " ")
    print()


def merge(arr, p, q, r):
    N1 = q - p + 1
    N2 = r - q 

    arr1 = []
    arr2 = []

    for i in range(N1):
        arr1.append(arr[p + i])

    for i in range(N2):
        arr2.append(arr[q + 1 + i])

    i = 0
    j = 0
    k = 0

    while(True):

        if(arr1[i] <= arr2[j]):
            arr[p + k] = arr1[i]
            i += 1
            k += 1
            if(i == N1):
                while(j < N2):
                    arr[p + k] = arr2[j]
                    j += 1
                    k += 1
                break

        else:
            arr[p + k] = arr2[j]
            j += 1
            k += 1
            if(j == N2):
                while(i < N1):
                    arr[p + k] = arr1[i]
                    i += 1
                    k += 1
                break
    
    arr1.clear()
    arr2.clear()



def merge_sort(array, p, r):
    if (p < r):
        q = (p + r) // 2
        merge_sort(array, p, q)
        merge_sort(array, q + 1, r)
        merge(array, p, q, r)


if(len(argv) != 2):
    print("Usage Error: Enter length of an array as command line argument", file = stderr)
    exit(8)
size = int(argv[1])
array = get_array(size)
show_array(array, size, "Before sorting:")
merge_sort(array, 0, size - 1)
show_array(array, size, "After sorting:")
array.clear()