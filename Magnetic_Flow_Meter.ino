//Grady Hillhouse 2016

//L298N Pins
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

//Biphasic DC Pulse Electromagnet Voltage Signal Properties
const int     freq          = 1;     //Hertz
const double  duty_cycle    = 0.5;
const boolean reverse_mag   = false;  //Set to true if the two electromagnets are not running in the same direction (easier just to switch the wires on the H-bridge)
const double  signal_delay  = 0.5 / freq * duty_cycle * 1000.0;         //Duration in milliseconds that the voltage is high or low 
const double  off_delay     = 0.5 / freq * (1.0 - duty_cycle) * 1000.0; //Duration in milliseconds that the voltage is zero

//Other variables
unsigned long previous_millis = 0; //Milliseconds
boolean previous_direction = false;
boolean currently_off = true;

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  turn_off_magnets(); //Just in case
}

void loop()
{
  unsigned long current_millis = millis();
  
  if (currently_off)
  {
    if (current_millis - previous_millis >= off_delay)
    {
      previous_millis = current_millis;
      previous_direction = !previous_direction;
      activate_magnets(previous_direction);
      currently_off = false;      
    }
  }
  else
  {
    if (current_millis - previous_millis >= signal_delay)
    {
      previous_millis = current_millis;
      turn_off_magnets();
      currently_off = true;
    }
  }
}

void activate_magnets(boolean positive)
{
  if (positive && !reverse_mag)
  {
    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);
  }
  else if (positive && reverse_mag)
  {
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN4, HIGH);
  }
  else if (!positive && !reverse_mag)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN4, HIGH);
  }
  else if (!positive && reverse_mag)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
  }
}

void turn_off_magnets()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

