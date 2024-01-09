import serial
import mysql.connector as MC

console = 1 #affiche les trames et les valeurs dans la console
relax = 0   #ignore les mauvais checksums et fin de trames (console doit etre = 1)

'''
6 bits partie entière vent en km/h (max 63)
7 bits partie décimale vent km/h
4 bits direction vent
3 bits indice uv
14 bits lumière visible 16 383
1 bit signe vent
6 bits partie entière température (-63 ~ 63)
4 bits partie décimale température
4 bits partie entière pluie (max 15)
4 bits partie décimale pluie
8 bits checksum


total:
61 bits,
7 octets 5 bits


décripté:
0    1     2    3     4     5    6     7     8    9    10   11    12    13   14    15
aaaa aabb  bbbb bccc  cddd eeee  eeee eeee  eeff ffff  kggg ghhh  hiii ijjj  jjjj j000

a entier vent
b decimal vent
c direction vent
d uv
e visible
f entier temperature
k signe vent
g decimal temperature
h entier pluie
i decmial pluie
j checksum


encrypté:
    1          2          3          4          5           6          7           8
ghhh eeee1 bbbb eeff  ijjj cddd  aaaa j000  ffff bccc  eeee3 hiii  aabb jjjj  eeee2 kggg
 1     11  1 1     1   11  11     1 1   11   1    11   1 1     11  1    11      1    1 1

1 = bit inversé

'''

def insert_valeur(vent,pluie,temperature,visible,direc,uv):
    query = "INSERT INTO valeur_station (vitesse_vent, valeur_pluie, valeur_termometre, visible, indice_tableau_direction_vent, valeur_ultraviolet) VALUES (%s, %s, %s, %s, %s, %s)"
    args = (vent, pluie, temperature, visible, direc, uv)

    try:
        conn = MC.connect(host='localhost', database ='station', user='adminSQL', password='StationSQL')
        cursor = conn.cursor()
        cursor.execute(query,args)
        conn.commit()
    except MC.Error as err:
        print(err)
    finally:

        cursor.close()
        conn.close()






def printval():
    # print("vent entier: " + str(vent_ent))
    # print("vent decimal: " + str(vent_dec))
    print("indice vent: " + str(dir))
    print("indice indice uv: " + str(uv))
    print("visible: " + str(visible))
    # print("signe: " + str(signe))
    # print("temperature entier: " + str(temp_ent))
    # print("temperature decimal: " + str(temp_dec))
    # print("pluie entier: " + str(plui_ent))
    # print("pluie decimal: " + str(plui_dec))
    # print(" ")

    print("vitesse vent finale: " + str(vitesse_vent))
    print("temperature finale: " + str(temperature))
    print("valeur pluie finale: " + str(valeur_pluie))

    '''
    for a in range(16):
        print(str(a) + " " + hex(nibble[a]))
    '''

he = ("0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F")

def conv(a):
    return he[a>>4] + he[a&15]

inp = serial.Serial('/dev/ttyUSB0',9600) #,serial.EIGHTBITS,serial.PARITY_NONE,serial.STOPBITS_ONE,3) #le dernier chiffre c'est le timeout en secondes


tab = [0] * 8 #comment on fait pour déclarer un tableau vide avec une taille définie dans que python fasse nimp' ?

nibble = [0] * 16 #ici aussi

xor = (0x43, 0xa1, 0x6c, 0x53, 0x46, 0xa3, 0x8c, 0x25)

nibble_order = (11,5,2,8,13,4,0,15,9,3,7,12,1,14,6,10)



#début du vrai programme (?)

conn = None
cursor = None
try:
    conn = MC.connect(host='localhost', database='station', user='adminSQL', password='StationSQL')
    cursor = conn.cursor()
    query = "SELECT vitesse_vent FROM valeur_station ORDER BY vitesse_vent DESC LIMIT 1"
    cursor.execute(query)

    result = cursor.fetchone()
except MC.Error as err:
    print(err)
finally:
    if cursor is not None:
        cursor.close()
    if conn is not None:
        conn.close()








inp.reset_output_buffer() #nécessaire ?

while 1:
    inp.reset_input_buffer()


    """
    En vrai, faudrait mettre plus pour éviter une désynchronisation, mais après ça prends plus
    de temps à écrire dans la base de donnée et surtout, ça écrit de manière irrégulière.
    """
    rec = inp.read(8)

    if len(rec)==8:

        clc_checksum = 0
        for a in range (8):

            tab[a] = rec[a] ^ xor[a]
            nibble[nibble_order[a*2]] = tab[a] >> 4
            nibble[nibble_order[(a*2)+1]] = tab[a] & 15

        #découpage du gâteau
        vent_ent = (nibble[0]<<2)+ (nibble[1]>>2)
        vent_dec = ((nibble[1] & 3)<<5) + (nibble[2]<<1) + (nibble[3]>>3)
        dir = ((nibble[3] & 7)<<1) + (nibble[4]>>3)
        uv = nibble[4] & 7
        visible = (nibble[5]<<10) + (nibble[6]<<6) + (nibble[7]<<2) + (nibble[8]>>2)

        temp_ent = ((nibble[8] & 3)<<4) + nibble[9]
        signe = nibble[10]>>3
        temp_dec = ((nibble[10] & 7)<<1) + (nibble[11]>>3)

        plui_ent = ((nibble[11] & 7)<<1) + (nibble[12]>>3)
        plui_dec = ((nibble[12] & 7)<<1) + (nibble[13]>>3)

        checksum = (((nibble[13] & 7)<<5) + (nibble[14]<<1) + (nibble[15]>>3))
        clc_checksum = (vent_ent + vent_dec + dir + uv + visible + temp_ent + signe + temp_dec + plui_ent + plui_dec)%256

        if signe:
            signe = '-'

        vitesse_vent = float(str(vent_ent) + "." + str(vent_dec))
        temperature = float(str(signe) + str(temp_ent) + "." + str(temp_dec))
        valeur_pluie = float(str(plui_ent) + "." + str(plui_dec))

        if console:
            print()
            print("longueur de la trame: " + str(len(rec)) + " octets")
            print()
            for a in range (8):
                print(conv(rec[a]))
            print()
            print("checksum lu: " + str(checksum))
            print("clc checksum: " + str(clc_checksum))

        if relax:
            if console:
                if checksum != clc_checksum:
                    print("Attention, mauvais checksum !")
                if (nibble[15]&7)!=0:
                    print("Attention, les 3 derniers bits de la trame ne sonts pas 0 !")

                printval()
                insert_valeur(vitesse_vent, valeur_pluie, temperature, visible, dir, uv)
        else:
            if console:
                if checksum != clc_checksum:
                    print("Erreur checksum !")
                if (nibble[15]&7)!=0:
                    print("Erreur, les 3 derniers bits de la trame ne sonts pas 0 !")
                if checksum == clc_checksum and (nibble[15]&7)==0:
                    printval()
                    insert_valeur(vitesse_vent, valeur_pluie, temperature, visible, dir, uv)
            elif checksum == clc_checksum and (nibble[15]&7)==0:
                insert_valeur(vitesse_vent, valeur_pluie, temperature, visible, dir, uv)

    elif console: #sert à rien si inp read = 8
        print()
        print("Timeout...     len: " + str(len(rec)))

""" leguacy

no=1 #combient ième trame reçue

while True:
    serial.flushInput();serial.flushOutput()
    trame=(serial.readline().decode("utf8", errors="replace"))
    print("trame " + str(no) + " recue")
    no=no+1
    if trame[0]=="d" and trame[-3]=="f":

        stg, ind = separ(1)
        vent = float(stg)

        stg, ind = separ(ind)
        pluie = float(stg)

        stg, ind = separ(ind)
        temperature = float(stg)

        stg, ind = separ(ind)
        visible = int(stg)

        stg, ind = separ(ind)
        direc = int(stg)

        stg, ind = separ(ind)
        uv = int(stg)

        print(vent)
        print(pluie)
        print(temperature)
        print(visible)
        print(direc)
        print(uv)
        insert_valeur(vent,pluie,temperature,visible,direc,uv)
"""
