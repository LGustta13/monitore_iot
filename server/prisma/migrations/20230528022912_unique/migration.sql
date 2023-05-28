-- RedefineTables
PRAGMA foreign_keys=OFF;
CREATE TABLE "new_Driver" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "nome" TEXT NOT NULL,
    "rfid" INTEGER NOT NULL,
    "ativado" BOOLEAN NOT NULL DEFAULT false,
    "cadastro" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "veiculoId" INTEGER DEFAULT 0,
    CONSTRAINT "Driver_veiculoId_fkey" FOREIGN KEY ("veiculoId") REFERENCES "Vehicle" ("id") ON DELETE SET NULL ON UPDATE CASCADE
);
INSERT INTO "new_Driver" ("ativado", "cadastro", "id", "nome", "rfid", "veiculoId") SELECT "ativado", "cadastro", "id", "nome", "rfid", "veiculoId" FROM "Driver";
DROP TABLE "Driver";
ALTER TABLE "new_Driver" RENAME TO "Driver";
CREATE UNIQUE INDEX "Driver_rfid_key" ON "Driver"("rfid");
CREATE UNIQUE INDEX "Driver_veiculoId_key" ON "Driver"("veiculoId");
PRAGMA foreign_key_check;
PRAGMA foreign_keys=ON;
