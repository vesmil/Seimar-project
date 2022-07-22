# Příprava

*Kvůli časové náročnosti přípravy se nejedná úplně o step by step příručku. Snažil jsem se ale aby žádné podstatné kroky nebyly vynechány.*

**Potřebné vybavení:**

* Nosná deska (v mém případě Trenz TE0701)
* Modul Trenz TE0820
* SD karta, mini USB kabel, Linux PC

## Příprava PetaLinux

V Docker kontejneru spustíme [PetaLinux 2021.2](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools.html) - příručka ve složce `docker-petalinux`,

> Já musel v Dockreu spustit i VIvado, protože jsem potřeboval generovat hw konfiguraci (`.xsa`), tu jsem ale již přidal do repositáře spolu se základem PetaLinuxu (který se běžně musí vytvářet - viz např. [tento návod](https://www.instructables.com/Getting-Started-With-PetaLinux/)),

Zároveň je potřeba zpřístupnit pro PetaLinux složku `petalinux-tpg-trenz`.

Když toto máme připravené, tak ve výše zmíněné složce provedeme následující řadu příkazů:

```bash
petalinux-config --get-hw-description=hardware/
```

, to nám načte konfiguraci pro programovatelné hradlové pole.

Následně nastavíme group packages pomocí (v současné chvíli stačí přidat GStreamer a QT):

```bash
petalinux-config -c rootfs
```

PetaLinux vybuldit:

```bash
petalinux-build
```

A zabalit:

```bash
petalinux-package --boot --fsbl images/linux/zynqmp_fsbl.elf --pmufw images/linux/pmufw.elf --atf images/linux/bl31.elf --u-boot images/linux/u-boot.elf --fpga images/linux/system.bit --force
```

Výsledné soubory `boot.scr`, `BOOT.bin` a `image.ub` je potřeba nahrát do boot partition na [vhodně připravenou](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842385/How+to+format+SD+card+for+SD+boot) SD kartu, do root partiotion rozbalit `rootfs.ext4` a po té desku jenom zapojit,

> Zde jsem dostal postranní úkol postarat se o bootování z QSPI flash paměti (pravděpodobně to není součástí ročníkové práce, ale svoji desku tedy zvládnu nabootovat bez SD karty). V podstatě jde o vytvoření ext4 filesystému na eMMC z nabootovaného PetaLinux, změna nastavení v konfiguraci před buildem a úprava boot flagů a nahrání boot partition do QSPI díky TFTP serveru.

Na desku se lze připopojit pomocí `minicom`:

```bash
minicom -D /dev/ttyUSB1 -b 115200
```

, kde je ideální vypnout software a hardware flow control (CTRL-A -> o -> Serial Port Setup -> g, f).

## Příprava QT

Musíme spustit Dockerizovaný PetaLinux a opět pomocí `petalinux-config -c rootfs` přidat ke QT možnost `populate_sdk_qt5` a vybuildit pomocí `petalinux-build -s`, abychom získali vhodné SDK. To ale ještě musíme rozbalit `petalinux-package --sysroot`.

Pokud bychom chtěli kompilovat, tak už můžeme tak, že použijeme `source` na vygenerované prostředí:

```
. ./images/linux/sdk/environment-setup-aarch64-xilinx-linux
```

Protože ale chceme pracovat s QtCreator, tak spustíme `sdk.sh`, který nám prostředí vytvoří ve složce `opt` (to je především abych měl snazší přípravu QtCreatoru jako takového).

Dále jsem automatizoval přidávání kitů do QT na Linuxu pomocí skriptu `Import.py`, který stačí spustit s argumentem `zynq.xml` (při zavřeném QtCreatoru).

Následně QtCreator budeme muset otevírat trochu nemotorně tímto stylem:

```bash
. /opt/petalinux/2021.2/environment-setup-cortexa72-cortexa53-xilinx-linux
QtCrator
```

A po té v devices ještě vhodně nastavit IP adresu po té, co v minicomu zadáme `ip a`,

## Grafická akcelerace

Jako grafický backend používáme fbdev. K tomu je třeba přidat `libmali-xlnx` driver do rootfs. Následně v souboru `./project-spec/meta-user/conf/petalinuxbsp.conf` tento backend specifikujeme (přidáme na konec souboru řádek).

```
MALI_BACKEND_DEFAULT = "fbdev"
```

Aby se nám spouštěly qt aplikace s GPU akcelerací, je potřeba nastavit proměnné `QT_QPA_EGLFS_INTEGRATION` a `QT_QPA_PLATFORM`. Abychom tento proces zautomatizovali, vytvoříme nový recept `./project-spec/meta-user/recipes-core/base-files/base-files_%.bbappend`, který tyto proměnné zapíše do `.profile`.

```
do_install_append () {
        cat >> ${D}${sysconfdir}/skel/.profile <<EOF
export QT_QPA_EGLFS_INTEGRATION=none
export QT_QPA_PLATFORM=eglfs
EOF
}
```

Případně můžeme přidat v QT Creator do build environment následující:

```bash
QT_QPA_PLATFORM=eglfs
QT_QPA_EGLFS_INTEGRATION=none
```

