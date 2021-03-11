project('qvm-mount', 'c')
executable('server', 'server.c')
fusedep = dependency('fuse3')
executable('client', 'client.c', dependency: fusedep)