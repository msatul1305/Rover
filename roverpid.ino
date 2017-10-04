int l1=2,l2=3,r1=4,r2=5,a[8],i=0;
int trigPin = 7,echoPin = 6,distance;
long duration;
//int error=0,last_proportional=0,integral=0;
int momax=100;
int rspeed,lspeed,lbspeed=150,rbspeed=150;
float kp,ki,kd;
unsigned int pos;
int S0=8,S1=9,S2=10,S3=11,sensorOut=12;
int frequency = 0;
int r,g,b;
char sm;
int p=22,n=24;
void left(){
    analogWrite(l1,momax);
    analogWrite(l2,0);
    analogWrite(r1,0);
    analogWrite(r2,momax);
}
void forward(){
    analogWrite(l1,0);
    analogWrite(l2,momax);
    analogWrite(r1,0);
    analogWrite(r2,momax);
}
void backward(){
    analogWrite(l1,momax);
    analogWrite(l2,0);
    analogWrite(r1,momax);
    analogWrite(r2,0);
}
void right(){
    analogWrite(l1,0);
    analogWrite(l2,momax);
    analogWrite(r1,momax);
    analogWrite(r2,0);
}
void stops()
{
  analogWrite(l1,0);
  analogWrite(l2,0);
  analogWrite(r1,0);
  analogWrite(r2,0);
}
void ledblink(){
  digitalWrite(p,1);
  digitalWrite(n,0);
  delay(100);
  digitalWrite(p,0);
  digitalWrite(n,0);
}
void setup()
{
  pinMode(p,OUTPUT);
  pinMode(n,OUTPUT);
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
  pinMode(a[0],INPUT);
  pinMode(a[1],INPUT);
  pinMode(a[2],INPUT);
  pinMode(a[3],INPUT);
  pinMode(a[4],INPUT);
  pinMode(a[5],INPUT);
  pinMode(a[6],INPUT);
  pinMode(a[7],INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  Serial.begin(115200);
}
void loop()
{
  delay(10);
  readline();
  if(a[0]==1&&a[1]==1&&a[2]==1&&(a[3]==0||a[4]==0)&&a[5]==1&&a[6]==1&&a[7]==1){
      Serial.write("f");  stops();   }
  else if(a[0]==0&&a[2]==0&&a[3]==0&&a[4]==0&&a[5]==0&&a[7]==0){
      Serial.write("T");  stops();   }
  else if(a[0]==1&&a[1]==1&&a[2]==1&&a[3]==1&&a[4]==1&&a[5]==1&&a[6]==1&&a[7]==1){
      Serial.write("p");  stops();   }
  else if((a[0]==0&&a[1]==0&&a[2]==0&&(a[3]==0||a[4]==0)&&a[5]==1&&a[6]==1&&a[7]==1)||a[0]==0){
      Serial.write("l");  stops();   }
  else if((a[0]==1&&a[1]==1&&a[2]==1&&(a[3]==0||a[4]==0)&&a[5]==0&&a[6]==0&&a[7]==0)||a[7]==0){
      Serial.write("r");  stops();   }
  else{ 
      Serial.write("w");  stops();   }
  if(Serial.available()>0){
      sm=Serial.read();
      ledblink();
      if(sm=='f'){    ledblink();
          pid();    }
      else if(sm=='l'){   ledblink(); forward();delay(500);
          left();delay(950);  pid();   }
      else if(sm=='r'){   ledblink(); forward();delay(500);
          right();delay(950); pid();   }
      else if(sm=='b'){   ledblink();
          left();delay(1800);pid();
      }
      else if(sm=='s'){   ledblink(); 
          stops();    }
  }
  
}
int readline()
{
  int j=31;
  for(int i=0;i<8;i++,j+=2)
  {
    a[i]=digitalRead(j);  
    //if(i!=7)Serial.print(a[i]);   else Serial.println(a[i]);
  }
  int v=(7000*a[0]+6000*a[1]+5000*a[2]+4000*a[3]+3000*a[4]+2000*a[5]+1000*a[6]+0*a[7])/(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]);       
  return v;
}

void pid()
{ 
  forward();
  delay(50);
  int derivative,proportional;
  int error=0,last_proportional=0,integral=0;
  while(1)
  {
    pos=readline();    
    Serial.write("n");
    
    proportional=((int)pos-3500);
    derivative=proportional-last_proportional;
    integral=integral+proportional;
    last_proportional=proportional;
    kp=0.2;
    ki=0.0001;
    kd=5.0;
    error=proportional*kp+integral*ki+derivative*kd;
    //Serial.println(error);
    const int max=155;
    if(error>max)  
      error=max;
    if(error<(-max))
      error=(-1*max);
    lspeed=lbspeed+error;
    rspeed=rbspeed-error;
    if(lspeed<0)  lspeed=0;
    if(rspeed<0)  rspeed=0;
    if(lspeed>130)  lspeed=130;
    if(rspeed>130)  rspeed=130;
    if(a[0]==1&&a[1]==1&&a[2]==1&&a[3]==1&&a[4]==1&&a[5]==1&&a[6]==1&&a[7]==1){
      rspeed=0;lspeed=0; stops();    return;
    }
    if(a[0]==0||a[7]==0){   stops(); rspeed=0;lspeed=0;
      return; }
    analogWrite(l1,0);
    analogWrite(l2,lspeed);
    analogWrite(r1,0);
    analogWrite(r2,rspeed);
    /*int k=findobj();
    if(k==1){
      backward();delay(300);
      left();delay(1800);
      pid();
      return;
    }*/
    
  }
}
int  findobj(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  if(distance<=3)
  {    stops(); Serial.write("q");  findcolor();  Serial.write("\n");return 1; }
  else return 0;
}
void findcolor(){
  for(int i=0;i<20;i++){
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 11,255,255,0);
  if(frequency<0)frequency=0;
  else if(frequency>255)frequency=255;
  r=frequency;
  delay(10);
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 11,255,255,0);
  if(frequency<0)frequency=0;
  else if(frequency>255)frequency=255;
  g=frequency;
  delay(10);
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 11,255,255,0);
  if(frequency<0)frequency=0;
  else if(frequency>255)frequency=255;
  b=frequency;
  delay(10); 
  Serial.write(r);
  Serial.write(g);
  Serial.write(b);
  }
}


