#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define Q 7
#define G 8
#define H 9
#define I 10
#define J 11

#define NUM_PINS 10
int PINS[NUM_PINS] = { A, B, C, D, E, Q, G, H, I, J };

#define NUM_LEDS (NUM_PINS * (NUM_PINS-1))
#define NUM_PAGES 3
#if 1
int Page[NUM_PAGES][NUM_LEDS];
#else
byte Page[NUM_PAGES][NUM_PINS/2][NUM_PINS/2];
// since only 1 of rgb can be on, to increase brightness, reduce Frame loop
// base it on 25 instead of 75
// each Page[Page][x][y] is of OFF, RED, GREEN, or BLUE
#endif


byte LedMap[NUM_LEDS][2] = {
    { I, A }, // 0 (HIGH Pin, LOW Pin)
    { H, A }, // 1
    { G, A }, // 2

    { A, B }, // 3
    { I, B }, // 4
    { H, B }, // 5

    { B, C }, // 6
    { A, C }, // 7
    { I, C }, // 8

    { C, D }, // 9
    { B, D }, // 10
    { A, D }, // 11

    { D, E }, // 12
    { C, E }, // 13
    { B, E }, // 14

    { E, Q }, // 15
    { D, Q }, // 16
    { C, Q }, // 17

    { Q, G }, // 18
    { E, G }, // 19
    { D, G }, // 20

    { G, H }, // 21
    { Q, H }, // 22
    { E, H }, // 23

    { H, I }, // 24
    { G, I }, // 25
    { Q, I }  // 26
  };


void clear()
{
  for( int i=0; i<NUM_PINS; i++ )
  { pinMode( PINS[i], INPUT ); }
}



void setup()
{
  //Serial.begin(9600);
  for( int i=0; i<NUM_PAGES; i++ )
    for( int j=0; j<NUM_LEDS; j++ )
      Page[i][j] = 0;
  clear();
  
  Page[0][0] = 1;
  Page[0][3] = 1;
  Page[0][6] = 1;
  Page[0][9] = 1;
  Page[0][12] = 1;
  Page[0][15] = 1;
  Page[0][18] = 1;
  Page[0][21] = 1;
  Page[0][24] = 1;

  Page[1][1] = 1;
  Page[1][4] = 1;
  Page[1][7] = 1;
  Page[1][10] = 1;
  Page[1][13] = 1;
  Page[1][16] = 1;
  Page[1][19] = 1;
  Page[1][22] = 1;
  Page[1][25] = 1;

  Page[2][2] = 1;
  Page[2][5] = 1;
  Page[2][8] = 1;
  Page[2][11] = 1;
  Page[2][14] = 1;
  Page[2][17] = 1;
  Page[2][20] = 1;
  Page[2][23] = 1;
  Page[2][26] = 1;
}

int CurPage = 0;
int CurFrame = 0;

int PrevState = 0;
int PrevHighPin = 0;
int PrevLowPin = 0;

void drawFrame()
{
  pinMode( PrevHighPin, INPUT );
  pinMode( PrevLowPin, INPUT );

for( int i=0; i<1; i++ )
{
  // turn on two led's on same rgb for mixing here?
  if( Page[CurPage][CurFrame+i] == 1 )
  {
    byte HighPin = LedMap[CurFrame][0];
    byte LowPin = LedMap[CurFrame][1];
    PrevHighPin = HighPin;
    PrevLowPin = LowPin;

    pinMode( HighPin, OUTPUT );
    pinMode( LowPin, OUTPUT );
    digitalWrite( HighPin, HIGH );
    digitalWrite( LowPin, LOW );
  }
}
  

}

unsigned long prevT = 0;
long pageDuration = 500;
void loop()
{
 
  drawFrame();
  if( ++CurFrame > NUM_LEDS-1 )
  { CurFrame = 0; }
  
  unsigned long curT = millis();
  if( curT - prevT > pageDuration )
  {
    prevT = curT;
    if( ++CurPage > NUM_PAGES-1 )
    { CurPage = 0; }
  }
}

