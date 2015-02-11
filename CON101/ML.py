import math
f1=open('train')
lines=f1.readlines()
lines=lines[0:9000]
bigarraywords=[]
freqspam=[]
freqham=[]
numberspam,numberham=0,0
for lineread in lines:
	splittedline=lineread.split()
	j,cons=2,1
	limt=len(splittedline)
	if (splittedline[1]=='spam'):
		numberspam+=1
		cons=0
	else:
		numberham+=1
	while (j<limt):
		if (splittedline[j] in bigarraywords):
			indexnumber=bigarraywords.index(splittedline[j])
		else:
			indexnumber=len(bigarraywords)
			bigarraywords.append(splittedline[j])
			freqspam.append(0)
			freqham.append(0)
		if (cons==1):
			freqspam[indexnumber]+=1
		else:
			freqham[indexnumber]+=1
		j+=2
	# splitted
	# print splittedline

totalham=1.0*sum(freqham)
totalspam=1.0*sum(freqspam)
totalwords=totalspam+totalham
# totalemail=
# print ("vocab", len(bigarraywords))

# for ep1 in bigarraywords:
	# print ep1
# orgspam=(numberspam*1.0)/(numberspam+numberham)
# orgham=(numberham*1.0)/(numberspam+numberham)

orgspam=totalspam/totalwords
orgham=totalham/totalwords

# print orgspam

lim1,i=len(bigarraywords),0
while (i<lim1):
	freqham[i]*=1.0
	freqspam[i]*=1.0
	tot1=freqspam[i]+freqham[i]
	freqham[i]/=tot1
	freqspam[i]/=tot1
	i+=1

# print "number spam", numberspam, "number ham", numberham
# print "Starting with test"

# countspam,countham=0,0
# f3=open('train')
# lines=f3.readlines()
# # lines=lines[0:2000]
# for lineread in lines:
# 	splittedline=lineread.split()
# 	j,limt2=2,len(splittedline)
# 	prospam,proham=orgspam,orgham
# 	pspam,pham=1.0,1.0
# 	while (j<limt2):
# 		if (splittedline[j] in bigarraywords):
# 			in1=bigarraywords.index(splittedline[j])
# 			prospam*=freqspam[in1]
# 			proham*=freqham[in1]
# 			pham*=freqham[in1]
# 			pspam*=freqspam[in1]
# 			# prospam/=(freqham[in1]+freqspam[in2])
# 		j+=2
# 	if (prospam>=proham):
# 		countspam+=1
# 	else:
# 		countham+=1

# print "for training" ,("ham", countham,"spam", countspam)



countspam,countham,numham,numspam,lspam,lham=0,0,0,0,0,0
f2=open('test')
lines=f2.readlines()
matching=0
for lineread in lines:
	splittedline=lineread.split()
	j,limt2=2,len(splittedline)
	if splittedline[1]=='spam':
		numspam+=1
	else:
		numham+=1
	prospam,proham=math.log10(orgspam),math.log10(orgham)
	pspam,pham=10000.0,1.0
	while (j<limt2):
		if (splittedline[j] in bigarraywords):
			in1=bigarraywords.index(splittedline[j])
			if freqspam[in1]>0.0:
				prospam+=(math.log10(freqspam[in1]))*(int(splittedline[j+1]))
			# print freqham[in1]
			if freqham[in1]>0.0:
				proham+=(math.log10(abs(freqham[in1])))*(int(splittedline[j+1]))
			pspam*=freqspam[in1]**(int(splittedline[j+1]))
			pham*=freqham[in1]**(int(splittedline[j+1]))
			# prospam/=(freqham[in1]+freqspam[in2])
		j+=2
	if (prospam>=proham):
		countspam+=1
		if splittedline[1]=='spam':
			matching+=1
	else:
		countham+=1
		if splittedline[1]!='spam':
			matching+=1
	if (pspam>=pham):
		lspam+=1
	else:
		lham+=1
	
# print orgham



# print ("ham", countham,"spam",countspam)
# print "actual" , ("ham", numham, "spam", numspam)
# print "actual 1.0" , ("ham", lham, "spam", lspam)

print "accuracy is", (1000-matching)*1.0/10