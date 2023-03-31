from re import X


balance=0


def order(x,y,balance):

    balance=y+balance
    print(x,"save",y)

a=order
b=order
balance=a("James",10,balance)
balance=b("Peter",1,balance)
print(balance)