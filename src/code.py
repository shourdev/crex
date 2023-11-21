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
def maketoken(type,value):
    token=[]
    append(token,type)
    append(token,value)
    return token
def tokenize(code):
    i=0
    tokens=[]
    while(i<len(code) and i!=len(code)):
       if (i!=len(code) and code[i]=="+"):
          append(tokens,maketoken("+",None))
          i=i+1
       if (i!=len(code) and code[i]=="*"):
          append(tokens,maketoken("*",None))
          i=i+1
       if (i!=len(code) and code[i]=="-"):
          append(tokens,maketoken("-",None))
          i=i+1
       if (i!=len(code) and code[i]=="/"):
          append(tokens,maketoken("/",None))
          i=i+1
       if (i!=len(code) and isnum(code[i])):
          str=code[i]
          i=i+1
          while(i!=len(code) and isnum(code[i])):
             str=str+code[i]
             i=i+1
          append(tokens,maketoken("number",str))
       else:
          cout("Lexical error, unexpected symbol: ",code[i])
          exit()
    append(tokens,maketoken("EOF",None))
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
def unarynode(op,node):
    unarynode=[]
    append(unarynode,op)
    append(unarynode,node)
    return makeast("unary",unarynode)
def binop(left,op,right):
    binopnode=[]
    append(binopnode,left)
    append(binopnode,op)
    append(binopnode,right)
    return makeast("binop",binopnode)
tokenslist=[]
tokenindex=[0]
def peek():
    return tokenslist[0][tokenindex[0]]
def previous():
    return tokenslist[0][tokenindex[0]-1]
def isatend():
    return peek()[0]=="EOF"
def match(tokentype):
    if ( not isatend() and peek()[0]==tokentype):
       tokenindex[0]=tokenindex[0]+1
       return True
    return False
def primary():
    if (match("number")):
       return numbernode(int(previous()[1]))
def unary():
    if (match("-")):
       left=primary()
       return unarynode("-",left)
    else:
       return primary()
def factor():
    left=unary()
    while(match("*") or match("/")):
       op=previous()[0]
       right=unary()
       left=binop(left,op,right)
    return left
def term():
    left=factor()
    while(match("+") or match("-")):
       op=previous()[0]
       right=factor()
       left=binop(left,op,right)
    return left
def parse(tokens):
    append(tokenslist,tokens)
    return term()
def unaryeval(ast):
    if (ast[1][0]=="-"):
       return -evaluate(ast[1][1])
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
    if (ast[0]=="unary"):
       return unaryeval(ast)
    if (ast[0]=="binop"):
       return binopeval(ast)
cout("Enter the expression:")
cout(evaluate(parse(tokenize(cin()))))
