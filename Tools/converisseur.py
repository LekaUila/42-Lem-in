fl = input("")
sl =input("")
liste_room_txt = ""
listetext = []
inpu = "yolo"
i = 0
while (True):
    inpu  = input("")
    if inpu[0: 5] == "#Here":
        break
    elif inpu[0] != "#" and not "-" in inpu:
        # print("adding " + inpu + " in liste room")
        liste_room_txt += inpu + "\n"
    else :
        # print("adding " + inpu + " in liste text")
        listetext.append([i, inpu])
    i+=1





import random

def getCoorNotInListe(listeSalle):
    x = 0
    y = 0
    b = True
    while b :
        x = random.randint(0, 120)
        y = random.randint(0, 85)
        b = False
        for salle in listeSalle:
            if salle[1] == x and salle[2] == y :
                b = True
                break
    return [x,y]


step = 0

listeSalle = []
strsave = ""


for i in range(len(liste_room_txt)):

    if step == 0 and liste_room_txt[i] != " ":
        strsave += liste_room_txt[i]
    elif step == 0 and liste_room_txt[i] == "-":
        step = 1
    elif step == 0 and liste_room_txt[i] == " ":
        step = 1
        liste_temp = [strsave] + getCoorNotInListe(listeSalle)
        listeSalle.append(liste_temp)
        strsave = ""
    elif step == 1 and liste_room_txt[i] == "\n":
        step = 0
        strsave = ""
        
# print(listeSalle)
i = 0
j = 0
print(fl)
print(sl)
for salle in listeSalle:
    while (listetext[j][0] == i):
        print(listetext[j][1])
        i+=1
        j+=1
    print(salle[0] + " " + str(salle[1]) + " " + str(salle[2]))
    i+=1
while (j < len(listetext) and listetext[j][0] == i):
    print(listetext[j][1])
    i+=1
    j+=1

    

    
    

