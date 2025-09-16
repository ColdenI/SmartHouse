import  random

sc_1 = ("1","2","3","4","5","6","7","8","9","0","A","B","C","D","E","F","J","H","I","G","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z")
sc_2 = ("1","2","3","4","5","6","7","8","9","0","a","b","c","d","e","f","j","h","i","g","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z")
sc_3 = ("1","2","3","4","5","6","7","8","9","0","A","B","C","D","E","F","J","H","I","G","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","j","h","i","g","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z")

ko = int(input("kol= "))
sc = input("sc= ")
key=""
if sc == "1":
    for i in range(ko):
        i+=1
        key+=sc_1[random.randint(0,len(sc_1))-1]
        if i%5==0 and i!= ko:
            key+="-"

if sc == "2":
    for i in range(ko):
        i+=1
        key+=sc_2[random.randint(0,len(sc_2))-1]
        if i%5==0 and i!= ko:
            key+="-"

if sc == "3":
    for i in range(ko):
        i+=1
        key+=sc_3[random.randint(0,len(sc_3))-1]
        if i%5==0 and i!= ko:
            key+="-"


print(key)
input("\n\nend")