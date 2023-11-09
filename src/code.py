from stdlib import*
class intnode:
    num = None
class addnode:
    left = None
    right = None
class ast_node:
    node = None
intno =intnode()
intno.num=2
intno2 =intnode()
intno2.num=2
add =addnode()
add.left=intno
add.right=intno2
node =ast_node()
ast_node.node=add
