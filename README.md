# Lab3_Navigation
given a data file containing Graph information find the shortest path between two given vertices.
In the given file, lines starting with 
'c' represent comments; 
'p sp' is followed by two numbers : vertices numbers then edges numbers
'a' is followed by three numbers : vertice i, vertice j then distance between i and j;

data file sample 'jzh-road.gr'

c 1 shanghai
c 2 nanjing
c 3 hangzhou
c 4 suzhou
c 5 wuxi
c 6 nantong
c 7 changzhou
c question shanghai to nanjing 1 to 2
c answer 1->4->5->7->2 282
c
p sp 7 18
a 1 3 166
a 3 4 121
a 7 5 48
a 3 1 166
a 1 4 86
a 7 6 88
a 2 3 238
a 3 2 238
a 4 5 34
a 5 7 48
a 4 6 81
a 7 2 114
a 6 7 88
a 2 7 114
a 4 3 121
a 4 1 86
a 5 4 34
a 6 4 81
