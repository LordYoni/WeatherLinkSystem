#include <Arduino.h>
#include <Wire.h>
#ifndef SI115X_H
#define SI115X_H

class Si115X
{
	public:
		typedef enum {
			DEVICE_ADDRESS = 0x53
		} UnitAddress;
		typedef enum {
			RESET_CMD_CTR = 0x00,
			RESET_SW = 0x01,
			FORCE = 0x11,
			PAUSE = 0x12,
			START = 0x13
		} CommandCodes;
		typedef enum {
			PART_ID = 0x00,
			REV_ID = 0x01,
			MFR_ID = 0x02,
			INFO_0 = 0x03,
			INFO_1 = 0x04,
			HOSTIN_3 = 0x07,
			HOSTIN_2 = 0x08,
			HOSTIN_0 = 0x0A,
			COMMAND = 0x0B,
			IRQ_ENABLE = 0x0F,
			RESPONSE_0 = 0x11,
			RESPONSE_1 = 0x10,
			IRQ_STATUS = 0x12,
			HOSTOUT_0 = 0x13,
			HOSTOUT_1 = 0x14,
			HOSTOUT_2 = 0x15,
			HOSTOUT_3 = 0x16,
			HOSTOUT_4 = 0x17,
			HOSTOUT_5 = 0x18,
			HOSTOUT_6 = 0x19,
			HOSTOUT_7 = 0x1A,
			HOSTOUT_8 = 0x1B,
			HOSTOUT_9 = 0x1C,
			HOSTOUT_10 = 0x1D,
			HOSTOUT_11 = 0x1E,
			HOSTOUT_12 = 0x1F,
			HOSTOUT_13 = 0x20,
			HOSTOUT_14 = 0x21,
			HOSTOUT_15 = 0x22,
			HOSTOUT_16 = 0x23,
			HOSTOUT_17 = 0x24,
			HOSTOUT_18 = 0x25,
			HOSTOUT_19 = 0x26,
			HOSTOUT_20 = 0x27,
			HOSTOUT_21 = 0x28,
			HOSTOUT_22 = 0x29,
			HOSTOUT_23 = 0x2A,
			HOSTOUT_24 = 0x2B,
			HOSTOUT_25 = 0x2C
		} RegisterAddress;
		typedef enum {
			I2C_ADDR = 0x00,
			CHAN_LIST = 0x01,
			ADCCONFIG_0 = 0x02,
			ADCSENS_0 = 0x03,
			ADCPOST_0 = 0x04,
			MEASCONFIG_0 = 0x05,
			ADCCONFIG_1 = 0x06,
			ADCPOST_1 = 0x08,
			ADCSENS_1 = 0x07,
			MEASCONFIG_1 = 0x09,
			ADCCONFIG_2 = 0x0A,
			ADCSENS_2 = 0x0B,
			ADCPOST_2 = 0x0C,
			MEASCONFIG_2 = 0x0D,
			ADCCONFIG_3 = 0x0E,
			ADCSENS_3 = 0x0F,
			ADCPOST_3 = 0x10,
			MEASCONFIG_3 = 0x11,
			ADCCONFIG_4 = 0x12,
			ADCSENS_4 = 0x13,
			ADCPOST_4 = 0x14,
			MEASCONFIG_4 = 0x15,
			ADCCONFIG_5 = 0x16,
			ADCSENS_5 = 0x17,
			ADCPOST_5 = 0x18,
			MEASCONFIG_5 = 0x19,
			MEASRATE_H = 0x1A,
			MEASRATE_L = 0x1B,
			MEASCOUNT_0 = 0x1C,
			MEASCOUNT_1 = 0x1D,
			MEASCOUNT_2 = 0x1E,
			LED1_A = 0x1F,
			LED1_B = 0x20,
			LED2_A = 0x21,
			LED2_B = 0x22,
			LED3_A = 0x23,
			LED3_B = 0x24,
			THRESHOLD0_H = 0x25,
			THRESHOLD0_L = 0x26,
			THRESHOLD1_H = 0x27,
			THRESHOLD1_L = 0x28,
			THRESHOLD2_H = 0x29,
			THRESHOLD2_L = 0x2A,
			BURST = 0x2B
		} ParameterAddress;
		void config_channel(uint8_t index, uint8_t *conf);
		void write_data(uint8_t addr, uint8_t *data, size_t len);
		int read_register(uint8_t addr, uint8_t reg, int bytesOfData);
		void param_set(uint8_t loc, uint8_t val);
		int param_query(uint8_t loc);
		void send_command(uint8_t code);
		int get_int_from_bytes(uint8_t *data, size_t len);
		bool Begin(void);
		uint16_t ReadHalfWord(void);
		float ReadHalfWord_UV(void);
		uint16_t ReadHalfWord_VISIBLE(void);
		uint8_t ReadByte(uint8_t Reg);
};
#endif
void Si115X::config_channel(uint8_t index, uint8_t *conf){
    int len = sizeof(conf);
    if(len != 4 || index > 5)
      return;
    int inc = index * len;
    param_set(Si115X::ADCCONFIG_0 + inc, conf[0]);
    param_set(Si115X::ADCSENS_0 + inc, conf[1]);
    param_set(Si115X::ADCPOST_0 + inc, conf[2]);
    param_set(Si115X::MEASCONFIG_0 + inc, conf[3]);
}
void Si115X::write_data(uint8_t addr, uint8_t *data, size_t len){
    Wire.beginTransmission(addr);
    Wire.write(data, len);
    Wire.endTransmission();
}
int Si115X::read_register(uint8_t addr, uint8_t reg, int bytesOfData){
    int val = -1;
    Si115X::write_data(addr, &reg, sizeof(reg));
    Wire.requestFrom(addr, bytesOfData);
    if(Wire.available())
      val = Wire.read();
    return val;
}
void Si115X::param_set(uint8_t loc, uint8_t val){
    uint8_t packet[2];
    int r;
    int cmmnd_ctr;
    do {
        cmmnd_ctr = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::RESPONSE_0, 1);
        packet[0] = Si115X::HOSTIN_0;
        packet[1] = val;
        Si115X::write_data(Si115X::DEVICE_ADDRESS, packet, sizeof(packet));
        packet[0] = Si115X::COMMAND;
        packet[1] = loc | (0B10 << 6);
        Si115X::write_data(Si115X::DEVICE_ADDRESS, packet, sizeof(packet));
        r = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::RESPONSE_0, 1);
    } while(r > cmmnd_ctr);
}
int Si115X::param_query(uint8_t loc){
    int result = -1;
    uint8_t packet[2];
    int r;
    int cmmnd_ctr;
    do {
        cmmnd_ctr = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::RESPONSE_0, 1);
        packet[0] = Si115X::COMMAND;
        packet[1] = loc | (0B01 << 6);
        Si115X::write_data(Si115X::DEVICE_ADDRESS, packet, sizeof(packet));
        r = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::RESPONSE_0, 1);
    } while(r > cmmnd_ctr);
    result = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::RESPONSE_1, 1);
    return result;
}
void Si115X::send_command(uint8_t code){
    uint8_t packet[2];
    int r;
    int cmmnd_ctr;
    do {
        cmmnd_ctr = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::RESPONSE_0, 1);
        packet[0] = Si115X::COMMAND;
        packet[1] = code;
        Si115X::write_data(Si115X::DEVICE_ADDRESS, packet, sizeof(packet));
        r = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::RESPONSE_0, 1);
    } while(r > cmmnd_ctr);
}
int Si115X::get_int_from_bytes(uint8_t *data, size_t len){
    int result = 0;
    int shift = 8 * len;
    for(size_t i = 0; i < len; i++){
        shift -= 8;
        result |= ((data[i] << shift) & (0xFF << shift));
    }
    return result;
}
bool Si115X::Begin(void){
    Wire.begin();
    if (ReadByte(0x00) != 0x51) {
        return false;
    }
    Si115X::send_command(Si115X::START);
    Si115X::param_set(Si115X::CHAN_LIST, 0B000010);
    Si115X::param_set(Si115X::MEASRATE_H, 0);
    Si115X::param_set(Si115X::MEASRATE_L, 1);  // 1 for a base period of 800 us
    Si115X::param_set(Si115X::MEASCOUNT_0, 5);
    Si115X::param_set(Si115X::MEASCOUNT_1, 10);
    Si115X::param_set(Si115X::MEASCOUNT_2, 10);
    Si115X::param_set(Si115X::THRESHOLD0_L, 200);
    Si115X::param_set(Si115X::THRESHOLD0_H, 0);
    Wire.beginTransmission(Si115X::DEVICE_ADDRESS);
    Wire.write(Si115X::IRQ_ENABLE);
    Wire.write(0B000010);
    Wire.endTransmission();
    uint8_t conf[4];
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega4809__)
    conf[0] = 0B00000000;
    conf[1] = 0B00000010,
    conf[2] = 0B00000001;
    conf[3] = 0B11000001;
    Si115X::config_channel(1, conf);
    conf[0] = 0B00000000;
    conf[1] = 0B00000010,
    conf[2] = 0B00000001;
    conf[3] = 0B11000001;
    Si115X::config_channel(3, conf);
#endif
#if defined(TARGET_RP2040) || defined(NRF52840_XXAA)
    conf[0] = 0B00000000;
    conf[1] = 0B00000010,
    conf[2] = 0B01111000;
    conf[3] = 0B11000000;
    Si115X::config_channel(1, conf);
    conf[0] = 0B00000000;
    conf[1] = 0B00000011,
    conf[2] = 0B01000000;
    conf[3] = 0B11000000;
    Si115X::config_channel(3, conf);
#endif
    return true;
}
#if defined(TARGET_RP2040) || defined(NRF52840_XXAA)
uint16_t Si115X::ReadHalfWord(void) {
    Si115X::send_command(Si115X::FORCE);
    uint8_t data[3];
    data[1] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_1, 1);
    data[2] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_2, 1);
    return data[2] * 256 + data[1];
}
float Si115X::ReadHalfWord_UV(void) {
    Si115X::send_command(Si115X::FORCE);
    uint8_t data[3];
    data[1] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_1, 1);
    data[2] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_2, 1);
    return ((data[2] * 256 + data[1])/3)*0.0012;
}
uint16_t Si115X::ReadHalfWord_VISIBLE(void) {
    Si115X::send_command(Si115X::FORCE);
    uint8_t data[3];
    data[1] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_1, 1);
    data[2] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_2, 1);
    return (data[2] * 256 + data[1])/3;
}
#endif
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) || defined(__SAMD51__) || defined(__AVR_ATmega4809__)
uint16_t Si115X::ReadHalfWord(void) {
    Si115X::send_command(Si115X::FORCE);
    uint8_t data[3];
    data[0] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_0, 1);
    data[1] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_1, 1);
    return data[0] * 256 + data[1];
}
float Si115X::ReadHalfWord_UV(void) {
    Si115X::send_command(Si115X::FORCE);
    uint8_t data[3];
    data[0] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_0, 1);
    data[1] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_1, 1);
    return ((data[0] * 256 + data[1])/3)*0.0012;
}
uint16_t Si115X::ReadHalfWord_VISIBLE(void) {
    Si115X::send_command(Si115X::FORCE);
    uint8_t data[3];
    data[0] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_0, 1);
    data[1] = Si115X::read_register(Si115X::DEVICE_ADDRESS, Si115X::HOSTOUT_1, 1);
    return (data[0] * 256 + data[1])/3;
}
#endif
uint8_t Si115X::ReadByte(uint8_t Reg) {
    Wire.beginTransmission(Si115X::DEVICE_ADDRESS);
    Wire.write(Reg);
    Wire.endTransmission();
    Wire.requestFrom(Si115X::DEVICE_ADDRESS, 1);
    return Wire.read();
}


const byte broche_pluviometre         = 3;
const byte broche_anemometre          = 2;
const byte broche_girouette           = A0;
const byte broche_capteur_temperature = A1;


const byte delai_anti_rebond_anemometre     = 10;
const byte delai_anti_rebond_pluviometre    = 50;
const byte rafraichissement_par_secondes    = 10;
const float longueur_tige_anemometre        = 7;
const byte temps_mode_etalonnage            = 2;
const byte temps_abandon_pluviometre        = 1;
const unsigned int temps_envoi_trame        = 5000;


const byte delai_rafraichissement           = rafraichissement_par_secondes * 10;
const unsigned int temps_abandon_pluviometre_ms = temps_abandon_pluviometre * 60000;
const float pre_calcul_vitesse_vent         = (longueur_tige_anemometre/100) * 2 * M_PI * 3.6;


const word tableau_valeurs_girouette[16][2] = {{760,20},
                                               {390,15},
                                               {450,15},
                                               {85,5},
                                               {95,5},
                                               {75,15},
                                               {175,10},
                                               {120,15},
                                               {275,15},
                                               {235,20},
                                               {620,15},
                                               {590,15},
                                               {920,15},
                                               {820,15},
                                               {875,15},
                                               {700,15}};



const String tableau_direction_vent[] = {
        "nord",  "nord nord est",    "nord est",   "est nord est",
        "est",   "est sud est",      "Sud est",    "sud sud est",
        "sud",   "sud sud ouest",    "sud ouest",  "ouest sud ouest",
        "ouest", "ouest nord ouest", "nord ouest", "nord nord ouest"};


const byte ordre_encription[] = {6, 12, 2, 9, 5, 1, 14, 10, 3, 8, 15, 0, 11, 4, 13, 7};
const byte xor_encription[] = {0x43, 0xa1, 0x6c, 0x53, 0x46, 0xa3, 0x8c, 0x25};


Si115X si1151;


unsigned long dernier_temps_envoi = 1000;


unsigned long temps_rafraichissement = 0;
boolean doit_rafraichir = 0;


byte valeur_ultraviolet;
word visible;


float vitesse_vent;
unsigned long tableau_temps_anemometre[2] = {0,0};
boolean indice_tableau_anemometre = 0;


byte indice_tableau_direction_vent;
word valeur_lu_girouette;
boolean pas_trouve;


float valeur_pluie;
unsigned long tableau_temps_pluviometre[2] = {0,0};
boolean indice_tableau_pluviometre = 0;


float valeur_thermometre;
float temperature;


volatile unsigned long dernier_temps_declanchement_anemometre  = 0;
volatile boolean anemometre_declanche = 0;
volatile unsigned long dernier_temps_declanchement_pluviometre = 0;
volatile boolean pluviometre_declanche = 0;


byte vent_ent, vent_dec, temp_ent, temp_dec, plui_ent, plui_dec, checksum;
boolean signe;
byte octet_encription[8];
byte quartet_encription[16];


void interrupt_anemometre() {
    dernier_temps_declanchement_anemometre = millis();
    anemometre_declanche = 1;
}


void interrupt_pluviometre() {
    dernier_temps_declanchement_pluviometre = millis();
    pluviometre_declanche= 1 ;
}


void cherche_indice_tableau_vent() {
    pas_trouve =1;
    for (byte a = 0; a != 16; a++) {
        if ((valeur_lu_girouette >= tableau_valeurs_girouette[a][0] - tableau_valeurs_girouette[a][1]) && (valeur_lu_girouette < tableau_valeurs_girouette[a][0] + tableau_valeurs_girouette[a][1])) {
            indice_tableau_direction_vent = a;
            pas_trouve = 0;
            break;
        }
    }
}


void setup() {

    pinMode(broche_anemometre,INPUT_PULLUP);
    pinMode(broche_pluviometre,INPUT_PULLUP);
    pinMode(broche_girouette, 0);
    pinMode(broche_capteur_temperature, 0);
    attachInterrupt(digitalPinToInterrupt(broche_anemometre), interrupt_anemometre, FALLING);
    attachInterrupt(digitalPinToInterrupt(broche_pluviometre), interrupt_pluviometre, FALLING);
    Wire.begin();
    Serial.begin(9600);
    if(!si1151.Begin()) {
        Serial.println("Capteur lumiere");
        Serial.println("pas pret");
        while (!si1151.Begin()) {}
    }
    valeur_lu_girouette = analogRead(broche_girouette);
    cherche_indice_tableau_vent();
    if(pas_trouve){
        Serial.println("Verif val. gir.");
        Serial.println("val. lue inconnue");
        delay(3000);
    }
}


void loop() {
    valeur_ultraviolet = si1151.ReadHalfWord_UV();
    visible = si1151.ReadHalfWord();
    valeur_lu_girouette = analogRead(broche_girouette);
    valeur_thermometre = analogRead(broche_capteur_temperature);
    valeur_thermometre = (valeur_thermometre * 5.0 / 1024.0 - 0.5) * 100.0;
    if (dernier_temps_declanchement_anemometre + delai_anti_rebond_anemometre <= millis() && anemometre_declanche) {
        tableau_temps_anemometre[indice_tableau_anemometre] = dernier_temps_declanchement_anemometre;
        indice_tableau_anemometre = !indice_tableau_anemometre;
        anemometre_declanche = 0;
    }
    if (tableau_temps_anemometre[!indice_tableau_anemometre] - tableau_temps_anemometre[indice_tableau_anemometre] < 3000 && tableau_temps_anemometre[1]) {
        vitesse_vent = pre_calcul_vitesse_vent * (1.0 / ( float(tableau_temps_anemometre[!indice_tableau_anemometre] - tableau_temps_anemometre[indice_tableau_anemometre]) * 0.002 ) );
    }
    else {
        vitesse_vent = 0;
    }
    if (dernier_temps_declanchement_pluviometre + delai_anti_rebond_pluviometre <= millis() && pluviometre_declanche){
        tableau_temps_pluviometre[indice_tableau_pluviometre] = dernier_temps_declanchement_pluviometre;
        indice_tableau_pluviometre = !indice_tableau_pluviometre;
        pluviometre_declanche = 0;
    }
    if ((tableau_temps_pluviometre[!indice_tableau_pluviometre] + temps_abandon_pluviometre_ms) > millis() && tableau_temps_pluviometre[0,1]) {
        valeur_pluie = (1.0 / float(tableau_temps_pluviometre[!indice_tableau_pluviometre] - tableau_temps_pluviometre[indice_tableau_pluviometre]))*3600.0 * 0.2794;
    }
    else {
        valeur_pluie = 0;
    }
    if(dernier_temps_envoi <= millis()){
        dernier_temps_envoi = millis() + temps_envoi_trame;
        vent_ent = byte(vitesse_vent);
        vent_dec = byte(int(vitesse_vent*100)%100)&127;
        temp_ent = byte(abs(valeur_thermometre))&63;
        signe = abs(valeur_thermometre)!=valeur_thermometre;
        temp_dec = byte(int(abs(valeur_thermometre)*10)%10);
        plui_ent = byte(valeur_pluie);
        plui_dec = byte(int(valeur_pluie*10)%10);
        checksum = vent_ent + vent_dec + indice_tableau_direction_vent + valeur_ultraviolet + +visible +temp_ent + signe + temp_dec + plui_ent + plui_dec;
        octet_encription[0] = (vent_ent<<2) + (vent_dec>>5);
        octet_encription[1] = (vent_dec<<3) + (indice_tableau_direction_vent>>1);
        octet_encription[2] = (indice_tableau_direction_vent<<7) + (valeur_ultraviolet<<4) + ((visible&0x3c00)>>10);
        octet_encription[3] = (visible&0x3fc)>>2;
        octet_encription[4] = ((visible)<<6) + temp_ent;
        octet_encription[5] = (signe<<7) + (temp_dec<<3) + (plui_ent>>1);
        octet_encription[6] = (plui_ent<<7) + (plui_dec<<3) + (checksum>>5);
        octet_encription[7] = checksum<<3;
        for(byte a=0;a<8;a++){
            quartet_encription[ordre_encription[a*2]] = octet_encription[a]>>4;
            quartet_encription[ordre_encription[(a*2)+1]] = octet_encription[a]&15;
        }
        for(byte a=0;a<8;a++){
            octet_encription[a] = ((quartet_encription[a*2]<<4)+quartet_encription[(a*2)+1]) ^ xor_encription[a];
        }
        for(byte a=0;a<8;a++){
            Serial.write(octet_encription[a]);
        }
    }

}
