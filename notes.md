# Development notes

*Zde si budu psát předběžné poznámky k vývoji*

## Setup

Jako základní setup jsem si stáhnul Petalinux a Vivado (oboje na verzi 2021.2) z [oficiálních stránek Xylinx](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2021-2.html) a následně oboje spustil v Doceker kontejneru. Jelikož součastí Vivada je GUI, musel jsem použít X Window System.

Následně jsem využil již hotový FPGA projekt svých kolegů ze kterého jsem vyexportoval hardwarový `.xsa` sobour  
Z toho jsem následně v PetaLinux vybuldil image, který jsem nahrál na SD kartu (tu jsem rozdělil na dvě partitions podle [tohoto návodu](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842385/How+to+format+SD+card+for+SD+boot)) a po té jsem mohl již desku nabootovat. (Zde jsem dostal postranní úkol napsat skript pro snadné bootování z emmc paměti). 

Nyní mě čeká příprava QtCreator a zajitšení cross kompilace (odeslání přes SSH) pro build projektu. 

## QT projekt

Je potřeba zobrazit výstup z kamery - použití GStreamer
Je potřeba být schopen s kamerou komunikovat - viz. [následující kapitola](##Komunikace s kamerou)

...

## Komunikace s kamerou

Použit bude pravděpodobně VISCA protokol
