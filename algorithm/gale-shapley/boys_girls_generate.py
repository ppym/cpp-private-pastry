import random
import os

max_count=10
lst=range(0,max_count)


f = open("boys.in", "w+")
for i in range(0,max_count):
	random.shuffle(lst)
	s=str(lst)
	s=s.replace(",","")
	s=s.replace("[","")
	s=s.replace("]","")+"\n"
	f.write(s)
f.close()

f = open("girls.in", "w+")
for i in range(0,max_count):
	random.shuffle(lst)
	s=str(lst)
	s=s.replace(",","")
	s=s.replace("[","")
	s=s.replace("]","")+"\n"
	f.write(s)
f.close()
