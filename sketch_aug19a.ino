// Define constants and variables
const int buttonPin = 2;   
int buttonState = HIGH;        
int lastButtonState = HIGH;    
bool isNameBlinking = false;    
char userName[100];           
int userNameIndex = 0;             

// Setup function
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600);
  Serial.println("Please enter the name you want to display in Morse code (a-z, space):");
}

// Function to display a dot
void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Function to display a dash
void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Function to convert a character to Morse code
void morseEncoding(char nameChar) {
  const char* morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                             "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                             "..-", "...-", ".--", "-..-", "-.--", "--.."};

  if (nameChar >= 'a' && nameChar <= 'z') {
    int index = nameChar - 'a';  
    const char* code = morseCode[index];
    
    for (int i = 0; code[i] != '\0'; i++) {
      if (code[i] == '.')
        dot();
      else if (code[i] == '-')
        dash();
    }
  }
}

// Main loop
void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    isNameBlinking = !isNameBlinking; 
    userNameIndex = 0; 
  }

  lastButtonState = buttonState;

  if (isNameBlinking) {
    if (userName[userNameIndex] != '\0') {
      char character = userName[userNameIndex];
      morseEncoding(character);
      delay(1000); 
      userNameIndex++;
    } else {
      isNameBlinking = false; 
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW); 
  }

  // Read user input from Serial Monitor
  while (Serial.available() > 0) {
    char inputChar = Serial.read();
    if (inputChar == '\n' || userNameIndex >= sizeof(userName) - 1) {
      userName[userNameIndex] = '\0'; 
      userNameIndex = 0; 
      Serial.print("Name ");
      Serial.print(userName);
      Serial.println(" is now blinking");
      isNameBlinking = true; 
    } else {
      userName[userNameIndex] = inputChar;
      userNameIndex++;
    }
  }
}
