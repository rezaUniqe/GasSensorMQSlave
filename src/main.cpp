#include <MQUnifiedsensor.h>
#include <Wire.h>

//Definitions
#define pin A0 //Analog input 0 of your arduino
#define type 2 //MQ2

MQUnifiedsensor MQ2(pin, type);


float H2, LPG, CO, Alcohol, Propane, Benzene;

void onRequestEvent();
int turnToInt(float t);
void setIntoBuffer(byte buff[],int val);
void sendData(byte buff[2]);

void setup() {
    Serial.begin(9600);
    Wire.begin(8);
    Wire.onRequest(onRequestEvent);
    MQ2.inicializar();

}

void loop() {
    MQ2.update();

    H2 =  MQ2.readSensor("H2"); // Return H2 concentration
    LPG =  MQ2.readSensor("LPG"); // Return LPG concentration
    CO =  MQ2.readSensor("CO"); // Return CO concentration
    Alcohol =  MQ2.readSensor("Alcohol"); // Return Alcohol concentration
    Propane =  MQ2.readSensor("Propane"); // Return Propane concentration

}

void onRequestEvent(){
    byte buff[2];
    int  val;
    //H2
    val=turnToInt(H2);
    setIntoBuffer(buff,val);
    sendData(buff);
    //LPG
    val=turnToInt(LPG);
    setIntoBuffer(buff,val);
    sendData(buff);
    //CO
    val=turnToInt(CO);
    setIntoBuffer(buff,val);
    sendData(buff);
    //Alcohol
    val=turnToInt(Alcohol);
    setIntoBuffer(buff,val);
    sendData(buff);
    //Propane
    val=turnToInt(Propane);
    setIntoBuffer(buff,val);
    sendData(buff);
}

int turnToInt(float t){
    return t*100;

}

void setIntoBuffer(byte buff[],int val){

    buff[0]=val;
    buff[1]=val>>8;

}
void sendData(byte buff[2]){
    Wire.write(buff[0]);
    Wire.write(buff[1]);
}
