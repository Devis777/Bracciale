int ficdxup ;    
int ficdxdn ;    
int ficsxup ;   
int ficsxdn ;

int emerg;
int up;
int down;
int onext;

int led=2;
int motA=3;
int motB=4;
int inversA=5;
int inversB=6;

int cnt=0;
unsigned long time;
unsigned long lampeggio_time = 0;

void setup() {
  
  pinMode(ficdxup, INPUT);
  pinMode(ficdxdn, INPUT);
  pinMode(ficsxup, INPUT);
  pinMode(ficsxdn, INPUT);

  pinMode(emerg, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(onext, INPUT);
  
  pinMode(led, OUTPUT);
  
  pinMode(motA, OUTPUT);
  pinMode(motB, OUTPUT);
  pinMode(inversA, OUTPUT);
  pinMode(inversB, OUTPUT);

  digitalWrite(led, LOW);
 
  ficdxup = digitalRead(1);
  ficdxdn = digitalRead(2);
  ficsxup = digitalRead(3);
  ficsxdn = digitalRead(4);
  emerg = digitalRead(5);
  up = digitalRead(6);
  down = digitalRead(7); 
  onext = digitalRead(8);
}

void loop() {
 
  
  do{
  if (ficdxup==LOW && ficsxup==LOW || ficdxdn==LOW && ficsxdn==LOW) { //i NO uso con parallelo relè ext
    digitalWrite(motA, LOW);  //FERMO
    delay(100);
    digitalWrite(motB, LOW);
    cnt=0;
    }
 if ( up==HIGH || down==HIGH && motA==HIGH && cnt==0 ) 
{
 digitalWrite(motA, LOW); //FERMO
  delay(100);
 digitalWrite(motB, LOW);
 cnt++;
}
if (up==HIGH && cnt==1 && ficdxup==HIGH && ficsxup==HIGH)
{
   digitalWrite(inversA, HIGH);
   digitalWrite(inversB, HIGH);
   digitalWrite(led, HIGH);
   digitalWrite(motA, HIGH); // VAI SU
   delay(100);
   digitalWrite(motB, HIGH);
   
}
if (down==HIGH && cnt==1 && ficdxdn==HIGH && ficsxdn==HIGH)
{
   digitalWrite(inversA, LOW);
   digitalWrite(inversB, HIGH);
   digitalWrite(motA, HIGH); // VAI GIU
   delay(100);
   digitalWrite(motB, HIGH);
   digitalWrite(led, HIGH);
}
  if (ficdxup==LOW && ficsxup==LOW && down==HIGH)
  {
  digitalWrite(inversA, LOW);
  digitalWrite(inversB, HIGH);
  digitalWrite(motA, HIGH); // VAI GIU
  delay(100);
  digitalWrite(motB, HIGH);
  digitalWrite(led, HIGH);
  }
if (ficdxdn==LOW && ficsxdn==LOW && up==HIGH)
{
  digitalWrite(inversA, HIGH);
  digitalWrite(inversB, HIGH);
  digitalWrite(motA, HIGH); // VAI SU
  delay(100);
  digitalWrite(motB, HIGH);
  digitalWrite(led, HIGH);   
}
  if (ficdxdn==LOW && ficsxdn==LOW && onext==HIGH)
  { 
   digitalWrite(inversA, HIGH);
   digitalWrite(inversB, HIGH);
   digitalWrite(motA, HIGH); // VAI SU
   delay(100);
   digitalWrite(motB, HIGH);
   digitalWrite(led, HIGH);
}
 }
  while (emerg==LOW);
  digitalWrite(motA,LOW);
  delay(100);
  digitalWrite(motB, LOW);
   
   time=millis();
   if(time>lampeggio_time+1000)
  {
    digitalWrite(led, HIGH);
  }
   if(time>lampeggio_time+2000)
  {
    digitalWrite(led, LOW);
    lampeggio_time=millis();
  }
}


