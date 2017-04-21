
char in;
char cmd[4];
int i = 0;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(5, HIGH); 
  digitalWrite(4, LOW); 
  digitalWrite(8, LOW); 
  delay(2000);
  power_on();
}

void loop()
{
  if (Serial1.available()>0) {
    Serial.write(Serial1.read());
  }
  if (Serial.available()>0) {    
    in = Serial.read();    
    
    if (in == '@' & i==0) { 
      cmd[i] = in; 
      i++; 
    }
    if (i > 0 & i < 4 && in != '@' & in != '\r') { 
      cmd[i] = in; 
      i++; 
    }
    
    if (i == 3 & in == '\r') { 
      cmd[i] = '\0'; 
      if (strstr(cmd,"@OF")) power_off();
      if (strstr(cmd,"@ON")) power_on();
      if (strstr(cmd,"@WE")) weakup(); 
      if (strstr(cmd,"@SL")) sleep(); 
      i=0;
    }
    if (i > 3) i=0;

    Serial1.write(in);
  }
}


void power_off() {

   digitalWrite(4, HIGH); // Power OFF
   Serial.println("A7-POWER-OFF");
   delay(3000);
   digitalWrite(4, LOW);   
}

void power_on() {
  digitalWrite(8, HIGH); 
  delay(3000);       
  digitalWrite(8, LOW); // Power ON
  delay(3000);       
  Serial.println("A7-POWER-ON");
  
}

void sleep() {

   digitalWrite(5, LOW);  // Sleep
   Serial.println("A7-GO-TO-SLEEP");
   delay(3000);
}

void weakup() {
  
   digitalWrite(5, HIGH);   // Weak-Up
   delay(1000);
   Serial.println("A7-WAKE-UP"); 
   
}
