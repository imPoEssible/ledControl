int light_mode = 0;
byte red_pin = 3;
byte blue_pin = 5;
byte green_pin = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(red_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
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
      light_fade_up(red_pin);
      light_fade_up(green_pin);
      light_fade_down(red_pin);
      light_fade_up(blue_pin);
      light_fade_down(blue_pin);
      light_fade_up(red_pin);
      light_fade_down(blue_pin);
      break;
  }
}

void light_blink(byte pin_number){
  analogWrite(pin_number, 255);
  delay(100);
  analogWrite(pin_number, 0);
  delay(100);
}

void light_fade_up(byte pin_number){
  for (byte x = 0; x < 255; x++){
    analogWrite(pin_number, x);
    delay(30);
  }
}

void light_fade_down(byte pin_number){
  for (byte x = 255; x > 0; x--){
    analogWrite(pin_number, x);
    delay(30);
  }
}

void two_light_fade(byte pin_number1, byte pin_number2){
  light_fade_up(pin_number1);
  light_fade_up(pin_number2);
  light_fade_down(pin_number1);
  light_fade_down(pin_number2);
}
