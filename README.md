# qvm-mount

A tool to mount remote directorys in your local Qubes VM.

```
Usage: qvm-mount <remote-vm>:<remote-path> <local-path>

Mounts remote directory if you confirm in dom0.
```

## Installation

Compile it yourself. First install the required tools:
```
sudo apt install build-essential ninja-build python3-pip libfuse3-dev libglib2.0-dev fuse3 autoconf libssl-dev gdb
pip3 install --user meson
```

Then compile:
```
cd builddir
meson compile # Client
cd ..
cd openssh-portable-V_8_5_P1
autoreconf
./configure CFLAGS='-O0 -ggdb'
make
```

## Testing (local)
```
mkfifo sftp-in
mkfifo sftp-out
mkdir source
mkdir target
# root privileges for chroot
sudo ./openssh-portable-V_8_5_P1/sftp-server -l DEBUG3 -e -D source < sftp-in > sftp-out
./builddir/client -o passive -o debug -o dir_cache=no localhost:/home/user/git/qvm-mount/source ./target > ./sftp-in < ./sftp-out
```

## Debugging (local)
```
mkfifo sftp-in
mkfifo sftp-out
mkdir source
mkdir target
gdb ./openssh-portable-V_8_5_P1/sftp-server 
(gdb) run -D /tmp < sftp-in > sftp-out
./builddir/client -o passive -o debug -o dir_cache=no localhost:/ ./target > ./sftp-in < ./sftp-out
```

## Debugging (remote)
```
sudo cp ln -s rpc/test.Mount /etc/qubes-rpc/ # on target machine
mkfifo sftp-in
mkfifo sftp-out
mkdir target
./builddir/client -o passive -o debug -o dir_cache=no localhost:/ ./target > ./sftp-in < ./sftp-out
qrexec-client-vm <server> test.Mount+/home/user <sftp-in >sftp-out
```


## License

Mixed due to lots of copied code. See files

## Inner Workings

TODO:
Client: import sftp over stdout/stdin as fuse (basically lobotomized sshfs)
Server: export sftp over stdout/stdin (sftp without the ssh and networking part)