i=30
j=30
height=100
width=100
i=0
while(i<height):
    j=0
    while(j<width):
       if (i==0 or i==width-1 or j==0 or j==height-1):
          print("#",end='')
       else:
          print(" ",end='')
       j=j+1
    print("\n",end='')
    i=i+1
