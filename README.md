# qvm-mount

A tool to mount directories accross Qubes VMs.

## Installation

Compile it yourself. 

First install the required tools:

### Debian/Ubuntu:
```
sudo apt install build-essential ninja-build python3-pip libfuse3-dev libglib2.0-dev fuse3 # Debian 10
sudo pip3 install meson
```

### Fedora
```
sudo dnf install gcc ninja-build python3-pip fuse3-devel glib2-devel fuse3
sudo pip3 install meson
```

Then compile and install
```
meson builddir
cd builddir
meson configure --prefix /usr
meson compile
sudo meson install
```

## Usage

```
Usage: qvm-mount [-R] <qube-name>:<remote-path> <local-path>

    -R       Mount remote-path readonly

Mounts remote directory after you confirm in dom0.
```

## License

Mixed due to lots of copied code. See LICENSE.

## Inner Workings

We use SFTP over Qrexec. [Qrexec](https://www.qubes-os.org/doc/qrexec/) is a kind of RPC mechanism, where you can connect the stdin and stdout of commands across Qubes. SFTP is a protocol usually used on top of SSH to transfer files. The encryption and authentication part is handled by SSH, SFTP is just a type of binary file transfer protocol.

There are two Qubes involved. A client and a server. The server is an SFTP server, just that it communicates to a socket instead of the network. This socket is connected via qrexec to the client machine, where the client translates [FUSE](https://github.com/libfuse/libfuse) requests to SFTP requests.

## FAQ

### Is this production-safe?

Probably not.

### Is it secure?

Probably not.

## Debugging and Testing

### Testing (local)
```
mkfifo sftp-in
mkfifo sftp-out
mkdir source
mkdir target
# root privileges for chroot
sudo ./builddir/server/qvmfs-server -l DEBUG3 -e ./source < sftp-in > sftp-out
./builddir/client/qvmfs-client ./target > ./sftp-in < ./sftp-out
```

### Debugging (local)
```
mkfifo sftp-in
mkfifo sftp-out
mkdir target
gdb ./builddir/server/qvmfs-server
(gdb) run -l DEBUG3 -e ./source < sftp-in > sftp-out
./builddir/client/qvmfs-client -o debug ./target > ./sftp-in < ./sftp-out
```

### Debugging (remote)

You need to modify the `/etc/qubes-rpc/qubes.MountReadWrite` to point to your testing binary. But there is probably no sense in that, since qrexec should work the same as a local fifo.
