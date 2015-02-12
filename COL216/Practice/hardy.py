a,b,c,d=1,2,3,4
num1,num2=9, 91
found=False
while (not found):
	if d<20:
		d+=1
	else:
		if c<20:
			c+=1
			d=c+1
		else:
			d=2
			c=1
			if b<20:
				b+=1
			else:
				a+=1
				b=a+1

	print a,b,c,d
	num1=a**3 + b**3
	num2=c**3 + d**3
	if num1==num2:
		if a != c:
			found=True

print num1,a,b,c,d