
#define ENA 7  
#define IN1 6 
#define IN2 9
#define ENB 12   
#define IN3 10
#define IN4 11



#define S_FL 8   
#define S_L  2   
#define S_M  5   
#define S_R  4   
#define S_FR 3   


const bool BLACK_IS_LOW = false;


int leftMotorSpeed  = 40;  
int rightMotorSpeed = 255;  
int turnSpeed       = 200;  
int hardTurnSpeed   = 255;  

inline bool isBlack(int value) {
  return BLACK_IS_LOW ? (value == LOW) : (value == HIGH);
}


void motorsForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftMotorSpeed);
  analogWrite(ENB, rightMotorSpeed);
}

void softLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, turnSpeed);
}

void softRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, 0);
}

void midLeft() { softLeft(); }
void midRight() { softRight(); }

void hardLeft() {
  
  digitalWrite(IN1, LOW);   
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW);

  
  analogWrite(ENA, 120);   
  analogWrite(ENB, 180);   
}

void hardRight() {
  
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);   
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 180);   
  analogWrite(ENB, 120);   
}



void stopAll() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


enum LastDir { STRAIGHT = 0, LEFT = 1, RIGHT = 2 };
LastDir lastSeen = STRAIGHT;

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(S_FL, INPUT);
  pinMode(S_L,  INPUT);
  pinMode(S_M,  INPUT);
  pinMode(S_R,  INPUT);
  pinMode(S_FR, INPUT);
}

void loop() {
  bool fl = isBlack(digitalRead(S_FL));
  bool l  = isBlack(digitalRead(S_L));
  bool m  = isBlack(digitalRead(S_M));
  bool r  = isBlack(digitalRead(S_R));
  bool fr = isBlack(digitalRead(S_FR));

  uint8_t state = (fl << 4) | (l << 3) | (m << 2) | (r << 1) | fr;

switch (state) {

  case 0b10000: // FL
  case 0b11000: // FL + L
  case 0b11100: // FL + L + M
    hardLeft();
    lastSeen = LEFT;
    break;


  case 0b00001: // FR
  case 0b00011: // R + FR
  case 0b00111: // M + R + FR
    hardRight();
    lastSeen = RIGHT;
    break;


  case 0b01100: // L + M
  case 0b01000: // L
    softLeft();
    lastSeen = LEFT;
    break;


  case 0b00110: // M + R
  case 0b00010: // R
    softRight();
    lastSeen = RIGHT;
    break;


  case 0b00100: // M
  case 0b01110: // L + M + R
    motorsForward();
    lastSeen = STRAIGHT;
    break;


  case 0b11111:
  case 0b11110:
  case 0b01111:
  case 0b10111:
  case 0b11101:
    motorsForward();
    lastSeen = STRAIGHT;
    break;

  default:
    if (lastSeen == LEFT)  hardLeft();
    else if (lastSeen == RIGHT) hardRight();
    else motorsForward();
    break;
}

  delay(10);
}
