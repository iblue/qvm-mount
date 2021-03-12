# qvm-mount

A tool to mount remote directorys in your local Qubes VM.

```
Usage: qvm-mount <remote-vm>:<remote-path> <local-path>

Mounts remote directory if you confirm in dom0.
```

## Installation

Compile it yourself. First install the required tools:
```
sudo apt install build-essential ninja-build python3-pip libfuse3-dev libglib2.0-dev fuse3 autoconf libssl-dev
pip3 install --user meson
```

Then compile:
```
cd builddir
meson compile # Client
cd ..
cd openssh-portable-V_8_5_P1
autoreconf
./configure
make
```

## Debugging
```
mkfifo sftp-in
mkfifo sftp-out
./openssh-portable-V_8_5_P1/sftp-server -d . < sftp-in > sftp-out
./builddir/client foo:bar ./target > ../sftp-in < ../sftp-out
```

## License

Mixed due to lots of copied code. See files

## Inner Workings

TODO:
Client: import sftp over stdout/stdin as fuse (basically lobotomized sshfs)
Server: export sftp over stdout/stdin (sftp without the ssh and networking part)