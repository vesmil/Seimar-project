# Zobrazení streamu 4k kamery na Zynq Ultrascale+

## Úvod

Cílem mého ročníkového projektu bude vytvořit program s grafickým rozhraním na platformě Zynq Ultrascale+ s operačním systém PetaLinux pro zobrazení streamu ze 4k Sony kamery.

Kromě zobrazení bude možné také v grafickém rozhraní možné kameru ovládat prostřednictvím komunikace přes UART (VISCA protokol) a to jednak změnit standardní vlastnosti jako nastavení expozice, zoom, ostření, atd. a také více specifické vlastnosti jako nastavení kvality odesílaného obrazu.

Následně bude také možnost obrazový stream uložit na SSD - v první řadě v RAW formátu a později i enkódovaně (je pravdědponé, že k enkódování bude využit přímo hardwarový modul).

Pro rozšíření bude možné implementovat zobrazení i jiné než visible kamery a odesílání dat po ethernetu.

Grafický výstup bude na desce prostřednictvím DisplayPort.

Program bude napsán v C++ a grafické rozhraní bude implementováno pomocí frameworku QT.  
Videostream z kamery bude zobrazen pravděpodobně pomocí knihovny GStreamer.

*Schéma grafického rozhraní:*

<img src="README.assets/UI.png" alt="UI" style="zoom:60%;" />

## Hardware

### MPSoC - [Zynq UltraScale+](https://www.xilinx.com/products/silicon-devices/soc/zynq-ultrascale-mpsoc.html)

Jedná se o MPSoC (Multiprocessor system on a chip) od společnosti Xilinx na kterém se nachází ARM procesor a programovatelné hradlové pole (FPGA).

Bude použit jako jako součást modulu [Trenz TE820-04](https://wiki.trenz-electronic.de/display/PD/TE0820+TRM). Ten mimo jiné obsahuje 2GB RAM, 8 GB eMMC paměť, 128 MB flash paměť pro bootování a mnoho pinů a kontektorů.

### Nosná deska

*Dočasně [Trenz TE0701-06](https://wiki.trenz-electronic.de/display/PD/TE0701+TRM), následně vlastní deska ze spolupráce s ČVUT*

Nosná deska přidá k základnímu modulu SSD disk a veškeré potřebné rozhraní - především tedy DisplayPort, ethernet a port pro připojení kamery.

#### 4k kamera - [Sony FCB-ER8550](https://www.image-sensing-solutions.eu/FCB-ER8550.html)

Kamerá, která podporuje přes UART podporuje VISCA protokol, ten slouží pro nastavení vlastností jako optický zoom, ostření či a expozice.

Kamera bude odesílat obraz ve formátu YCbCr.

### HW schéma projektu:

<img src="README.assets/Scheme.png" alt="Scheme" style="zoom: 80%;" />

## Provedení

### Současný stav

V současné chvíli nejsou ještě hotové dvě hardwarové věci - převodník výstupu kamery na desku a hradlové pole pro zprostředkování streamu pro procesor. To ale ovšem není pro postup potřeba, jelikož je na FPGA připraven test pattern generátor, který mi bude dočasně generovat náhodný obraz.

Navíc se stále čeká na nosnou desku od ČVUT, která místo HDMI nabídne DisplayPort. HDMI u aktuální desky totiž nevysílá žádný obraz a pouze je k němu přístup z hradlového pole. V nejhorším případě mám ale k dispozici desku na které DisplayPort je a s úpravou prostředí by šla využít.

### TODO

- [x] Specifikace
- [x] Prázdný QT projekt
- [x] Setup kompilace
- [ ] RAW stream - GStreamer
    - [x] Na SD kartu
        - [x] Příkazový řádek
        - [x] v C++
        - [ ] (Volitelně) Vyřešit proč SD karta nestíhá - na ČVUT desce bude SSD 
    - [ ] Přes ethernet
        - [x] Příkazový řádek
        - [ ] C++
          - [x] Základ
          - [ ] Objektový návrh
        - [x] Klient
- [ ] Enkódovací modul hotový (počkat či dočasně udělat softwarově)
- [ ] Zobrazit stream na display port (note: HDMI na Trenz desce je problematický. je potřeba použít Zynq desku nebo počkat na ČVUT desku)
- [ ] Zobrazit menu
  - [ ] Práce se streamem - ukládání, atd.
  - [ ] Komunikace s kamerou - VISCA protkol
    - [ ] Setup dočasné kamery s HDMI na monitor a UART do desky
    - [ ] Funguící protkol
    - [ ] Všechny potřebné příkazy
- [ ] Bonusy:
  - [ ] Komunikace s deskou pomocí ethernetu
  - [ ] Zobrazení jiné kamery než s viditelným světlem
  - [ ] ...

---

**Ročníkový projekt na MFF v zimním semestru 2022/23**  
Autor Milan Veselý ve spolupráci s Workswell s.r.o.
