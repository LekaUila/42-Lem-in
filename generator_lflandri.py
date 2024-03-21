import random
mapstr = str(random.randint(0, 30)) + "\n"
strpath = ""
counterroom = 1

listeSalle = [["0", 50, 50]]

mapstr += "##start\n"
mapstr += "0 10 10\n"

for i in range(random.randint(10, 25)):
    listeSalle += [[str(counterroom), 12 + i * 2, 12 + i * 2]]
    mapstr += str(counterroom) + " " + str(12 + i * 2) + " " + str(12 + i * 2) + "\n"
    strpath += str(counterroom - 1) + "-" + str(counterroom) + "\n"
    counterroom+=1
s = counterroom
mapstr += "##end\n" 
listeSalle += [[str(counterroom), 10 + s * 2, 10 + s * 2]]
mapstr += str(counterroom) + " " + str(10 + s * 2) + " " + str(10 + s * 2) + "\n"
strpath += str(counterroom - 1) + "-" + str(counterroom) + "\n"
counterroom+=1


for i in range(random.randint(3, 50)):
    x = random.randint(0, 100)
    y = random.randint(0, 100)
    b = True
    for salle in listeSalle:
        if salle[1] == x and salle[2] == y :
            b = False
            break
    if b :
        listeSalle += [[str(counterroom), x, y]]
        mapstr += str(counterroom) + " " + str(x) + " " + str(y) + "\n"
        for i in range(random.randint(2, 4)):
            r1 = random.randint(s, counterroom)
            r2 = random.randint(0, counterroom)
            testpath =  str(r1) + "-" + str(r2) + "\n"
            testpath2 =  str(r2) + "-" + str(r1) + "\n"
            if (not testpath in strpath) and (not testpath2 in strpath) and r1 != r2:
            	strpath += testpath
    counterroom+=1







mapstr += strpath

print(mapstr)