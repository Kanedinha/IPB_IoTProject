#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// Crie um objeto MPU6050
Adafruit_MPU6050 mpu;

// Função para calcular o ângulo de pitch
float calculatePitch(float ax, float az) {
  return atan2(ax, az) * 180 / PI;
}

// Função para calcular o ângulo de roll
float calculateRoll(float ay, float az) {
  return atan2(ay, az) * 180 / PI;
}

void setup() {
  // Inicialize a comunicação serial
  Serial.begin(115200);
  Wire.begin(25,26);
  // Inicialize a comunicação I2C
  if (!mpu.begin()) {
    Serial.println("Falha ao encontrar o MPU6050. Verifique as conexões e tente novamente.");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 encontrado com sucesso!");
}

void loop() {
  // Variáveis para armazenar os dados do acelerômetro
  sensors_event_t a, g, temp;
  
  // Ler os valores brutos do acelerômetro e giroscópio
  mpu.getEvent(&a, &g, &temp);
  
  // Calcular os ângulos de pitch e roll
  float pitch = calculatePitch(a.acceleration.x, a.acceleration.z);
  float roll = calculateRoll(a.acceleration.y, a.acceleration.z);
  
  // Plotar os dados na serial
  Serial.print("Pitch: "); Serial.print(pitch); Serial.print(" ");
  Serial.print("Roll: "); Serial.println(roll);
  
  // Esperar um pouco antes de ler novamente
  delay(200); // Amostragem fixa de 1 segundo
}
