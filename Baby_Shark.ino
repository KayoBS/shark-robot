//Fiz praticamente nenhuma alteração significativa, mas vou indicar com um "ATR:" onde eu tiver alterado
#include <NewPing.h>

NewPing sens(3, 2);
byte led_dire = 4, led_esq = 5;
int alea[10];
float dist;
byte vez=0;

//ATR: criei essas variáveis para facilitar a minha vida. Dedutivelmente, são as velocidades
const byte min_velocity = 60;
const byte max_velocity = 75;

//Não entendi exatamente de onde veio esse crusamento entre POO e programação estruturada
//(isso é coisa da última pessoa a mexer)
struct motores{
  byte sent_1, sent_2, potencia;
  
  void andar(bool sent1, bool sent2, int pot){
    digitalWrite(sent_1, sent1);
    digitalWrite(sent_2, sent2);
    analogWrite(potencia, pot); //ATR: no lugar de pot, estava por padrão 150, sempre, independetemente do valor passado como argumento
  }
};
motores motor_esq, motor_dire;
void setup() {
  pinMode(led_esq, OUTPUT);
  pinMode(led_dire, OUTPUT);

  Serial.begin(9600);
  motor_esq.sent_1 = 8;
  motor_esq.sent_2 = 9;
  motor_esq.potencia = 10;

  motor_dire.sent_1 = 6;
  motor_dire.sent_2 = 7;
  motor_dire.potencia = 11;

  pinMode(motor_esq.sent_1, OUTPUT);
  pinMode(motor_esq.sent_2, OUTPUT);
  pinMode(motor_dire.potencia, OUTPUT);

  pinMode(motor_esq.potencia, OUTPUT);
  pinMode(motor_dire.sent_1, OUTPUT);
  pinMode(motor_dire.sent_2, OUTPUT);

  for(int i=0; i<10; i++){
    alea[i] = random(2);
  }
  for(int i=0; i<10; i++){
    Serial.println(alea[i]);
  }
}

void loop() {
  vez++;
  if(vez == 9){
    vez = 0;
  }
  dist = sens.ping_cm();

  /*ATR: coloquei esse tanto de informação no monitor Serial para entender melhor
  o funcionamento desse código na prática. Talvez seja isso a causa daquele problema
  do robô simplesmente parar e apagar a luz da serial, não resolvendo nem com o
  botão de reset*/
  Serial.print("-!- dist=");
  Serial.print(dist);
  Serial.print(" :: alea[");
  Serial.print(vez);
  Serial.print("]=");
  Serial.print(alea[vez]);
  Serial.println(" -!-");

  motor_esq.andar(1, 0, max_velocity);
  motor_dire.andar(1, 0, max_velocity + 20);
  
  //ATR: antes a condição era apenas dist<15, mas mudei isso, porque, no começo dos testes, ele dava muitos falsos zeros
  if(dist<15 && dist>1){
    
    if(alea[vez] == 0){
      digitalWrite(led_dire, 0);
      digitalWrite(led_esq, 1);

      //ATR: coloquei as velocidades max e min mais ou menos algum valor empiricamente, mas antes estavam todos como 50
      motor_esq.andar(1, 0, max_velocity - 15);
      motor_dire.andar(0, 1, min_velocity + 15);
      delay(1000);
    }else{
      digitalWrite(led_dire, 1);
      digitalWrite(led_esq, 0);
      motor_dire.andar(1, 0, max_velocity);
      motor_esq.andar(0, 1, min_velocity - 5);
      delay(1000);
    }
  }
  digitalWrite(led_esq, 0);
  digitalWrite(led_dire,0);
}