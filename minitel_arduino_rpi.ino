/* 
This code is an adaptation from the following article:
https://www.instructables.com/Old-School-Minitel-Laptop/
*/

#include <Keypad.h>
#include <HID-Project.h> //https://github.com/NicoHood/HID/wiki

const byte ROWS = 8; 
const byte COLS = 8;

char keys[ROWS][COLS] = {
/* Here the number is the number on the Arduino Pro Micro Pinout
     //   A0  A1  A2  A3   4   5   6   10
/* 15 */{'c','D','S','Q','KEY_ENTER','l',' ',' '},
/* 14 */{'L','F','A','Y',',','r','s',' '},
/* 2  */{'K','G','T','Z','.','a','KEY_LEFT_SHIFT',' '},
/* 3  */{'J','H','R','E','"',' ','g',' '},
/* 7  */{'V','C','U',';','e','r','s',' '},
/* 8  */{'B','X','I','-','*','4','7','1'},
/* 9  */{'P','W','N',':','O','5','8','2'},
/* 11 */{'M',' ','O','?','#','9','6','3'}};





/* Here the number is the number on the ribon cable [1] is not used
         [5] [4] [3] [2] [15][14][13][9] 
   [6]  {'c','D','Q','S','r','l',' ',' '},
   [7]  {'L','F','Y','A',',','r','s',' '},
   [17] {'K','G','Z','T','.','a','c',' '},
   [16] {'J','H','E','R','"',' ','g',' '},
   [12] {'V','C',';','U','e','r','s',' '},
   [11]{'B','X','-','I','*','4','7','1'},
   [10] {'P','W',':','N','O','5','8','2'},
   [8]  {'M',' ','?','O','#','9','6','3'}};

*/

byte rowPins[ROWS] = {6,7,8,9,15,18,19,20};
byte colPins[COLS] = {2,3,4,5,10,16,14,21};

// Initialize a Keyboard Class with the matrix above
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  /* Use this to use the Arduino Serial Monitor to Debug
  Serial.begin(9600);
  Serial.println("Test de clavier 16 touches");
  */
  
  BootKeyboard.begin();
  delay(1000);

  // Permanent key press
  unsigned int time_hold = 4;
  keypad.setHoldTime(time_hold);
  
  //Anti rebound
  unsigned int time_anti_rebond = 4;  //4 ms
  keypad.setDebounceTime(time_anti_rebond);
}


void loop(){
  /* Use this to use the Arduino Serial Monitor to Debug
  Serial.print(key);
  */
  
  char key = keypad.getKey();

  // Switch case to convert some key on the matrix to a function like Backspace 
  // All the constant from the HID-Project librery can be found here : https://github.com/NicoHood/HID/blob/master/src/KeyboardLayouts/ImprovedKeylayouts.h#L61
  switch (key){
    case 'r':
      BootKeyboard.write(KEY_BACKSPACE);
      break;
    case 'e':
      BootKeyboard.write(KEY_ENTER);
      break;
    default:
      BootKeyboard.write(key);
      break;
  }
  
}
