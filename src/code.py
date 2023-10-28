array=[]
array.append([])
array.append([])
code=input()
i=0
while(i<len(code)):
    if (code[i]=="+"):
       array[0].append("Plus")
       array[1].append("None")
    i=i+1
print( array[0][0])
