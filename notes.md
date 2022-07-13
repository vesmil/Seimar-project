# Development notes

*Zde si budu psát předběžné poznámky k vývoji*

## Setup

Jako základní setup jsem si stáhnul Petalinux a Vivado (oboje na verzi 2021.2) z [oficiálních stránek Xylinx](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2021-2.html) a následně oboje spustil v Doceker kontejneru. Jelikož součastí Vivada je GUI, musel jsem použít X Window System.

Následně jsem využil již hotový FPGA projekt svých kolegů. který v hradlovém poli generuje náhodný obraz - tzv. test pattern genrator, ze kterého jsem musel vyexportovat hardwarový `.xsa` sobor. Zde skončila moje práce s Vivadem. Je ale možné, že ho následně budu nucen použít pro konfiguraci.  

Díky hw konfiguraci jsem mohl již [vybuldit PetaLinuxl image](https://www.instructables.com/Getting-Started-With-PetaLinux/), který jsem nahrál na [vhodně připravenou](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842385/How+to+format+SD+card+for+SD+boot) SD kartu. Po té jsem mohl již desku nabootovat.

*Zde jsem dostal postranní úkol postarat se o bootování z eMMC paměti - není součástí ročníkové práce.* 

Nyní mě čeká příprava QtCreator, vytvoření prázdného projektu a zajitšení odeslání buildu přes SSH.

## QT projekt

Je potřeba zobrazit výstup z kamery - použití GStreamer 

Je potřeba být schopen s kamerou komunikovat přes VISCA protokol

