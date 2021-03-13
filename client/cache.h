
/*
    Caching file system proxy
    Copyright (C) 2004  Miklos Szeredi <miklos@szeredi.hu>
    This program can be distributed under the terms of the GNU GPL.
    See the file LICENSE.
*/
#define FUSE_USE_VERSION 31
#include <fuse.h>
#include <fuse_opt.h>
#define IDMAP_DEFAULT "user"
#define PACKAGE_VERSION "0.0.1"


struct fuse_operations *cache_wrap(struct fuse_operations *oper);
int cache_parse_options(struct fuse_args *args);
void cache_add_attr(const char *path, const struct stat *stbuf, uint64_t wrctr);
void cache_invalidate(const char *path);
uint64_t cache_get_write_ctr(void);