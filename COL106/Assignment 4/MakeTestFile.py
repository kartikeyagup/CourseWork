import random;

chararr=[" ","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","."]
limt1=len(chararr)
print limt1
s1=""
f=open('input3.txt','w')

getbigrandom=random.randint(10000,1000000)
print getbigrandom
for i in range(getbigrandom):
	# s1+=chararr(random.randint(0,limt1-1))
	f.write(chararr[random.randint(0,limt1-1)])
# f.writeline()
