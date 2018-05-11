# python3
import sys
import random


def partition3(a, lp, rp):
    x = a[lp]
    m1 = lp
    m2 = lp
    for i in range(lp + 1, rp + 1):
        if a[i] < x:
            m2 += 1
            a[i], a[m1], a[m2] = a[m2], a[i], a[m1]
            m1 += 1
        elif a[i] == x:
            m2 += 1
            a[m2], a[i] = a[i], a[m2]
    return m1, m2


def partition2(a, lp, rp):
    x = a[lp]
    j = lp
    for i in range(lp + 1, rp + 1):
        if a[i] <= x:
            j += 1
            a[i], a[j] = a[j], a[i]
    a[lp], a[j] = a[j], a[lp]
    return j


def randomized_quick_sort(a, lp, rp):
    if lp >= rp:
        return
    k = random.randint(lp, rp)
    a[lp], a[k] = a[k], a[lp]
    # use partition3
    m1, m2 = partition3(a, lp, rp)
    randomized_quick_sort(a, lp, m1 - 1)
    randomized_quick_sort(a, m2 + 1, rp)


if __name__ == '__main__':
    data = sys.stdin.read()
    n, *arr = list(map(int, data.split()))
    randomized_quick_sort(arr, 0, n - 1)
    for _ in arr:
        print(_, end=' ')
