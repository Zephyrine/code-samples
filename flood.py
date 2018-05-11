# python3

import heapq, sys

def get_vol(M, N, elev):
    vol = 0
    if N < 3 or M < 3:  # island too small to hold water
        return 0
    
    que = []  # empty priority queue (heap), sorted by elevation in asc order
    n = N-1
    m = M-1
    visited = [[False]*N for i in range(M)]  # set all as unvisited
    for i in range(M):  # push all border cells onto heap and set as visited
        heapq.heappush(que, (elev[i][0], (i, 0)))
        heapq.heappush(que, (elev[i][n], (i, n)))
        visited[i][0] = True
        visited[i][n] = True
    for i in range(1, n):
        heapq.heappush(que, (elev[0][i], (0, i)))
        heapq.heappush(que, (elev[m][i], (m, i)))
        visited[0][i] = True
        visited[m][i] = True
        # border cells hold volume 0

    while que:  # while heap is not empty
        h, (y, x) = heapq.heappop(que) # pop an element
        neighbors = [(y, x-1), (y-1, x), (y, x+1), (y+1, x)]  # possible neighbors
        for p, q in neighbors:  # for each neighbor
            if p < 0 or p > m or q < 0 or q > n:  # if it doesn't exist, skip
                continue
            if visited[p][q]:  # if it exists but is visited, skip
                continue
            if h > elev[p][q]:  # if the current min border is higher
                vol += h - elev[p][q]  # cell holds water, add its vol to total
            heapq.heappush(que, (max(elev[p][q], h), (p, q)))  # add to border
            visited[p][q] = True  # set neighbor as visited
            
    return vol    

if __name__ == '__main__':
    # process data  
    data = list(map(int, sys.stdin.read().split()))
    res = []
    j = 1
    for i in range(data[0]):  # for each island
        elev = [data[j+2+data[j+1]*k:j+2+data[j+1]*(k+1)]
                   for k in range(data[j])]  # get elevation data
        res.append(get_vol(data[j], data[j+1], elev))  # get vol for island
        j += data[j]*data[j+1] + 2  # move pointer to next island in raw dataset

    for each in res:  # for each result, output it
        print(each)