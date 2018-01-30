struct M {
  int digital_input;
  float distance_mm;
};
const int N =25;
struct M measured[N] ={{320,20},{356,30},{431,40},{531,50},{603,60},{668,70},{723,80},{769,90},{813,100},
                       {845,110},{866,120},{887,130},{903,140},{911,150},{922,160},{930,170},{935,180},{940,190},{944,200},
                       {947,210},{950,220},{952,230},{953,240},{955,250}} ;

int reading;
float distance;

String distanceOutput;
String distanceLabel = "Distance: ";
String readingOutput;
String readingLabel = "Analog Read Value: ";
String mm = " mm";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = analogRead(0);
  distance = Get_distance_from_voltage_reading(reading);
  readingOutput = readingLabel + String(reading);
  distanceOutput = distanceLabel + String(distance) + mm;
  Serial.println(readingOutput);
  Serial.println(distanceOutput);
  delay(1000);
}

float Get_distance_from_voltage_reading(int r){
  if(r >1000){
    return 1;
  }
  int i =0;
  while(i < N && measured[i].digital_input <= r){
    i++;
  }
  i--;
  
  float lower_bound = measured[i].distance_mm;
  int ub_idx = ((i+1) < N) ? i+1 : i;
  float upper_bound = measured[ub_idx].distance_mm;
  float interval_distance = measured[ub_idx].digital_input - measured[i].digital_input;
  float multiplier = ((r - measured[i].digital_input)/interval_distance);
  float value = lower_bound + (upper_bound - lower_bound)* multiplier;
  Serial.println(multiplier);
  return value;
}

