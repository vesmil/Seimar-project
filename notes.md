# Dočasná dokumentace

*Zde si budu psát předběžné poznámky k vývoji*

## Setup

Jako základní setup jsem rozběhl Docker kontejnery Vivado a Petalinux (oboje na verzi 2021.2)

Následně jsem využil již hotový FPGA projekt ze kterého jsem vyexportoval hardwarový `.xsa` sobour  
Ten jsem pak použil v kontejneru PetaLinux na build projektu

Hotový build jsem nahrál na SD kartu se kteoru jsem PetaLinux nabootoval

V této fázi jsem již mohl V QtCreator pomocí cross kompilace (odeslání přes SSH) vybuildovat projekt 
Nastavení QtCreator: ...

**TODO: více podrovně + odkazy na využitý software**

## QT projekt

Je potřeba zobrazit výstup z kamery - použití GStreamer? Základ již hotová appka na GitLabu

Je potřeba být schopen s kamerou komunikovat - viz. [následující kapitola](##Komunikace s kamerou)

...

## Komunikace s kamerou

Použit bude pravděpodobně VISCA protokol
