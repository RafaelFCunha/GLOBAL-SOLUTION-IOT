#include <LiquidCrystal.h> //Inclusão da Biblioteca
LiquidCrystal lcd(9, 11, 10, 5, 4, 3, 2);

int trigger = 12;
int echo = 6;
int led = 8;
int led2 = 7;

long duration = 0;
int cm = 0;
int inch = 0;

int backLight = 13;
unsigned long lcdTimer = 0;
unsigned long lcdInterval = 500;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH);// Liga backlight. Substituir 'HIGH' por 'LOW' para desligar a luz de fundo.

  lcd.begin(16, 2);//Colunas, linhas. Use 16,2 para display LCD 16x2
  lcd.clear();// Inicializa o display com uma tela vazia
  lcd.setCursor(0, 0);//Posiciona o cursor na coluna 0, linha 0 (primeira linha)
  lcd.print("Vagas Livres: ");//Escreve o texto desejado
}

void loop() {  
  lcd.display();// Liga Display:
  
  // put your main code here, to run repeatedly:
  digitalWrite(trigger, LOW);
  digitalWrite(trigger, HIGH);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);
  cm = duration*0.034/2;
  inch = duration*0.0133/2;

  if (inch < 79){
    digitalWrite(led, HIGH);
    digitalWrite(led2, LOW);
    lcdTimer = millis();
    lcd.setCursor(15, 0);
    lcd.print("0");
    lcd.setCursor(0, 1);
    
  } else {
    digitalWrite(led, LOW);
    digitalWrite(led2, HIGH);
    lcdTimer = millis();
    lcd.setCursor(15, 0);
    lcd.print("1");
    lcd.setCursor(0, 1);
  }

  if (inch < 100 ) {
    Serial.print("Inches: ");
    Serial.println(inch);
    Serial.print("Cm: ");
    Serial.println(cm);
  }
  
  delay(500);
}
