import random


map_len_empl = 1




mapstr = str(random.randint(1, 30)) + "\n"
strpath = ""
counterroom = 1

listeSalle = [["0", 50, 50]]

mapstr += "##start\n"
mapstr += "0 10 10\n"

def getCoorNotInListe(listeSalle):
    x = 0
    y = 0
    b = True
    while b :
        x = random.randint(0, 100)
        y = random.randint(0, 100)
        b = False
        for salle in listeSalle:
            if salle[1] == x and salle[2] == y :
                b = True
                break
    return (x,y)

for i in range(random.randint(map_len_empl, map_len_empl * 5)):
    x, y = getCoorNotInListe(listeSalle)
    listeSalle += [[str(counterroom), x, y]]
    mapstr += str(counterroom) + " " + str(x) + " " + str(y) + "\n"
    strpath += str(counterroom - 1) + "-" + str(counterroom) + "\n"
    counterroom+=1
x, y = getCoorNotInListe(listeSalle)
mapstr += "##end\n" 
listeSalle += [[str(counterroom), x, y]]
mapstr += str(counterroom) + " " + str(x) + " " + str(y) + "\n"
strpath += str(counterroom - 1) + "-" + str(counterroom) + "\n"
counterroom+=1


for i in range(random.randint(map_len_empl, map_len_empl * 15)):
    x, y = getCoorNotInListe(listeSalle)
    b = True
    if b :
        listeSalle += [[str(counterroom), x, y]]
        mapstr += str(counterroom) + " " + str(x) + " " + str(y) + "\n"
        for i in range(random.randint(2, 4)):
            r1 = random.randint(0, counterroom)
            r2 = random.randint(0, counterroom)
            testpath =  str(r1) + "-" + str(r2) + "\n"
            testpath2 =  str(r2) + "-" + str(r1) + "\n"
            if (not testpath in strpath) and (not testpath2 in strpath) and r1 != r2:
                strpath += testpath
    counterroom+=1







mapstr += strpath

print(mapstr)