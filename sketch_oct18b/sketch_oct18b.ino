/*
  The circuit:
  Rotary Encoder:
  ROTA to digital pin 2
  ROTB to digital pin 3

  LCD Display:
  LCD D4 pin to digital pin 4
  LCD D5 pin to digital pin 5
  LCD D6 pin to digital pin 6
  LCD D7 pin to digital pin 7
  LCD RS pin to digital pin 8
  LCD Enable pin to digital pin 9
  LCD R/W pin to ground
  10K resistor:
  ends to +5V and ground
  wiper to LCD VO pin (pin 3)

  SPI Interface:
  CS - to digital pin 10  (SS pin)
  SDI - to digital pin 11 (MOSI pin)
  SDO - to digital pin 12 (MISO pin)
  CLK - to digital pin 13 (SCK pin)

  Analog Inputs:
  A0 - to analog pin A0
  A1 - to analog pin A1
  A2 - to analog pin A2 (ptt_in_n)
  A3 - to analog pin A3 (pll_lock)

  I2C/TWI:
  I2C_SDA - to analog pin A4
  I2C_SCL - to analog pin A5
*/
//
// Frequency bands
//
// PLL_HF defines HF VCO using 74HC163 as a 8/9 prescaler
// PLL_IC215 defines a HF VCO multiplied by 9 on RX and by 8 on TX for 146MHz
// PLL_70CM defines a UHF VCO using an MB504 as a 32/33 or 64/65 prescaler
//
#define PLL_HF
//#define PLL_IC215
//#define PLL_70CM

//
// Define CONSOLE for serial I/O
//
#define CONSOLE

//
// Define TWI if you want I2C
//
#define TWI

//
// Define EEP if you want EEPROM
//
#define EEPR

// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h>

#ifdef TWI
#include <Wire.h>
#endif

#ifdef EEPR
#include <EEPROM.h>
#endif
// initialize the LiquidCrystal library
// with the numbers of the interface pins
// RS,(RW),E,D4,D5,D6,D7
// Note read-write pin not defined

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


//
// MC145159 PLL
// 14 bits for reference divider
// 10 bits for N divider
// 7 bits for A divider (prescaller)
// 1 bit for All load control bit (C)
// if C is set  to 1 then the reference counter is programmed
// R13 .. R0,N9..N0,A7..A0,C
//

//
// Number of bits in counters in the MC145159
//
#define R_BITS 14
#define N_BITS 10
#define A_BITS 7
#define C_BITS 1
//
// Number of bits in Prescaler
// Fvco = Fref * (N * P + A)
//
#ifdef PLL_HF
#define P_BITS 3
#endif

#ifdef PLL_IC215
#define P_BITS 3
#endif

#ifdef PLL_70CM
#define P_BITS 6
#endif
//
// Maximum size of count
//
#define R_MAX (1<<R_BITS)
#define N_MAX (1<<N_BITS)
#define A_MAX (1<<A_BITS)
#define P_MAX (1<<P_BITS)

#ifdef PLL_HF
//
// TX 1.8MHz - 7.5MHz
// IF 0.455MHz
// 1KHz channel spacing
//
#define FREQ_HF_BOT 1800
#define FREQ_HF_TOP 7500
#define FREQ_HF_IF   455
#define FREQ_HF_REF    1
#define FREQ_HF_XTL 8000
#define MULT_HF_TX     1
#define MULT_HF_RX     1

#define R_COUNT_TX (FREQ_HF_XTL/(FREQ_HF_REF * MULT_HF_TX))
#define R_COUNT_RX (FREQ_HF_XTL/(FREQ_HF_REF * MULT_HF_RX))

#define ENC_IF_OFF (FREQ_HF_IF /FREQ_HF_REF)
#define ENC_TX_BOT (FREQ_HF_BOT/FREQ_HF_REF)
#define ENC_TX_TOP (FREQ_HF_TOP/FREQ_HF_REF)
#define ENC_RX_BOT (ENC_TX_BOT + ENC_IF_OFF)
#define ENC_RX_TOP (ENC_TX_TOP + ENC_IF_OFF)
/*
  #define ENC_TX_BOT 1800
  #define ENC_TX_TOP 7500
  #define ENC_RX_BOT 2255
  #define ENC_RX_TOP 7955
*/
#endif

#ifdef PLL_IC215
//
// TX 144MHz - 148MHz
// IF 10.7MHz
// 25KHz channel spacing
// FREF TX 1/8
// FREF RX 1/9
//
#define FREQ_IC215_BOT 144000
#define FREQ_IC215_TOP 148000
#define FREQ_IC215_IF   10700
#define FREQ_IC215_REF     25
#define FREQ_IC215_XTL   9216
#define MULT_IC215_TX       8
#define MULT_IC215_RX       9

#define R_COUNT_TX (FREQ_IC215_XTL/(FREQ_IC215_REF * MULT_IC215_TX))
#define R_COUNT_RX (FREQ_IC215_XTL/(FREQ_IC215_REF * MULT_IC215_RX))

#define ENC_IF_OFF (FREQ_IC215_IF /FREQ_IC215_REF)
#define ENC_TX_BOT (FREQ_IC215_BOT/FREQ_IC215_REF)
#define ENC_TX_TOP (FREQ_IC215_TOP/FREQ_IC215_REF)
#define ENC_RX_BOT (ENC_TX_BOT + ENC_IF_OFF)
#define ENC_RX_TOP (ENC_TX_TOP + ENC_IF_OFF)
/*
  #define ENC_TX_BOT 5760
  #define ENC_TX_TOP 5920
  #define ENC_RX_BOT 6188
  #define ENC_RX_TOP 6348
*/
#endif

#ifdef PLL_70CM
//
// TX 430MHz - 440MHz
// IF 21.4MHz
// 25KHz channel spacing
//
#define FREQ_70CM_BOT 430000
#define FREQ_70CM_TOP 440000
#define FREQ_70CM_IF   21400
#define FREQ_70CM_REF     25
#define FREQ_70CM_XTL   8000
#define MULT_70CM_TX       1
#define MULT_70CM_RX       1

#define R_COUNT_TX (FREQ_70CM_XTL/(FREQ_70CM_REF * MULT_70CM_TX))
#define R_COUNT_RX (FREQ_70CM_XTL/(FREQ_70CM_REF * MULT_70CM_RX))

#define ENC_IF_OFF (FREQ_70CM_IF /FREQ_70CM_REF)
#define ENC_TX_BOT (FREQ_70CM_BOT/FREQ_70CM_REF)
#define ENC_TX_TOP (FREQ_70CM_TOP/FREQ_70CM_REF)
#define ENC_RX_BOT (ENC_TX_BOT + ENC_IF_OFF)
#define ENC_RX_TOP (ENC_TX_TOP + ENC_IF_OFF)
/*
  #define ENC_TX_BOT 17200
  #define ENC_TX_TOP 17600
  #define ENC_RX_BOT 18056
  #define ENC_RX_TOP 18456
*/
#endif

//
// Rotary encoder variables
//
// usually the rotary encoders three pins
// and have the ground pin in the middle
//
enum PinAssignments {
  encoderPinA = 2,    // right
  encoderPinB = 3,    // left
  pttPin      = A2,   // Analog input
  lockPin     = A3    // Analog input
};

volatile unsigned int encoderPos = ENC_TX_BOT;  // a counter for the dial
unsigned int encoderBot = ENC_TX_BOT;           // counter lower limit
unsigned int encoderTop = ENC_TX_TOP;           // counter upper limit
unsigned int lastReportedPos = 1;               // change management
static boolean rotating = false;                // debounce management

boolean A_set = false;
boolean B_set = false;


//
// Analogue input
// I'm using 2 of the analogue inputs.
// A2 is a digital input for ptt_in_in
// A3 is a digital input for pll_locked
//
#define MAX_ANALOGUE 2
int sensorPin[MAX_ANALOGUE] = {A0, A1};    // select the input pin for the potentiometer
int sensorValue[MAX_ANALOGUE] = {0, 0}; // variable to store the value coming from the sensor

// I2C Pot example code
// Used as a stub for future possible use.
// I2C can be used for an external EEPROM.
byte val = 0;

// Internal EEPROM routine variables.
// start reading from the first byte (address 0) of the EEPROM
// There are 512 bytes of EEPROM in the Arduino UNO.
int address = 0;
byte value;

//
// Serial input & output
//
int inByte = 0;         // incoming serial byte
char string[2];

//
// Union for SPI transfer
//
// Use a union of 4 bytes, 2 integers and 1 long
// An unsigned long allows the different counter values to shifted
// into the correct position, and the bytes are used for the SPI transfer
//
// assume big endian.
//

union  pll_spi_t {
  unsigned char uc[4];
  unsigned int  ui[2];
  unsigned long ul;
} pll_spi;

int pll_r_count = 0; // R count
int pll_n_count = 0; // N count
int pll_a_count = 0; // A count

int freq_khz[6] = {0, 0, 0, 0, 0, 0};

//
// The SPI Interface will be used to program a MC145159 PLL chip.
// set pin 10 as the slave select.
// The slave select output is used as the enable pin.
const int slaveSelectPin = 10;

/*
   Another Interrupt Library THAT REALLY WORKS
   (the Encoder interrupts the processor and debounces like there is no tomorrow).
   by rafbuff
   http://playground.arduino.cc/Main/RotaryEncoders#Example14

   I tried most of the above but found that they do not
   reliably count steps up and down.
   Most have trouble with debouncing.
   While I use all the tricks regarding interrupt usage
   and efficiency above, I found this one to work best
   when precision counts...

   interrupt routine for Rotary Encoders
   tested with Noble RE0124PVB 17.7FINB-24
   http://www.nobleusa.com/pdf/xre.pdf
   - available at pollin.de and a few others,
   seems pretty universal

   The average rotary encoder has three pins, seen from front: A C B
   Clockwise rotation A(on)->B(on)->A(off)->B(off)
   CounterCW rotation B(on)->A(on)->B(off)->A(off)

   and may be a push switch with another two pins, pulled low at pin 8 in this case
   raf@synapps.de 20120107
*/

// Interrupt on A changing state
void doEncoderA() {
  // debounce
  // wait a little until the bouncing is done
  if ( rotating ) delay (1);

  // Test transition, did things really change?
  if ( digitalRead(encoderPinA) != A_set ) // debounce once more
  {
    A_set = !A_set;

    // adjust counter + if A leads B
    if ( A_set && !B_set )
    {
      if ( encoderPos < encoderTop )
        encoderPos += 1;
    }
    rotating = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doEncoderB() {
  // debounce
  // wait a little until the bouncing is done
  if ( rotating ) delay (1);

  // Test transition, did things really change?
  if ( digitalRead(encoderPinB) != B_set )
  {
    B_set = !B_set;
    //  adjust counter - 1 if B leads A
    if ( B_set && !A_set )
    {
      if ( encoderPos > encoderBot )
        encoderPos -= 1;
    }
    rotating = false;
  }
}

void pllWrite(int R_count, int N_count, int A_count )
{
  pll_spi.ul = 0;
  pll_spi.ul |= (unsigned long)(R_count & (R_MAX - 1)) << (C_BITS + A_BITS + N_BITS);
  pll_spi.ul |= (unsigned long)(N_count & (N_MAX - 1)) << (C_BITS + A_BITS);
  pll_spi.ul |= (unsigned long)(A_count & (A_MAX - 1)) << (C_BITS);
  pll_spi.ul |= (unsigned long)1;  // program R count as well as N and A

  SPI.transfer(pll_spi.uc[0]);
  SPI.transfer(pll_spi.uc[1]);
  SPI.transfer(pll_spi.uc[2]);
  SPI.transfer(pll_spi.uc[3]);
  // take the SS pin high to load counters then low again
  digitalWrite(slaveSelectPin, HIGH);
  digitalWrite(slaveSelectPin, LOW);
}

void setup()
{
  // Rotary Encode initialization
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  //  digitalWrite(encoderPinA, HIGH);  // turn on pullup resistor
  //  digitalWrite(encoderPinB, HIGH);  // turn on pullup resistor
  // encoder A pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder B pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  encoderTop = ENC_TX_TOP;
  encoderBot = ENC_TX_BOT;
  encoderPos = ENC_TX_BOT;

  pinMode(pttPin, INPUT_PULLUP);         // ptt_in_n input on A2
  pinMode(lockPin, INPUT_PULLUP);        // pll_lock input on A3
  //  digitalWrite(pttPin, HIGH);     // turn on pullup resistor
  //  digitalWrite(lockPin, HIGH);    // turn on pullup resistor

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Frequency");

  // MC145159 PLL on the SPI port
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, LOW);
  // initialize SPI:
  SPI.begin();

#ifdef TWI
  // Initialize I2C / TWI
  Wire.begin(); // join i2c bus (address optional for master)
#endif

#ifdef CONSOLE
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  // wait for serial port to connect. Needed for Leonardo only
  while (!Serial);
#endif
}

void loop()
{
  int i;
  byte ptt_in_n = 0;
  byte ptt_in_old = 0;
  byte ptt_in_chg = 0;
  byte pll_lock = 0;
  byte pll_lock_old = 0;
  byte pll_lock_chg = 0;
  byte leading_zero = 0;

  ptt_in_old = ptt_in_n;
  ptt_in_n = digitalRead(pttPin);
  if ( ptt_in_n != ptt_in_old )
  {
    ptt_in_chg = 1;
  }
  pll_lock_old = pll_lock;
  pll_lock = digitalRead(lockPin);
  if ( pll_lock != pll_lock_old )
  {
    pll_lock_chg = 1;
  }

  // Rotary Encoder
  if ((lastReportedPos != encoderPos) || ptt_in_chg )
  {
#ifdef CONSOLE
    // Serial.print("Frequency = ");
    // Serial.print(encoderPos, DEC);
    // Serial.print("KHz");
    // Serial.println();
#endif
    //
    // Reference divider may depend on state of PTT
    // depending on which band we are using
    // IC215 used different referency frequencies for RX & TX
    //
    if ( ptt_in_n )
    {
      pll_r_count = R_COUNT_RX;
      pll_n_count = (encoderPos + ENC_IF_OFF) >> P_BITS;
      pll_a_count = (encoderPos + ENC_IF_OFF) & (P_MAX - 1);
    }
    else
    {
      pll_r_count = R_COUNT_TX;
      pll_n_count = encoderPos >> P_BITS;
      pll_a_count = encoderPos & (P_MAX - 1);
    }
    // SPI digital PLL
    pllWrite(pll_r_count, pll_n_count, pll_a_count);
    lastReportedPos = encoderPos;
    ptt_in_chg = 0;
  }
  //
  // LCD Frequency Display
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //
  lcd.setCursor(0, 1);
  freq_khz[5] = encoderPos;
  for (i = 5; i > 0; i--)
  {
    freq_khz[i - 1] = freq_khz[i] / 10;
  }
  for (i = 0; i < 6; i++)
  {
    freq_khz[i] %= 10;
  }
  leading_zero = 1;
  // print the encoder position multiplied by the refernce frequency
  for ( i = 0; i < 6; i++ )
  {
    if ( leading_zero && (i == 2) )
      leading_zero = 0;

    if ( leading_zero && (freq_khz[i] == 0) )
    {
      lcd.write(0x20);
    }
    else
    {
      leading_zero = 0;
      lcd.write(freq_khz[i] + 0x30);
    }
    if ( i == 2 )
    {
      lcd.print(".");
    }
  }
  lcd.print(" Mhz");
  if ( ptt_in_n )
  {
    lcd.print(" RX");
  }
  else
  {
    lcd.print(" TX");
  }

  for ( i = 0; i < MAX_ANALOGUE; i++)
  {
    sensorValue[i] = analogRead(sensorPin[i]);
  }

#ifdef CONSOLE

  if (Serial.available() > 0)
  {
    // get incoming byte:
    inByte = Serial.read();
    switch ( inByte )
    {
      case 'A':
      case 'a':
        // ADC:
        // read the value from the sensor:
        for ( i = 0; i < MAX_ANALOGUE; i++)
        {
          Serial.print("Analog[");
          Serial.print(i);
          Serial.print("] = ");
          Serial.print(sensorValue[i], DEC);
          Serial.print(" ");
        }
        Serial.println();
        break;
      case 'E':
      case 'e':
        // read a byte from the current address of the EEPROM
        value = EEPROM.read(address);

        Serial.print("EEPROM[");
        Serial.print(address);
        Serial.print("] = ");
        Serial.print(value, DEC);
        Serial.println();

        // advance to the next address of the EEPROM
        address = address + 1;

        // there are only 512 bytes of EEPROM, from 0 to 511, so if we're
        // on address 512, wrap around to address 0
        if (address == 512)
          address = 0;
        break;

      case 'I':
      case 'i':
        // I2C / TWI Digital Pot
        Wire.beginTransmission(44); // transmit to device #44 (0x2c)
        // device address is specified in datasheet
        Wire.write(byte(0x00));     // sends instruction byte
        Wire.write(val);            // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting
        val++;        // increment value
        if (val == 64) // if reached 64th position (max)
        {
          val = 0;    // start over from lowest value
        }
        break;

      case 'L':
      case 'l':
        // write a message to the LCD display
        Serial.print("Type to LCD Display");
        Serial.println();
        lcd.setCursor(0, 1);
        while ( (inByte != 'X') && (inByte != 'x') )
        {
          if (Serial.available() > 0) {
            // get incoming byte:
            lcd.write(Serial.read());
          }
        }
        Serial.println();
        Serial.print("Exit LCD Display");
        Serial.println();
        break;

      default:
        break;
    }
  }
#endif
}
