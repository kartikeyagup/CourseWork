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

lim2=random.randint(1,5)
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

def splitandstuff(name1):
	f1=open(name1,'r')
	content= f1.readlines()
	bigarr2=[-1]*101
	bigarr3=[0]*5
	t1=[0,0,0,0,0]
	i=0
	while (i<5):
		bigarr3[i]=[0,[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],0]
		i+=1
	bigarr=[0]*1001
	i=0
	while (i<=1000):
		bigarr[i]=[i,i/10,0]
		i+=1
	j=0
	# print len(bigarr[501])
	for line in content:
		num1=int(line[:-1])
		# print num1
		if (bigarr2[num1/10]==-1):
			if bigarr3[0][2]<20:
				bigarr3[0][1][num1/10]=num1/10
				bigarr3[0][2]+=1
				if bigarr3[0][2]==1:
					t1[0]=j;
				bigarr2[num1/10]=0
			elif bigarr3[1][2]<20:
				bigarr3[1][1][num1/10]=num1/10
				bigarr3[1][2]+=1
				if bigarr3[1][2]==1:
					t1[1]=j;
				bigarr2[num1/10]=1
			elif bigarr3[2][2]<20:
				bigarr3[2][1][num1/10]=num1/10
				bigarr3[2][2]+=1
				if bigarr3[2][2]==1:
					t1[2]=j;
				bigarr2[num1/10]=2
			elif bigarr3[3][2]<20:
				bigarr3[3][1][num1/10]=num1/10
				bigarr3[3][2]+=1
				if bigarr3[3][2]==1:
					t1[3]=j;
				bigarr2[num1/10]=3
			elif bigarr3[4][2]<20:
				bigarr3[4][1][num1/10]=num1/10
				bigarr3[4][2]+=1
				if bigarr3[4][2]==1:
					t1[4]=j;
				bigarr2[num1/10]=4
			bigarr[num1][2] +=1 
		j+=1
	cost1=0
	cost2=0
	pqr=0
	while (pqr<5):
		if t1[pqr]!=0:
			cost1+=1+1*(j-t1[pqr]) + (0.1*(t1[pqr]))
		pqr+=1
		cost2+=1+j
	print "cost without heuristic " + str(cost2)
	print "cost with heuristic " + str(cost1)
	# print 
	# print bigarr[0]
	# bigarr2=[0]*101
	# for alpha in bigarr:
		# print alpha
		# bigarr2[alpha[1]] += alpha[2]
	# return (bigarr3,t1)

splitandstuff("input2.txt")
