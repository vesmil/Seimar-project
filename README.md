# Zobrazení streamu 4k kamery na Zynq Ultrascale+

## Úvod

Cílem mého ročníkového projektu bude vytvořit program s grafickým rozhraním na platformě Zynq Ultrascale+ s operačním systém PetaLinux pro zobrazení streamu ze 4k Sony kamery.

Kromě zobrazení bude možné také v grafickém rozhraní možné kameru ovládat prostřednictvím komunikace přes UART (VISCA protokol) a to jednak změnit standardní vlastnosti jako nastavení expozice, zoom, ostření, atd. a také více specifické vlastnosti jako nastavení kvality odesílaného obrazu.

Následně bude také možnost obrazový stream uložit na SSD - v první řadě v RAW formátu a později i enkódovaně (je pravdědponé, že k enkódování bude využit přímo hardwarový modul).

Pro rozšíření bude možné implementovat zobrazení i jiné než visible kamery a odesílání dat po ethernetu.

Grafický výstup bude na desce prostřednictvím DisplayPort.

Program bude napsán v C++ a grafické rozhraní bude implementováno pomocí frameworku QT.  
Videostream z kamery bude zobrazen pravděpodobně pomocí knihovny GStreamer.

## Hardware

#### MPSoC - [Zynq UltraScale+](https://www.xilinx.com/products/silicon-devices/soc/zynq-ultrascale-mpsoc.html)

Jedná se o MPSoC (Multiprocessor system on a chip) od společnosti Xilinx na kterém se nachází ARM procesor a programovatelné hradlové pole (FPGA).

#### Nosná deska

*Dočasně [ZCU104](https://www.xilinx.com/products/boards-and-kits/zcu104.html), následně deska ze spolupráce s ČVUT*

Nosná deska přidá k základnímu modulu SSD disk a veškeré potřebné rozhraní - především tedy DisplayPort, ethernet a port pro připojení kamery.

#### 4k kamera - [Sony FCB-ER8550](https://www.image-sensing-solutions.eu/FCB-ER8550.html)

Kamera, která podporuje přes UART podporuje VISCA protokol, ten slouží pro nastavení vlastností jako optický zoom, ostření či a expozice.

Kamera bude odesílat obraz ve formátu YCbCr.

### Současný stav hardware

Dokončení vlastní desky ze strany ČVUT je odloženo na neurčito. Projekt tedy bude finalizován na vývojové desce od Xylinx (ZCU104).

## Realizace

- [x] Setup
    - [x] Specifikace
    - [x] Prázdný QT projekt
    - [x] Setup zynq zařízení
    - [x] Setup kompilace
- [x] GStreamer
    - [x] RAW ukldání na SD kartu
        - [x] Příkazový řádek
        - [x] v C++
    - [x] RTP stream přes ethernet
        - [x] Příkazový řádek
        - [x] C++
        - [x] Klient
    - [x] Zobrazení kamery na Display Port
- [x] VISCA protokol
    - [x] Setup dočasné kamery s HDMI na monitor a UART do desky
    - [x] Funguící protokol
        - [x] Odesílání a přijímání příkazů
        - [x] Adresa a command buffer
    - [x] Všechny potřebné příkazy
        - [x] Command
        - [x] Inquiry
- [x] Menu
  - [x] Kostra menu
    - [x] Základní položky - submenu, hodnotové položky
    - [x] Závislosti jednotlivých položek
  - [x] Vyplnit menu
      - [x] Práce se streamem - zapnout, vypnout jednotlivé pipelines
      - [x] Komunikace s kamerou
- [ ] Upravit výsledek pro finální použití
    - [x] Visca - předělat na novou kameru
        - [x] Setup rozlišení
    - [x] Gstreamer
        - [x] Předělat stávající pipelines pro novou kameru
        - [x] Využít videomixer
    - [ ] Menu
        - [ ] Zařídit odesílání na KMS sink pro kombinaci obrazu
        - [ ] Detaily
    - [ ] Dokumentace

## Uživatelská příručka

Vzhledem k tomu, že program není mířen na cílového zákazníka, tak uživatelský manuál popíšu více stručně.

Po spuštění programu se zobrazí obraz z kamery. Jediná možnost je stisknutí šipky doleva či entru pro otevření menu.
Navigace v menu je intuitivní - šipku nahoru pro pohyb, šipka doprava pro potvrzení a šipka doleva pro zrušení či posun o úroveň výše.

V menu se nachází tři základní kategorie - **Functions**, **Stream** a **Advanced**.

### Functions

Nastavení všech podstatných vlastností kamery:

* Zoom
* Ostření
* Expozice
* Whitebalance
* Visibility Enhancment
* Backlight compoensation

### Stream

Vypínání a zapínání základních GStreamer pipeline - zobrazení na monitor, odeslání po RTP a uložení do souboru.

### Advanced

Nastavení rozlišení, barevného formátu (RGB vs YUV) a IP adresa na kterou se odesílají dat prostřednictvím RTP.

---

**Ročníkový projekt na MFF v letním semestru 2021/2022 a zimním semestru 2022/23**  
Autor Milan Veselý ve spolupráci s Workswell s.r.o.
