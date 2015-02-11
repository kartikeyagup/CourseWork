import copy

fileread=open('cipher0.txt')
string1=fileread.read()

splitted=list(string1)

possiblechars=[]

for i in xrange(127):
	possiblechars.append(chr(i))

countchrs=[0]*256

for i in xrange(256):
	countchrs[i]=[i,chr(i), splitted.count(chr(i))]

filtered=[]
for elem in countchrs:
	if elem[2]:
		filtered.append(elem)

filtered.sort(key=lambda x: x[2])
filtered=filtered[::-1]

print len(filtered)

corrected=copy.deepcopy(filtered)
# corrected[0].append(' ')
# corrected[1].append('t')
# corrected[2].append('a')
# corrected[3].append('o')
# corrected[4].append('i')
# corrected[5].append('n')

cipphercode={}
for elem in corrected:
	cipphercode[elem[1]]=elem[1]

# relativeordering=[' ','e','t','a','o','i','n','s','r','h','d','l','u','c','m','f','y','w','g','p','b','v','k','x','q','j','z']
# for j in xrange(len(relativeordering)):
	# cipphercode[corrected[j][1]]=relativeordering[j]

cipphercode['=']=' '
cipphercode['\\']=','
cipphercode['&']='.'
cipphercode['?']='-'
cipphercode['*']='"'
cipphercode['#']=':'
cipphercode['`']='\\'
cipphercode[']']='_'



cipphercode['a']='q'
cipphercode['b']='s'
cipphercode['c']='a'
cipphercode['d']='g'
cipphercode['e']='f'
cipphercode['f']='j'
cipphercode['g']='h'
cipphercode['h']='y'
cipphercode['i']='b'
cipphercode['j']='v'
cipphercode['k']='n'
cipphercode['l']='r'
cipphercode['m']='p'
cipphercode['n']='x'
cipphercode['o']='i'
cipphercode['p']='e'
cipphercode['q']='u'
cipphercode['r']='t'
cipphercode['s']='k'
cipphercode['t']='z'
cipphercode['u']='l'
cipphercode['v']='w'
cipphercode['w']='m'
cipphercode['x']='c'
cipphercode['y']='d'
cipphercode['z']='o'
# cipphercode['b']='s'



cipphercode['A']='S'
cipphercode['B']='P'
cipphercode['C']='M'
cipphercode['D']='W'
cipphercode['F']='D'
cipphercode['G']='E'
cipphercode['J']='Y'
cipphercode['L']='R'
cipphercode['N']='I'
cipphercode['P']='J'
cipphercode['Q']='F'
cipphercode['R']='U'
cipphercode['S']='N'
cipphercode['T']='H'
cipphercode['V']='B'
cipphercode['X']='T'
cipphercode['Z']='A'



 # Nt is iktelestikd


ans=""
for elem in splitted:
	ans+= cipphercode[elem]

print ans
# print cipphercode
# print filtered
# print corrected
# print splitted
