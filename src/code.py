class student:
    name = "null"
    offence = "null"
    level = 0
students=[]
def add(name,offence,level):
    student1 = student()
    student1.name=name
    student1.offence=offence
    student1.level=level
    students.append(student1)
def printstudents():
    print("All the students \n")
    i = 0
    while(i<len(students)):
       print(i,")Name: ",students[i].name)
       print("Offence: ",students[i].offence)
       print("Level of offence: ",students[i].level,"\n")
       i=i+1
def modify():
    printstudents()
    print("Enter the index of what student you want to modify:")
    index=input()
    print("Enter new offence:")
    newoffence=input()
    print("Enter new level:")
    newlevel=input()
    students[int(index)].offence=newoffence
    students[int(index)].level=int(newlevel)
while(True):
    print("Enter name:")
    name=input()
    print("Enter offence:")
    offence=input()
    print("Enter level of offence:")
    level=input()
    if (name!="" and offence!="" and level!=""):
       add(name,offence,int(level))
    moreinput=input()
    if (moreinput=="quit"):
       break
    if (moreinput=="edit"):
       modify()
    if (moreinput=="print"):
       printstudents()
