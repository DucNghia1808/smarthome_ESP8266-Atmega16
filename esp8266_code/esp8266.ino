#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "webserver.h"
ESP8266WebServer webServer(1808);

char *ssid = "Nhan";
char *pass = "nhungoc1";
String ChuoiJSON="";
#define NUT1 D2
#define NUT2 D3
#define RELAY1 D0
#define RELAY2 D1
#define NUT3 D5
#define NUT4 D6
#define RELAY3 D7
#define RELAY4 D8

IPAddress local_ip(192,168,1,120);// dia chi config wifi 192.168.1.120

IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress primaryDNS(8,8,8,8);// dia chi google
IPAddress secondaryDNS(8,8,4,4);

int nhietdo=0,doam=0;
int TTTB1=0,TTTB2=0,TTTB3=0,TTTB4=0,TTTB5=0,TTTB6=0,TTTB7=0,TTTB8=0;  // khai bao 8 thiet bi
int TTTB1last=0,TTTB2last=0,TTTB3last=0,TTTB4last=0,TTTB5last=0,TTTB6last=0,TTTB7last=0,TTTB8last=0;  // khai bao 8 thiet bi
long last=0;
int kiemtra=0;

void connectWiFi();
void datajson(String ss1,String ss2,String ss3,String ss4,String ss5,String ss6);
void mainpage();
void send_update();
void chuongtrinhcambien();
void duytri();
void xulyONOFF(String button);
void web_button();
void button();

void setup() {
   Serial.begin(9600);

   pinMode(RELAY1,OUTPUT); // khởi tạo các chân IO các kiểu
   pinMode(RELAY2,OUTPUT);
   pinMode(RELAY3,OUTPUT); 
   pinMode(RELAY4,OUTPUT);
   pinMode(NUT1,INPUT_PULLUP);
   pinMode(NUT2,INPUT_PULLUP);
   pinMode(NUT3,INPUT_PULLUP);
   pinMode(NUT4,INPUT_PULLUP);
   digitalWrite(RELAY1,LOW);// giá trị mặc định ban dầu
   digitalWrite(RELAY2,LOW);
   digitalWrite(RELAY3,LOW);
   digitalWrite(RELAY4,LOW);
   connectWiFi();
   webServer.on("/",mainpage);// gọi hàm mainpage khi nhận được truy vấn GET cho URL=" /"
   webServer.on("/Update",send_update);
   webServer.on("/Button",web_button);// bật đường dẫn điều khiển từ web về esp
   webServer.begin();// mo server ra
   last=millis();
}

void loop() {
    webServer.handleClient();// lắng nghe các truy vấn từ người dùng //duy trì server
    if(Serial.available()){
      read_uart(); // đọc uart từ atmega16
    }
}

void connectWiFi(){
  WiFi.disconnect();delay(1000);
  if(!WiFi.config(local_ip,gateway,subnet,primaryDNS,secondaryDNS)){
         Serial.println("ERROR config");
  }
  delay(1000);
  WiFi.begin(ssid,pass);
  Serial.print("Connecting");
  while(WiFi.status()!=WL_CONNECTED){
    delay(800);
    Serial.print("...");
  }
  Serial.println(WiFi.localIP());
}
void datajson(String ss1,String ss2,String ss3,String ss4,String ss5,String ss6,String ss7,String ss8,String ss9,String ss10){
    ChuoiJSON="{\"ND\":\""+String(ss1)+"\","+
              "\"DA\":\""+String(ss2)+"\","+
              "\"TB1\":\""+String(ss3)+"\","+
              "\"TB2\":\""+String(ss4)+"\","+
              "\"TB3\":\""+String(ss5)+"\","+
              "\"TB4\":\""+String(ss6)+"\","+
              "\"TB5\":\""+String(ss7)+"\","+ 
              "\"TB6\":\""+String(ss8)+"\","+
              "\"TB7\":\""+String(ss9)+"\","+
              "\"TB8\":\""+String(ss10)+"\"}";              
}
void mainpage(){
  String s = FPSTR(MainPage);//  hàm chứa file HTML
  webServer.send(200,"text/html",s);
}
void send_update(){ // send  dữ liệu JSON
  datajson(String(nhietdo),String(doam),String(TTTB1),String(TTTB2),String(TTTB3),String(TTTB4),String(TTTB5),String(TTTB6),String(TTTB7),String(TTTB8));
  webServer.send(200,"text/html",String(ChuoiJSON));
}
void chuongtrinhcambien(){

}
void duytri(){ // có chức năng duy trì webserver khi nhấn giữ nút
    webServer.handleClient();// lắng nghe các truy vấn từ người dùng// duy trì server
    if(millis()-last>=1000){
      chuongtrinhcambien();
      last=millis();
    }
}

void xulyONOFF(String button){
  if(button.indexOf("A0B")>=0){           // tu server gui ve 1 s 1 lan
    TTTB1=0;
  }
  else if(button.indexOf("A1B")>=0){
    TTTB1=1;
  }
  if(TTTB1!=TTTB1last){ // kiem tra neu khac trang thai cu
    Serial.print('A');
    TTTB1last=TTTB1;
  }
  if(button.indexOf("C0D")>=0){
    TTTB2=0;
  }
  else if(button.indexOf("C1D")>=0){
    TTTB2=1;
  }
  if(TTTB2!=TTTB2last){
    Serial.print('B');
    TTTB2last=TTTB2;
  }
  if(button.indexOf("E0F")>=0){
    TTTB3=0;
  }
  else if(button.indexOf("E1F")>=0){
    TTTB3=1;
  }
  if(TTTB3!=TTTB3last){
    Serial.print('C');
    TTTB3last=TTTB3;
  }
  if(button.indexOf("G0H")>=0){
    TTTB4=0;
  }
  else if(button.indexOf("G1H")>=0){
    TTTB4=1;
  }
  if(TTTB4!=TTTB4last){
    Serial.print('D');
    TTTB4last=TTTB4;
  }
  //////////// 5
  if(button.indexOf("I0J")>=0){// thiet bị 5
    TTTB5=0;
  }
  else if(button.indexOf("I1J")>=0){
    TTTB5=1;
  }
  if(TTTB5!=TTTB5last){
    Serial.print('E');
    TTTB5last=TTTB5;
  }
   if(button.indexOf("K0L")>=0){
    TTTB6=0;
  }
  else if(button.indexOf("K1L")>=0){
    TTTB6=1;
  }
  if(TTTB6!=TTTB6last){
    Serial.print('F');
    TTTB6last=TTTB6;
  }
  if(button.indexOf("M0N")>=0){ /// thiet bi 7
    TTTB7=0;
  }
  else if(button.indexOf("M1N")>=0){
    TTTB7=1;
  }
  if(TTTB7!=TTTB7last){
    Serial.print('G');
    TTTB7last=TTTB7;
  }
  if(button.indexOf("O0P")>=0){ /// thiet bi 8
    TTTB8=0;
  }
  else if(button.indexOf("O1P")>=0){
    TTTB8=1;
  }
  if(TTTB8!=TTTB8last){
    Serial.print('H');
    TTTB8last=TTTB8;
  }
}
void web_button(){
  //Serial.println(webServer.arg("Button"));
  String button="";
  button=webServer.arg("Button");
  xulyONOFF(String(button)); 
  mainpage();
}
void read_uart(){ // doc uart tu atmega 16
  char x=(char)Serial.read();
  if(x=='A'){
    if(TTTB1==0){
       TTTB1=1;
    }
    else{
       TTTB1=0;
    }
    TTTB1last=TTTB1;
  }
  else if(x=='B'){
    if(TTTB2==0){
       TTTB2=1;
    }
    else{
       TTTB2=0;
    }
    TTTB2last=TTTB2;
  }
  else if(x=='C'){
    if(TTTB3==0){
       TTTB3=1;
    }
    else{
       TTTB3=0;
    }
    TTTB3last=TTTB3;
  }
  else if(x=='D'){
    if(TTTB4==0){
       TTTB4=1;
    }
    else{
       TTTB4=0;
    }
    TTTB4last=TTTB4;
  }
  else if(x=='E'){ //// nut thu 5
    if(TTTB5==0){
       TTTB5=1;
    }
    else{
       TTTB5=0;
    }
    TTTB5last=TTTB5;
  }
  else if(x=='F'){ //// nut thu 6
    if(TTTB6==0){
       TTTB6=1;
    }
    else{
       TTTB6=0;
    }
    TTTB6last=TTTB6;
  }
  else if(x=='G'){ //// nut thu 7
    if(TTTB7==0){
       TTTB7=1;
    }
    else{
       TTTB7=0;
    }
    TTTB7last=TTTB7;
  }
  else if(x=='H'){ //// nut thu 8
    if(TTTB8==0){
       TTTB8=1;
    }
    else{
       TTTB8=0;
    }
    TTTB8last=TTTB8;
  } 
  else if(x=='X'){
    // ham doc uart gia tri do am va nhiet do uart
    delay(10);
    doam=(int)Serial.read()*10+(int)Serial.read();// tinh uart gia tri do am
    delay(10);
    nhietdo=(int)Serial.read()*10+(int)Serial.read();// tinh uart gia tri nhiet do
  }
}
void button(){ // ham kiem tra phim nhan
    if(digitalRead(NUT1)==0){/// nut relay 1
      delay(100);
      if(digitalRead(NUT1)==0){
        while(digitalRead(NUT1)==0){duytri();}
        if(TTTB1==0){
          digitalWrite(RELAY1,HIGH);
          TTTB1=1;
        }
        else{
          digitalWrite(RELAY1,LOW);
          TTTB1=0;
         }
      }
    }
    if(digitalRead(NUT2)==0){/// nut relay 2
      delay(100);
      if(digitalRead(NUT2)==0){
        while(digitalRead(NUT2)==0){duytri();}
        if(TTTB2==0){
          digitalWrite(RELAY2,HIGH);
          TTTB2=1;
        }
        else{
          digitalWrite(RELAY2,LOW);
          TTTB2=0;
         }
      }
    }
    if(digitalRead(NUT3)==0){/// nut relay 3
      delay(100);
      if(digitalRead(NUT3)==0){
        while(digitalRead(NUT3)==0){duytri();}
        if(TTTB3==0){
          digitalWrite(RELAY3,HIGH);
          TTTB3=1;
        }
        else{
          digitalWrite(RELAY3,LOW);
          TTTB3=0;
         }
      }
    }
    if(digitalRead(NUT4)==0){/// nut relay 4
      delay(100);
      if(digitalRead(NUT4)==0){
        while(digitalRead(NUT4)==0){duytri();}
        if(TTTB4==0){
          digitalWrite(RELAY4,HIGH);
          TTTB4=1;
        }
        else{
          digitalWrite(RELAY4,LOW);
          TTTB4=0;
         }
      }
    }
}
