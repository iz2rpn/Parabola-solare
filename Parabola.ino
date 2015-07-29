/*Sketch to ddrive Brushed DC-Motor in two directions*/

#define  IS_1  0
#define  IS_2  1
#define  IN_1  3
#define  IN_2  11
#define  INH_1 12
#define  INH_2 13
#define  change 8

#define TCONST 100      //Delay Time between Steps

int Motor_DC     = 0;    // actual DC
int Motor_DC_MAX = 60;   // 50% Dutycycle

int i = 0;

// PhotoResistor pin connections

int ptrlt = 0; //top left
int ptrrt = 1; //top rigt
int ptrld = 2; //down left
int ptrrd = 3; //down rigt


void setup() {

  // put your setup code here, to run once:
  pinMode(IN_1,OUTPUT);
  pinMode(IN_2,OUTPUT);
  pinMode(INH_1,OUTPUT);
  pinMode(INH_2,OUTPUT);
  pinMode(change,OUTPUT);
  
  reset_ports();
  
  digitalWrite(INH_1,1);
  digitalWrite(INH_2,1);
}

void fade_Motor(int port)
{
   for(i = 0; i< Motor_DC_MAX; i++)
  {
  Motor_DC = map( i , 0 , 100 , 0 , 255 );
  analogWrite( port , Motor_DC );

  delay(TCONST);
  }
  
  //Slow down Motor
  for(i = Motor_DC_MAX; i>= 0; i--)
  {
  Motor_DC = map( i , 0 , 100 , 0 , 255 );
  analogWrite( port , Motor_DC );

  delay(TCONST);
  }
}

//Alle IOs zurücksetzen
void reset_ports()
{
  digitalWrite(IN_1,0);
  digitalWrite(IN_2,0);
}

void loop() {
  
  int lt = analogRead(ptrlt); // top left
  int rt = analogRead(ptrrt); // top right
  int ld = analogRead(ptrld); // down left
  int rd = analogRead(ptrrd); // down rigt
 
if (lt < ld)
{
  reset_ports();
  delay(1000);
  digitalWrite(change,HIGH);
  delay(1000);
  fade_Motor(IN_2);
}
else if (lt > ld)
{
  reset_ports();
  delay(1000);
  fade_Motor(IN_1);
}
else
{
    reset_ports();
  delay(1000);
  digitalWrite(change,LOW);
  delay(1000);
}


 
if (rt < rd)
{
  reset_ports();
  delay(1000);
  digitalWrite(change,LOW);
  delay(1000);
  fade_Motor(IN_2);
}
else if (rt > rd)
{
  reset_ports();
  delay(1000);
  fade_Motor(IN_1);
}
else
{
    reset_ports();
  delay(1000);
}  
  
}
