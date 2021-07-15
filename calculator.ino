#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys [ROWS] [COLS] = {
  {'7','4','1','C',},
  {'8','5','2','0',},
  {'9','6','3','=',},
  {'/','*','-','+',}
};
byte rowPins[ROWS] = {2 ,3 ,4 ,5};
byte colPins[COLS] = {6, 7,8, 9};

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


boolean presentValue = false;
boolean next = false;
boolean final = false;
String num1, num2;
int answer;
char op;

void setup()
{
  Serial.begin(9600);
}

void loop(){
  char key = myKeypad.getKey();

  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'))
  {
    if (presentValue != true)
    {
      num1 = num1 + key;
      int numLength = num1.length();
      Serial.print(numLength, 0); //to adjust one whitespace for operator
      Serial.print(num1);
    }
    else 
    {
      num2 = num2 + key;
      int numLength = num2.length();
      Serial.print( numLength-1,0);
      Serial.println(num2);
      final = true;
    }
  }

  else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))
  {
    if (presentValue == false)
    {
      presentValue = true;
      op = key;
      Serial.println(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '='){
    if (op == '+'){
      answer = num1.toInt() + num2.toInt();
    }
    else if (op == '-'){
      answer = num1.toInt() - num2.toInt();
    }
    else if (op == '*'){
      answer = num1.toInt() * num2.toInt();
    }
    else if (op == '/'){
      answer = num1.toInt() / num2.toInt();
    }   
      
     
      Serial.println(answer);
      
  }
  else if (key != NO_KEY && key == 'C'){
   
    presentValue = false;
    final = false;
    num1 = "";
    num2 = "";
    answer = 0;
    op = ' ';
  }
}
