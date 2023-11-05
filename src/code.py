from stdlib import*
class token:
    tokenname = ""
    tokenvalue = ""
def lexer(code):
    i=0
    tokens=[]
    tokenindex = 0
    while(i<len(code)):
       if (code[i]=="+"):
          add = token()
          add.tokenname="add"
          add.tokenvalue=""
          i=i+1
          addlist(tokens,tokenindex,add)
          tokenindex=tokenindex+1
    return tokens
tokens=lexer("+++++++")
i=0
while(i<len(tokens)):
    cout("Token name: ",tokens[i].tokenname," Token value: ",tokens[i].tokenvalue,"\n")
    i=i+1
