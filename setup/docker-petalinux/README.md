# Dockerized petalinux

## Prerequisities

Install `docker` and `docker-compose` tools. On ubuntu, this is done by running command
```bash
sudo apt-get install docker docker-compose
```

## Build

Download appropriate petalinux installer from [Xilinx's website](https://www.xilinx.com/support/download.html) (behind loginwall) into the `version/files` (e.g. `./2021.1/files`) directory.
Next, run the `docker-compose build` command from the directory containing `docker-compose.yml` file (e.g. `./2021.1/`).
Alternatively, you can skip the build and just run `docker-compose up` as in the next section (container will build itself automatically).

### Possible issues

#### `ERROR: Couldn't connect to Docker daemon at http+docker://localunixsocket - is it running?`

Solutions:
 - Make sure the docker daemon is running. On ubuntu run `sudo systemctl start docker` to start the docker daemon. To start daemon automatically on boot, run `sudo systemctl enable docker`.
 - Try running `docker` command as root. Protip: you can add your user into `docker` group in order to run `docker` as non-root (i.e. to not use sudo every time).

## Run

Run `docker-compose up` to start the container.
You can use `-d` flag to run it in the background.
To attach to the terminal, run `docker attach petalinux-2021.1` (obviously replace the version with yours).
To stop the container, run `docker-compose down`.

## Mount directory

In order to access files from your container, you need to specify a path to your workspace.
Open appropriate `docker-compose.yml` file and just change the last line in *volumes* section.

## Troubleshooting

### Wayland

In case you are running wayland (Ubuntu), please execute following command to enable GUI output.
```bash
xhost +si:localuser:root
```
