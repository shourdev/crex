from stdlib import*
def isnum(str):
    if (str=="0"):
       return True
    if (str=="1"):
       return True
    if (str=="2"):
       return True
    if (str=="3"):
       return True
    if (str=="4"):
       return True
    if (str=="5"):
       return True
    if (str=="6"):
       return True
    if (str=="7"):
       return True
    if (str=="8"):
       return True
    if (str=="9"):
       return True
    return False
def tokenize(code):
    i=0
    tokens=[[],[]]
    while(i<len(code) and i!=len(code)):
       if (i!=len(code) and code[i]=="+"):
          append(tokens[0],"+")
          append(tokens[1],None)
          i=i+1
       if (i!=len(code) and code[i]=="*"):
          append(tokens[0],"*")
          append(tokens[1],None)
          i=i+1
       if (i!=len(code) and code[i]=="-"):
          append(tokens[0],"-")
          append(tokens[1],None)
          i=i+1
       if (i!=len(code) and code[i]=="/"):
          append(tokens[0],"+")
          append(tokens[1],None)
          i=i+1
       if (i!=len(code) and isnum(code[i])):
          str=code[i]
          i=i+1
          while(i!=len(code) and isnum(code[i])):
             str=str+code[i]
             i=i+1
          append(tokens[0],"number")
          append(tokens[1],str)
       else:
          cout("Lexical error, unexpected symbol: ",code[i])
          exit()
    return tokens
def makeast(type,node):
    ast=[]
    append(ast,type)
    append(ast,node)
    return ast
def numbernode(number):
    numnode=[]
    append(numnode,number)
    return makeast("number",numnode)
def binop(left,op,right):
    binopnode=[]
    append(binopnode,left)
    append(binopnode,op)
    append(binopnode,right)
    return makeast("binop",binopnode)
tokens2=[]
tokenindex=[0]
def primary():
    global tokens2;
    global tokenindex;
    if (tokens2[0][tokenindex[0]]=="number"):
       tokenindex[0]=tokenindex[0]+1
       return numbernode(tokens2[1][tokenindex[0]-1])
def factor():
    
    left=primary()
    global tokens2;
    global tokenindex;
    while(tokens2[0][tokenindex[0]]=="*" or tokens2[0][tokenindex[0]]=="/"):
       tokenindex[0]=tokenindex[0]+1
       right=primary()
       left=binop(left,tokens2[0][tokenindex[0]-1],right)
    return left
def term():
    
    left=factor()
    global tokenindex;
    global tokens2;
    while(tokens2[0][tokenindex[0]]=="+" or tokens2[0][tokenindex[0]]=="-"):
       tokenindex[0]=tokenindex[0]+1
       right=factor()
       left=binop(left,tokens2[0][tokenindex[0]-1],right)
    return left
def parse(tokens):
    global tokens2;
    tokens2=tokens
    cout(tokens2)
    return term()
def number(ast):
    return ast[1][0]
def binopeval(ast):
    left=evaluate(ast[1][0])
    right=evaluate(ast[1][2])
    if (ast[1][1]=="+"):
       return left+right
    if (ast[1][1]=="*"):
       return left*right
    if (ast[1][1]=="-"):
       return left-right
    if (ast[1][1]=="/"):
       return left/right
def evaluate(ast):
    if (ast[0]=="number"):
       return number(ast)
    if (ast[0]=="binop"):
       return binopeval(ast)
code=input()
evaluate(parse(tokenize(code)))
