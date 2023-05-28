-- CreateTable
CREATE TABLE "Driver" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "nome" TEXT NOT NULL,
    "rfid" INTEGER NOT NULL,
    "ativado" BOOLEAN NOT NULL DEFAULT false,
    "cadastro" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "vehicleId" INTEGER NOT NULL,
    CONSTRAINT "Driver_vehicleId_fkey" FOREIGN KEY ("vehicleId") REFERENCES "Vehicle" ("id") ON DELETE RESTRICT ON UPDATE CASCADE
);

-- CreateTable
CREATE TABLE "Vehicle" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "placa" TEXT NOT NULL,
    "rfid" INTEGER NOT NULL,
    "limite" INTEGER NOT NULL,
    "cadastro" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "alterado" DATETIME NOT NULL,
    "ativado" BOOLEAN NOT NULL DEFAULT false
);

-- CreateTable
CREATE TABLE "Attendant" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "nome" TEXT NOT NULL,
    "rfid" INTEGER NOT NULL,
    "ativado" BOOLEAN NOT NULL DEFAULT false,
    "cadastro" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- CreateIndex
CREATE UNIQUE INDEX "Driver_rfid_key" ON "Driver"("rfid");

-- CreateIndex
CREATE UNIQUE INDEX "Driver_vehicleId_key" ON "Driver"("vehicleId");

-- CreateIndex
CREATE UNIQUE INDEX "Vehicle_rfid_key" ON "Vehicle"("rfid");

-- CreateIndex
CREATE UNIQUE INDEX "Attendant_rfid_key" ON "Attendant"("rfid");
