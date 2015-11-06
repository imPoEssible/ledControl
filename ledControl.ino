int light_mode = 0;
byte red_pin = 3;
byte blue_pin = 5;
byte green_pin = 6;
byte photoDiode_pin = A5;

int brightness;
long prevTime = 0;

void setup() {  
  pinMode(red_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(photoDiode_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    light_mode = Serial.parseInt();
  }
  switch(light_mode){
    case 1:
      light_blink(red_pin);
      break;
    case 2:
      light_blink(blue_pin);
      break;
    case 3:
      light_blink(green_pin);
      break;
    case 4:
      rainbow();
      break;
    case 5:
      if ((millis() - prevTime) > 1000){
        brightness = map(analogRead(photoDiode_pin), 500, 900, 0, 255);
        prevTime = millis();
      }
      analogWrite(red_pin, brightness);
  }
}

void reset(){
  analogWrite(red_pin, 0);
  analogWrite(blue_pin, 0);
  analogWrite(green_pin, 0);
}

void light_blink(byte pin_number){
  reset();
  delay(100);
  analogWrite(pin_number, 255);
  delay(100);
}

void light_fade_up(byte pin_number){
  for (byte x = 0; x < 255; x++){
    analogWrite(pin_number, x);
    delay(10);
  }
}

void light_fade_down(byte pin_number){
  for (byte x = 255; x > 0; x--){
    analogWrite(pin_number, x);
    delay(10);
  }
}

void rainbow(){
  reset();
  light_fade_up(red_pin);
  light_fade_up(green_pin);
  light_fade_down(red_pin);
  light_fade_up(blue_pin);
  light_fade_down(green_pin);
  light_fade_up(red_pin);
  light_fade_down(blue_pin);
}
