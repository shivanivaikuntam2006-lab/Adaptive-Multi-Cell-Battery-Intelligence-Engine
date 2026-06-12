float cell[4];

void setup() {
  Serial.begin(9600);

  // Seed random generator for temperature simulation
  randomSeed(analogRead(A5));

  Serial.println("Adaptive Multi-Cell Battery Intelligence Engine");
  Serial.println("==============================================");
}

void loop() {

  // Simulate Li-ion cells (3.0V to 4.2V)
  cell[0] = 3.0 + (analogRead(A0) / 1023.0) * 1.2;
  cell[1] = 3.0 + (analogRead(A1) / 1023.0) * 1.2;
  cell[2] = 3.0 + (analogRead(A2) / 1023.0) * 1.2;
  cell[3] = 3.0 + (analogRead(A3) / 1023.0) * 1.2;

  // Pack Voltage
  float packVoltage = 0;

  for (int i = 0; i < 4; i++) {
    packVoltage += cell[i];
  }

  // Average Voltage
  float averageVoltage = packVoltage / 4.0;

  // Strongest & Weakest Cell
  float maxV = cell[0];
  float minV = cell[0];

  int strongestCell = 1;
  int weakestCell = 1;

  for (int i = 1; i < 4; i++) {

    if (cell[i] > maxV) {
      maxV = cell[i];
      strongestCell = i + 1;
    }

    if (cell[i] < minV) {
      minV = cell[i];
      weakestCell = i + 1;
    }
  }

  // Imbalance %
  float imbalance = ((maxV - minV) / averageVoltage) * 100.0;

  // SOC Calculation
  float soc = ((averageVoltage - 3.0) / 1.2) * 100.0;

  if (soc > 100) soc = 100;
  if (soc < 0) soc = 0;

  // Temperature Simulation
  float temperature = random(25, 51);

  // Battery Health Score
  int healthScore = 100;

  if (imbalance > 5)
    healthScore -= 20;

  if (minV < 3.2)
    healthScore -= 30;

  if (temperature > 45)
    healthScore -= 20;

  if (healthScore < 0)
    healthScore = 0;

  // Display Results
  Serial.println();
  Serial.println("================================");

  for (int i = 0; i < 4; i++) {
    Serial.print("Cell ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(cell[i], 2);
    Serial.println(" V");
  }

  Serial.println();

  Serial.print("Pack Voltage: ");
  Serial.print(packVoltage, 2);
  Serial.println(" V");

  Serial.print("Average Voltage: ");
  Serial.print(averageVoltage, 2);
  Serial.println(" V");

  Serial.println();

  Serial.print("Strongest Cell: ");
  Serial.println(strongestCell);

  Serial.print("Weakest Cell: ");
  Serial.println(weakestCell);

  Serial.print("Imbalance %: ");
  Serial.println(imbalance, 2);

  Serial.println();

  Serial.print("SOC: ");
  Serial.print(soc, 1);
  Serial.println("%");

  // Charge State
  if (soc >= 80) {
    Serial.println("Charge State: FULLY CHARGED");
  }
  else if (soc >= 50) {
    Serial.println("Charge State: GOOD");
  }
  else if (soc >= 20) {
    Serial.println("Charge State: LOW");
  }
  else {
    Serial.println("Charge State: CRITICAL");
  }

  Serial.println();

  // Cell Balancing Recommendation
  if (imbalance > 5) {
    Serial.println("ACTION: CELL BALANCING REQUIRED");
  }
  else {
    Serial.println("ACTION: NO BALANCING REQUIRED");
  }

  Serial.println();

  // Temperature
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  if (temperature > 45) {
    Serial.println("WARNING: OVER TEMPERATURE");
  }

  Serial.println();

  // Health Score
  Serial.print("Battery Health Score: ");
  Serial.print(healthScore);
  Serial.println("/100");

  Serial.println();

  // Battery Status
  if (minV < 3.0) {
    Serial.println("STATUS: PACK FAILURE");
  }
  else if (imbalance < 2) {
    Serial.println("STATUS: HEALTHY");
  }
  else if (imbalance < 5) {
    Serial.println("STATUS: MINOR IMBALANCE");
  }
  else if (imbalance < 10) {
    Serial.println("STATUS: CRITICAL IMBALANCE");
  }
  else {
    Serial.println("STATUS: PACK FAILURE");
  }

  Serial.println("================================");

  delay(3000);
}