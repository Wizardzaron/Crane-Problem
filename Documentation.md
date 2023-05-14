# Exhaustive Alogrithm Pseudocode 
**Problem:** Get the route that maximizes the number of cranes reached while avoiding buildings.
**i/p:** a 2D array  of n > 0 numbers. 
**o/p:** the path that gives the most cranes and least buildings.

**Pseudocode**
Cranes[5] = {#, #, #, #, #}
Buildings[5] = {#, #, #, #, #}
Path[5][9]
best = None


Time Complexity: O(2^n)

# Dynamic Algorithm Pseudocode 
**Problem:** Get the route that maximizes the number of cranes reached while avoiding buildings.
**i/p:** a 2D array  of n > 0 numbers. 
**o/p:** the path that gives the most cranes and least buildings.

**Pseudocode**
Cranes[5] = {#, #, #, #, #}
Buildings[5] = {#, #, #, #, #}
Path[5][9]

For row = 0 to n - 1 do --> n - 1 + 1 = n times
    For column = 0 to m - 1 do -->
        if row OR column == 0 --> 2 tu
            Path[row][column] = 0 --> 1 tu
        else if Building[row] <= column --> 1 tu
            Path[row][column] = max(Cranes[row] + Path[row - 1][column - Buildings[row]],
            Path [row - 1][column]) --> 5 tu
        else Path[row][column] = Path[row - 1][column] --> 2 tu
        endif
    endfor
return Path[row][column]
endfor

Time Complexity: O(n^2)