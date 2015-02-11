#import file
import random

f1=open('input1.txt','w')
i=0
lim=random.randint(0,1000)
while (i<lim):
	s1=random.randint(0,1000)
	s2=s1-1
	s3=s1+1
	p2=random.randint(0,10)
	p3=random.randint(0,10)
	f1.write(str(s1)+"\n")
	if s2>=0:
		if p2<=6:
			f1.write(str(s2)+"\n")
			i+=1
	if p3<=6:
		if (s3<1000):
			f1.write((str(s3)+"\n"))
	i+=2
f1.close()

f3=open('input2.txt','w')
f3.close()

lim2=random.randint(0,5)
i=1
while (i<lim2):
	with open('input1.txt','r') as source:
		data = [(random.random(), line) for line in source]
	data.sort()
	#print data
	with open('input2.txt','a') as target:
		for _, line in data:
			target.write( line )
	i+=1	
