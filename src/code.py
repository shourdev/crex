from stdlib import*
def isnum(num):
    if (num[0]=="0"):
       return True
    if (num[0]=="1"):
       return True
    if (num[0]=="2"):
       return True
    if (num[0]=="3"):
       return True
    if (num[0]=="4"):
       return True
    if (num[0]=="5"):
       return True
    if (num[0]=="6"):
       return True
    if (num[0]=="7"):
       return True
    if (num[0]=="8"):
       return True
    if (num[0]=="9"):
       return True
    else:
       return False
class token:
    tokenname = ""
    tokenvalue = ""
def lexer(code):
    tokens=[]
    token_index = 0
    i=0
    while(1):
       if (i!=len(code) and isnum(code[i])):
          result = ""
          while(i!=len(code) and isnum(code[i])):
             result=result+code[i]
             i=i+1
          num = token()
          num.tokenname="intliteral"
          num.tokenvalue=result
          addlist(tokens,token_index,num)
          token_index=token_index+1
       if (i!=len(code) and code[i]=="+"):
          add = token()
          add.tokenname="add"
          add.tokenvalue=""
          addlist(tokens,token_index,add)
          token_index=token_index+1
          i=i+1
       if (i==len(code)):
          eof = token()
          eof.tokenname="EOF"
          eof.tokenvalue=""
          addlist(tokens,token_index,eof)
          token_index=token_index+1
          break
    return tokens
tokens=lexer("234+232+234+352+52")
i=0
while(i<len(tokens)):
    cout("Token name: ",tokens[i].tokenname," Token value: ",tokens[i].tokenvalue,"\n")
    i=i+1
