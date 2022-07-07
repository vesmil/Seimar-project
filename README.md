# Zobrazení streamu 4k kamery na Zynq Ultrascale+

**Ročníkový projekt na MFF v zimním semestru 2022/23**
Autor Milan Veselý ve spolupráci s Workswell s.r.o.

---

## Úvod

Cílem mého ročníkového projektu bude vytvořit program s grafickým rozhraním na platformě Zynq Ultrascale+ s operačním systém PetaLinux pro zobrazení LVDS streamu ze 4k Sony kamery.

Kromě zobrazení bude možné také v grafickém rozhraní možné kameru ovládat prostřednictvím komunikace přes UART a to jednak změnit standardní vlastnosti jako nastavení expozice, zoom, ostření, atd. a také více specifické vlastnosti jako nastavení kvality odesílaného obrazu *(detaily doplním po nastudování datasheet konkrétní Sony kamery)*. 

Následně bude také možnost obrazový stream uložit na SSD - v první řadě v RAW formátu a později i enkódovaně (je pravdědponé, že k enkódování bude využit přímo hardwarový modul.

Pro rozšíření bude možné implementovat zobrazení i jiné než visible kamery a odesílání dat po ethernetu.

Grafický výstup bude na desce prostřednictvím DisplayPort.

Program bude napsán v C++ a grafické rozhraní bude implementováno pomocí frameworku QT.

*Schéma grafického rozhraní:*

<img src="README.assets/UI.png" alt="UI" style="zoom:67%;" />

<div style="page-break-after: always;"></div>

## Hardware

### Xilinx Zynq UltraScale+

Jedná se o MPSoC (Multiprocessor system on a chip) s ARM procesorem.

#### Trenz kit (TE0701-06)

Bude pravděpodobně využit jako nosná deska pro Zynq

#### Sony 4k kamera s optickým zoomem

...bude doplněno později

### HW schéma projektu:

<img src="README.assets/Scheme.png" alt="Scheme" style="zoom: 80%;" />

---

## Provedení

### Současný stav

V současné chvíli nejsou ještě hotové dvě hardwarové věci - převodník výstupu kamery na desku a hradlové pole pro zprostředkování streamu pro procesor. To ale ovšem není pro postup potřeba, jelikož je na FPGA připraven test pattern generátor, který mi bude dočasně generovat náhodný obraz.

### Navrhovaný postup

1. V první řadě vytvořím nějaký základ v QT - místo pro menu a stream
2. Zobrazení obrazu z test pattern generátoru
3. Zprovoznění menu pro ovládání kamery
4. Zprovoznění menu pro ukládání obrazu
5. Bonusy...