# qvm-mount

A tool to mount directories accross Qubes VMs.

```
Usage: qvm-mount <qube-name>:<remote-path> <local-path>

Mounts remote directory after you confirm in dom0.
```

## Installation

Compile it yourself. 

First install the required tools (assuming a debian or ubuntu machine or vm):
```
sudo apt install build-essential ninja-build python3-pip libfuse3-dev libglib2.0-dev fuse3 autoconf libssl-dev gdb
pip3 install --user meson
```

Then compile and install
```
mkdir -p builddir
cd builddir
meson compile
meson install
```

## Testing (local)
```
mkfifo sftp-in
mkfifo sftp-out
mkdir source
mkdir target
# root privileges for chroot
sudo ./builddir/server/server -l DEBUG3 -e -D /tmp < sftp-in > sftp-out
./builddir/client/qvmfs-client ./target > ./sftp-in < ./sftp-out
```

## Debugging (local)
```
mkfifo sftp-in
mkfifo sftp-out
mkdir source
mkdir target
gdb ./builddir/server/server
(gdb) run -l DEBUG3 -e -D /tmp < sftp-in > sftp-out
./builddir/client/qvmfs-client -o debug ./target > ./sftp-in < ./sftp-out
```

## Debugging (remote)
```
sudo cp ln -s rpc/test.Mount /etc/qubes-rpc/ # on target machine
mkfifo sftp-in
mkfifo sftp-out
mkdir target
./builddir/client/qvmfs-client -o debug ./target > ./sftp-in < ./sftp-out
qrexec-client-vm <server> test.Mount+/home/user <sftp-in >sftp-out
```


## License

Mixed due to lots of copied code. See files

## Inner Workings

TODO:
Client: import sftp over stdout/stdin as fuse (basically lobotomized sshfs)
Server: export sftp over stdout/stdin (sftp without the ssh and networking part)