// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Which Pin the buttons are in
int starterBtn = 7;
int reduceBtn = 9;
int restBtn = 8;

// Flags for loop manipulation
int start_flag = 0;
int rest_flag = 0;
int lock_flag = 0;
int buzzer_flag = 0;

// Timer variables
int counter = 0;
int cache_counter = 0;

// Async Timer variables
unsigned long LEDStartTime = 0;
unsigned long buzzerStartTime;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long second = 200; //In milliseconds

void setup() {
  lcd.begin(16, 2);
  pinMode(10, OUTPUT); // For Buzzer
  pinMode(6, OUTPUT); // For LED
  pinMode(starterBtn, INPUT_PULLUP);
  pinMode(reduceBtn, INPUT_PULLUP);
  pinMode(restBtn, INPUT_PULLUP);
}

void clearRow(byte rowToClear) // Clearing a row of chars
{
  lcd.setCursor(0, rowToClear);
  lcd.print("                ");  
}

void showCounter(int num) // Show Counter on LCD
{
  lcd.setCursor(0, 0);
  lcd.print("  ");
  lcd.setCursor(0, 0);
  lcd.print(counter);
}

void loop() {

  currentMillis = millis();  // Get the current "time" (actually the number of milliseconds since the program started)
  
  if (counter > 0 && counter > 9 && currentMillis - startMillis >= second){
    // Decrements counter every x amount of ms
    
    counter = counter - 1;
    
    if (rest_flag == 0) { // Only show timer during work time
      lcd.setCursor(0, 0);
      lcd.print(counter);
    }

    startMillis = currentMillis;  // IMPORTANT to save the start time of counter change
  }
  else if (counter < 10 && counter > 0 && currentMillis - startMillis >= second) {
    // To remove double digits in the counter when below 10
    
    counter = counter - 1;
    
    if (rest_flag == 0) { // Only show timer during work time
      lcd.setCursor(0, 0);
      lcd.print("  ");
      lcd.setCursor(0, 0);
      lcd.print(counter);
    }

    startMillis = currentMillis;  // IMPORTANT to save the start time of counter change
  }
  else if (rest_flag == 0) { // Only show timer during work time
    // Prints the current counter value constantly
    lcd.setCursor(0, 0);
  	lcd.print(counter);
  }
  else{
  	lcd.setCursor(0, 0);
  	lcd.print("   ");
  }
  
  
  if (counter <= 0 && start_flag == 1 && rest_flag == 0){ 
  // After counter reaches 0 and user's last button press was one of the work button
    lcd.setCursor(0, 1);
    lcd.print("Take a break!");
    
    if (buzzer_flag == 0) { // Async counter for buzzer to buzz for short time
      digitalWrite(10, HIGH);
      buzzer_flag = 1;
      buzzerStartTime = millis();
    }

    if (buzzer_flag == 1 && currentMillis - buzzerStartTime >= 600) {
      digitalWrite(10, LOW);
    }
  }
  else if (counter <= 0 && rest_flag == 1) { 
  // After counter reaches 0 and user's last button press was break button
  	lcd.setCursor(0, 1);
    lcd.print("Break time over!");
    
    if (currentMillis - LEDStartTime >= 650) { // Blink LED with 650 delay between on and off
    	LEDStartTime = currentMillis;

        if (digitalRead(6) == LOW) { // Turn LED on if off, off if on
          digitalWrite(6, HIGH);
        } 
      
        else {
          digitalWrite(6, LOW);
        }
    }
    
  }
    
  else{ // Constantly turns off LED and Buzzer
    digitalWrite(10, LOW);
    digitalWrite(6, LOW);
  }
  
  
  int start_counter = digitalRead(starterBtn);
  // Left most button to reset counter back to the orignal 60
  if (start_counter == LOW){ // Button is pushed
    counter = 60; 
    start_flag = 1; // Lets code knows the application can start
    cache_counter = 60; // Resets the cache
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    rest_flag = 0; // Lets code know user wants to work
    buzzer_flag = 0; // Rests the buzzer
    delay(200); // For debounce logic, btn will be registered multiple times without this
    startMillis = millis();  // Initial start time
  }
  
  
  int reduce_counter = digitalRead(reduceBtn);
  // Middle button to reduce previous counter by 25%
  if (reduce_counter == LOW){ // Button is pushed
    counter = cache_counter * 0.75; 
    cache_counter = counter;
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    rest_flag = 0; // Lets code know user wants to work
    buzzer_flag = 0; // Rests the buzzer
    delay(200); // For debounce logic, btn will be registered multiple times without this
    startMillis = millis();  // Initial start time
  }
  
  int rest_counter = digitalRead(restBtn);
  // Right most button to let user rest for 15 counters
  if (rest_counter == LOW){ // Button is pushed
    counter = 15; // User is allowed 15 counter of break
    rest_flag = 1; // Lets code know user wants to rest
    buzzer_flag = 0; // Rests the buzzer
    lcd.setCursor(0, 1);
    lcd.print("Rest Well!         ");
    delay(200); // For debounce logic, btn will be registered multiple times without this
    startMillis = millis();  // Initial start time
  }
  
}











