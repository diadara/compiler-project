f = open("newGram.txt")
lines = f.readlines();
a= []
for l in lines:
    a += l.split(" ")
for i in set(a):
    if i.startswith("TK"):
        print i
for i in set(a):
    if not i.startswith("TK"):
        print i
        
    
  










