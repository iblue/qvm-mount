# qvm-mount

A tool to mount remote directorys in your local Qubes VM.

```
Usage: qvm-mount <remote-vm>:<remote-path> <local-path>

Mounts remote directory if you confirm in dom0.
```

## Installation

Compile it yourself. First install the required tools:
```
sudo apt install build-essential ninja-build python3-pip libfuse3-dev libglib2.0-dev fuse3
pip3 install --user meson
```

Then compile:
```
cd builddir
meson compile
```


## License

GPL2

## Inner Workings

TODO