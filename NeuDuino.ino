byte Pins[] = {2,3,4};
const int NUM_PINS = sizeof(Pins) / sizeof(Pins[0]);
const int NUM_LEDS = NUM_PINS * (NUM_PINS-1);

const int NUM_PAGES = 3;
byte Pages[NUM_PAGES][NUM_LEDS];
const int PAGE_DURATION = 500;

byte LedMap[NUM_LEDS/2][2];

void clear()
{
  for( int i=0; i<NUM_PINS; i++ )
  {
    pinMode( Pins[i], INPUT );
    digitalWrite( Pins[i], LOW );
  }
}

/*
 * LedMap is all possible pairs of Pins
 *  + even numbered leds use (0,1)
 *  + odd numbeded leds use (1,0)
 *
 * For example, if only 5 pins, there are 20 leds (5 * 4),
 *  and 10 combinations of pins, each reversable:
 *    {0,1}, {0,2}, {0,3}, {0,4},
 *           {1,2}, {1,3}, {1,4},
 *                  {2,3}, {2,4},
 *                         {3,4}
*/
void setup()
{
  // build the LedMap
  for( int i=0, count=0; i<NUM_PINS-1; i++ )
  {
    for( int j=i+1; j<NUM_PINS; j++, count++ )
    {
      LedMap[count][0] = i;
      LedMap[count][1] = j;
    }
  }

  // set the initial states
  for( int page=0; page<NUM_PAGES; page++ )
  {
    for( int led=0; led<NUM_LEDS; led++ )
    { Pages[page][led] = 0; }
  }
  clear();

  // turn off onboard led
  pinMode( 13, OUTPUT );
  digitalWrite( 13, LOW );

  // test pattern
  Pages[0][0] = 1;
  Pages[0][1] = 1;
  Pages[1][2] = 1;
  Pages[1][3] = 1;
  Pages[2][4] = 1;
  Pages[2][5] = 1;
}

void ledOn( int led )
{
  int LowPin, HighPin;
  static int prevLowPin = 0, prevHighPin = 0;

  // convert led number to a high and low pin number
  int indexA = LedMap[led/2][0];
  int indexB = LedMap[led/2][1];

  if( led % 2 == 0 )
  {
    HighPin = Pins[indexA];
    LowPin = Pins[indexB];
  }
  else
  {
    HighPin = Pins[indexB];
    LowPin = Pins[indexA];
  }

  // turn the previous led off
  pinMode( prevLowPin, INPUT );
  pinMode( prevHighPin, INPUT );
  digitalWrite( prevHighPin, LOW );

  // light the led
  pinMode( HighPin, OUTPUT );
  pinMode( LowPin, OUTPUT );
  digitalWrite( HighPin, HIGH );
  digitalWrite( LowPin, LOW );

  // store away current pin values
  prevLowPin = LowPin;
  prevHighPin = HighPin;
}

void drawFrame()
{
  static int CurLed = 0;
  static int CurPage = 0;
  if( ++CurLed > NUM_LEDS )
  { CurLed = 0; }
 
  // turn on two led's on same rgb for mixing here?
  if( Pages[CurPage][CurLed] == 1 )
  { ledOn( CurLed ); }

  static unsigned long prevT = 0;
  unsigned long curT = millis();
  if( curT - prevT > PAGE_DURATION )
  {
    prevT = curT;
    if( ++CurPage > NUM_PAGES-1 )
    { CurPage = 0; }
  }
}

void loop()
{
  drawFrame();
}

