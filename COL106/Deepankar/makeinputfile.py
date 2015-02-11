chars=["Erdos","Sheldon","Leonard","Leslie","Amy","Bernadette","Penny","Raj","Howard","Stuart"]

f1=open('rawinp.txt','w')
for elem in chars:
	f1.write("1\n")
	f1.write(elem+"\n")
	f1.write("y\n")



for elem in chars:
	for elem2 in chars:
		f1.write("2\n")
		f1.write(elem+"\n")
		f1.write(elem2+"\n")
		f1.write("y\n")


for elem in chars:
	for elem2 in chars:
		f1.write("3\n")
		f1.write(elem+"\n")
		f1.write(elem2+"\n")
		f1.write("y\n")

