# python3

import sys

def seek_(N):
# Given a string, finds the first number
# whose highest position is found in the needle.
# e.g. 91011 -> 9, 99091 -> 90, 54321 -> 15433
    
# Zero is a special case:
    if int(N) == 0:
        return [10**len(N), -1] # return the corresponding number
                                # and a negative offset
    
# See if the needle can contain a k-digit number,
# with k from 1 to the needle's length.

    for k in range(1, len(N)+1):  # for each slice length

        ans = []  # empty array of values

        for j in range(k):  # for each offset of said length

            if N[j] == '0':
                continue  # a natural number can't have a leading zero,
                          # e.g. '8099100' is not a match
            else:
                s = N[j : j+k]  # get 1st substring ("slice")
                                # in python, out-of-bound range indices are ok                    
        
            if j != 0:  # checking the tail
                # could've used regex
                tail = str(int(N[:j])+1)[-j:]  # tail incremented and snipped
                                               # variable used for readability
                if tail[:j-k+len(s)] != s[k-j:]:  # relevant substrings
                    continue  # the current (k, j) pair is not a match

                if j + k > len(N):
                    ans.append([int(''.join([s[:k-j], tail])), j])
                    continue        
                
            
            i = j  # now to check the number going forward
            while True:
                i += len(s)  # get next position
                s = str(int(s) + 1)  # slice incremented
                
                if s == N[i : i+len(s)]:  # if it matches next needle section
                    continue  # if slices match, check the next slice
                
                elif s[:len(N[i:])] == N[i:]:  # if its beginning matches
                                               # the remainder of the needle                                               
                    ans.append([int(N[j : j+k]), j])  # record a match
                    break  # and exit
                else:  
                    break  # mismatch, pick a new offset

        if ans != []:
            row = [row[0] for row in ans]  # python's min is awkward
            min_ = row.index(min(row))  # the minimum with a given k
            return ans[min_]  # returns the first number and offset   
                


def count_(n):
# returns number of digits preceding the nth component in the sequence
# aka position of first digit of explicit n, starting with zero
# count_(100) == 189
    pos = 0
    for i in range(1, len(str(n))):
        pos += i * 9 * 10**(i - 1)
    pos += (n - 10**(len(str(n))-1)) * (len(str(n)))
    return pos


def locate(s):
# calculates the actual answer given a subsequence

    found = seek_(s)  # get the first number and offset
    #  subtract offset from the length of the preceding string and add 1
    return count_(found[0]) - found[1] + 1
    

if __name__ == '__main__':
  
    data = list(map(str, sys.stdin.read().split()))  # read input

    for each in data:
        print(locate(each))  # for each line, process it and output result