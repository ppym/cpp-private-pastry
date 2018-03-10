import random
import os
import sys

max_count=int(sys.argv[1])

lst=range(0,max_count)

f = open("data.in", "w+")
random.shuffle(lst)
s=str(lst)
s=s.replace(",","")
s=s.replace("[","")
s=s.replace("]","")+"\n"
f.write(s)


