def cout(*args):
    for arg in args:
        print(arg,end='')
def cin():
    return input()
def totype(type,val):
    if(type=="int"):
        return int(val)
    if(type=="str"):
        return str(val)
    if(type=="float"):
        return float(val)
    else:
        print("Crex Runtime Error!")
        print(type," is not a valid type!")
        exit()
