// REGISTRIERUNG ALLER PINS UND BENÖTIGTEN VARIABLEN
int trigger = 7;
int echo = 6;
int piezo = 5;
long dauer = 0;
long entfernung = 0;
long puls = 0;

void setup() {  
  
  Serial.begin(9600); //VERBINDUNGSAUFBAU MIT AUSGABE AN PC
	
  //INITIALISIERUNG DER INPUT & OUTPUT PINS
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(piezo, OUTPUT);
  
}

void loop() {

  //BERECHNUNG DES ABSTANDES ZU NÄCHSTEM OBJEKT
  //für weitere Details siehe Readme.md
  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer/2) * 0.03432;
  
  //ÜBERPRÜFUNG OB KEIN OBJEKT GEFUNDEN WURDE
  if(entfernung == 1203) {
	  
    Serial.println("Abgebrochen!"); 	//AUSGABE WIRD AN PC GESENDET
    digitalWrite(piezo, LOW);		//LAUTSPRECHER WIRD DEAKTIVIERT, FALLS ER NOCH AKTIVIERT IST
    return;
	
  }else {
	 
    //ENTFERNUNG ZU NÄCHSTEM OBJEKT WIRD AN PC GESENDET
    Serial.print(entfernung);		
    Serial.println(" cm");

    //ÜBERPRÜFEN OB OBJEKT IN WARNBEREICH LIEGT
    if(entfernung <= 23 && entfernung >= 0) {
      //WENN OBJEKT IN BEREICH LIEGT WIRD DER TEIL AUSGEFÜHRT:
	    
      //BERECHNEN DES ZEITABSTANDES IN PIEPSGERÄUSCH
      //für weitere Details siehe Readme.md
      puls = (31 * entfernung - 218) / 2; 
	  
      //ENTFERNEN VON NEGATIVEN WERTEN
      if(puls < 0) {
        puls = 0;
      }
	
      //ÜBERPRÜFEN OB ZEITABSTAND GRÖßERGLEICH 30 IST
      if(puls >= 30) {
		  
	//WENN ZEITABSTAND ÜBER 30MS IST WIRD PIEPS SIGNAL AUSGEGEBEN
        digitalWrite(piezo, HIGH);
        delay(puls);
        digitalWrite(piezo, LOW);
        delay(puls);
        return;
		
      }else {
	//ANSONSTEN GIBT LAUTSPRECHER DAUERTON AUS
        digitalWrite(piezo, HIGH);
      }
	  
    }else {
      //ANSONSTEN WIRD DER LAUTSPRECHER DEAKTIVIERT, FALLS ER NOCH AKTIVIERT IST
      digitalWrite(piezo, LOW);
    }
  }
  
  //NUN WIRD 500MS GEWARTET BIS ALLES VON VORNE BEGINNT
  delay(500);
}
