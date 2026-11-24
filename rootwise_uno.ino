const bool USE_DIY_PROBE = true;
const bool CALIBRATING   = true;   // step 1: true. step 2: false for the demo

int DRY_RAW = 1000;   // replace with your raw reading in AIR
int WET_RAW = 400;    // replace with your raw reading in WATER

const int LOW_PCT  = 35;   // below this: valve opens
const int HIGH_PCT = 55;   // above this: valve closes

const int PROBE_PIN = A0;
const int VALVE_LED = 13;
bool valveOpen = false;

void setup() {
  Serial.begin(9600);
  pinMode(VALVE_LED, OUTPUT);
  if (USE_DIY_PROBE) pinMode(PROBE_PIN, INPUT_PULLUP);
  else pinMode(PROBE_PIN, INPUT);
}

int readAvg() {
  long s = 0;
  for (int i = 0; i < 10; i++) { s += analogRead(PROBE_PIN); delay(5); }
  return s / 10;
}

void loop() {
  int raw = readAvg();
  int moisture = constrain(map(raw, DRY_RAW, WET_RAW, 0, 100), 0, 100);

  if (moisture < LOW_PCT)   valveOpen = true;
  if (moisture >= HIGH_PCT) valveOpen = false;
  digitalWrite(VALVE_LED, valveOpen ? HIGH : LOW);

  if (CALIBRATING) {
    Serial.print("raw: ");        Serial.print(raw);
    Serial.print("   moisture: "); Serial.print(moisture);
    Serial.println("%");
  } else {
    Serial.print("Moisture:");  Serial.print(moisture);
    Serial.print(",DryLimit:"); Serial.print(LOW_PCT);
    Serial.print(",WetLimit:"); Serial.print(HIGH_PCT);
    Serial.print(",Valve:");    Serial.println(valveOpen ? 100 : 0);
  }
  delay(250);
}