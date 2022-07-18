# Development notes

*Zde si budu psát předběžné poznámky k vývoji*

### První část - uložení generovaného obrazu na SD kartu

V tuto chvíli jsem zprovoznil uložení jako jpg na SD kartu z příkazové řádky

```bash
media-ctl -d /dev/media0 -V '5:0 [fmt:RBG888_1X24/1024x768@1/60 field:none]'
v4l2-ctl -d /dev/video0 --set-fmt-video=width=1024,height=768,pixelformat='RGB3'

yavta --no-query -w '0x009e0901 30' /dev/v4l-subdev0
yavta --no-query -w '0x009e0902 304' /dev/v4l-subdev0
yavta --no-query -w '0x009f0903 0' /dev/v4l-subdev0
yavta --no-query -w '0x0098c912 1' /dev/v4l-subdev0

gst-launch-1.0 v4l2src io-mode=dmabuf ! video/x-raw, format=I420, width=1024, height=768, framerate=1/5, format=RGB ! identity sync=true ! jpegenc ! multifilesink location="img_%0 6.jpg"
```

Jeden ze vzniklých obrázků:

<img src="/home/vesmil/vesely/README.assets/img_0x1.jpg" style="zoom:50%;" />

*Nyní toto musím "přepsat" do C++*

