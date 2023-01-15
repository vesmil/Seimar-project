1. Zapnout
2. Zjistit IP
3. Znovu připojit USB

```
modetest -D a0000000.v_mix -s 40@38:3840x2160-60@BG24
```

```
gst-launch-1.0 videotestsrc ! video/x-raw, width=3840, height=2160, framerate=60/1 ! queue ! kmssink bus-id="a0000000.v_mix" plane-id=37 fullscreen-overlay=false sync=false
```

```
modetest -D a0000000.v_mix -P 35@38:640x480+500+200@RG24
```

```
export QT_QPA_PLATFORM=eglfs
export QT_QPA_EGLFS_INTEGRATION=none
```

4. Done
