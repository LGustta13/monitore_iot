/*
  Warnings:

  - You are about to drop the column `vehicleId` on the `Driver` table. All the data in the column will be lost.
  - Added the required column `veiculoId` to the `Driver` table without a default value. This is not possible if the table is not empty.

*/
-- CreateTable
CREATE TABLE "Supply" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "inicio" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "fim" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "dreno" REAL NOT NULL DEFAULT 0,
    "latitude" REAL NOT NULL DEFAULT 0,
    "longitude" REAL NOT NULL DEFAULT 0,
    "tanqueId" INTEGER NOT NULL,
    "frentistaId" INTEGER NOT NULL,
    "motoristaId" INTEGER NOT NULL,
    "veiculoId" INTEGER NOT NULL,
    CONSTRAINT "Supply_tanqueId_fkey" FOREIGN KEY ("tanqueId") REFERENCES "Tank" ("id") ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT "Supply_frentistaId_fkey" FOREIGN KEY ("frentistaId") REFERENCES "Attendant" ("id") ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT "Supply_motoristaId_fkey" FOREIGN KEY ("motoristaId") REFERENCES "Driver" ("id") ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT "Supply_veiculoId_fkey" FOREIGN KEY ("veiculoId") REFERENCES "Vehicle" ("id") ON DELETE RESTRICT ON UPDATE CASCADE
);

-- CreateTable
CREATE TABLE "Tank" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "nome" TEXT NOT NULL
);

-- RedefineTables
PRAGMA foreign_keys=OFF;
CREATE TABLE "new_Driver" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "nome" TEXT NOT NULL,
    "rfid" INTEGER NOT NULL,
    "ativado" BOOLEAN NOT NULL DEFAULT false,
    "cadastro" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "veiculoId" INTEGER NOT NULL,
    CONSTRAINT "Driver_veiculoId_fkey" FOREIGN KEY ("veiculoId") REFERENCES "Vehicle" ("id") ON DELETE RESTRICT ON UPDATE CASCADE
);
INSERT INTO "new_Driver" ("ativado", "cadastro", "id", "nome", "rfid") SELECT "ativado", "cadastro", "id", "nome", "rfid" FROM "Driver";
DROP TABLE "Driver";
ALTER TABLE "new_Driver" RENAME TO "Driver";
CREATE UNIQUE INDEX "Driver_rfid_key" ON "Driver"("rfid");
CREATE UNIQUE INDEX "Driver_veiculoId_key" ON "Driver"("veiculoId");
PRAGMA foreign_key_check;
PRAGMA foreign_keys=ON;

-- CreateIndex
CREATE UNIQUE INDEX "Tank_id_key" ON "Tank"("id");
