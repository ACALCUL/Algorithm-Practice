import math

cnt=int(input())
input_list=[int(x) for x in input().split(" ")]
input_list.sort()

print("{} {} {}".format(input_list[0], input_list[math.ceil(cnt/2)-1],input_list[cnt-1]))

