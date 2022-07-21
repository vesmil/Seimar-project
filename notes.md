# Development notes

*Zde si budu psát předběžné poznámky k vývoji*

## 1. část - uložení generovaného obrazu na SD kartu

### Setup

Před použitím gstreameru je nutný setup pro video for linux. 

```bash
media-ctl -d /dev/media0 -V '5:0 [fmt:RBG888_1X24/1024x768@1/60 field:none]'
v4l2-ctl -d /dev/video0 --set-fmt-video=width=1024,height=768,pixelformat='RGB3'

yavta --no-query -w '0x009e0901 30' /dev/v4l-subdev0
yavta --no-query -w '0x009e0902 304' /dev/v4l-subdev0
yavta --no-query -w '0x009f0903 0' /dev/v4l-subdev0
yavta --no-query -w '0x0098c912 1' /dev/v4l-subdev0
```

### Příkazová řádka

V tuto chvíli jsem zprovoznil uložení jako na SD kartu z příkazové řádky

```bash
gst-launch-1.0 v4l2src io-mode=dmabuf ! video/x-raw, width=1024, height=768, framerate=60/1, format=RGB !  filesink location=/media/sd-mmcblk1p2/video-raw-file
```

### C++

Pouižtí je ve výsledku velmi podobné, musím vytvořit jednotlivé elementy a ty dát do pipeline.

Navíc je tedy potřeba řešit změna stavu na přehrávání - je to blokující funkce. V současné chvíli, ale stav změním z `PLAYING` na `PAUSED` a následně `READY` v destroktoru.

Dále se musím postarat o vyjímky a spárvnou destrukci.

### RAW náhled

Pro spuštění nebo enkódování vzniklého videa můžu využít následující příkazy:

```bash
gst-launch-1.0 filesrc location=video-raw-file ! rawvideoparse width=1024 height=768 format=16 framerate=60/1 ! autovideoconvert ! autovideosink

gst-launch-1.0 filesrc location=video-raw-file ! rawvideoparse width=1024 height=768 format=16 framerate=60/1 ! autovideoconvert ! x264enc ! mp4mux ! filesink location=tpg.mp4
```

Výsledek:

<img src="README.assets/tpg.gif" style="zoom:50%;" />

## 2. část - zobrazení

Potřeba přidat další GStreamer pipeline...

Využití QML...

## 3. Část - menu



## 4. část - ovládání kamery

VISCA protokol
