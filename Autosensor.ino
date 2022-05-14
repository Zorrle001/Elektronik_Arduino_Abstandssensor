int trigger = 7;
int echo = 6;
int piezo = 5;
long dauer = 0;
long entfernung = 0;
long puls = 0;

void setup() {  

  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(piezo, OUTPUT);
  
}

void loop() {
	
  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer/2) * 0.03432;
  
  if(entfernung == 1203) {
	  
    Serial.println("Abgebrochen!");
    digitalWrite(piezo, LOW);
    return;
	
  }else {
	  
    Serial.print(entfernung);
    Serial.println(" cm");

    if(entfernung <= 23 && entfernung >= 0) {
		
      puls = (31 * entfernung - 218) / 2; 
	  
      if(puls < 0) {
        puls = 0;
      }
	  
      if(puls >= 30) {
		  
        digitalWrite(piezo, HIGH);
        delay(puls);
        digitalWrite(piezo, LOW);
        delay(puls);
        return;
		
      }else {
        digitalWrite(piezo, HIGH);
      }
	  
    }else {
      digitalWrite(piezo, LOW);
    }
  }
  
  delay(500);
}
