from stdlib import*
def test():
    cout("Hello outer!")
    def test2():
       cout("hello inner!")
    return test2
test()()
