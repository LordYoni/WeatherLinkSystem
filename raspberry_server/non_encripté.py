import serial
import mysql.connector as MC



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



def separ(index):
    var=""
    for i in range(index,len(trame)-3):
        if trame[i] == ",":
            break
        else:
            var = var + trame[i]
    return var,i+1

serial = serial.Serial('/dev/ttyUSB0', 9600)

no=1 #combient ième trame reçue

while True:
    serial..reset_input_buffer();serial.reset_output_buffer()
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

