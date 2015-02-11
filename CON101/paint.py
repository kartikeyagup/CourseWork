from Tkinter import *
def move():
    global Dx,Dy
    x1,y1,x2,y2=w.coords(id1)
    if x1+Dx<=0 or x1+Dx>=190:
        Dx=-Dx
    if y1+Dy<=0 or y1+Dy>=190:
        Dy=-Dy
    w.coords(id1,x1+Dx,y1+Dy,x2+Dx,y2+Dy)
    root.after(50,move)

root=Tk()
w = Canvas(root, width=200, height=200,
           borderwidth=0,
           highlightthickness=0,
           background='white')
w.pack(padx=10,pady=10)
button1=Button(root,text='Move')
button1.pack()
button1.bind('<Button-1>',move)
Dx=1
Dy=1
id1=w.create_rectangle(3,7,3+10,7+10)
root.after(50,move)
root.mainloop()