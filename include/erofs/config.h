/* SPDX-License-Identifier: GPL-2.0+ OR Apache-2.0 */
/*
 * Copyright (C) 2018-2019 HUAWEI, Inc.
 *             http://www.huawei.com/
 * Created by Li Guifu <bluce.liguifu@huawei.com>
 */
#ifndef __EROFS_CONFIG_H
#define __EROFS_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "defs.h"
#include "err.h"


enum {
	FORCE_INODE_COMPACT = 1,
	FORCE_INODE_EXTENDED,
};

enum {
	FORCE_INODE_BLOCK_MAP = 1,
	FORCE_INODE_CHUNK_INDEXES,
};

enum {
	TIMESTAMP_NONE,
	TIMESTAMP_FIXED,
	TIMESTAMP_CLAMPING,
};

#define EROFS_MAX_COMPR_CFGS		64

struct erofs_configure {
	const char *c_version;
	int c_dbg_lvl;
	bool c_dry_run;
	bool c_legacy_compress;
#ifndef NDEBUG
	bool c_random_pclusterblks;
	bool c_random_algorithms;
#endif
	char c_timeinherit;
	char c_chunkbits;
	bool c_noinline_data;
	bool c_ztailpacking;
	bool c_fragments;
	bool c_all_fragments;
	bool c_dedupe;
	bool c_ignore_mtime;
	bool c_showprogress;
	bool c_extra_ea_name_prefixes;

#ifdef HAVE_LIBSELINUX
	struct selabel_handle *sehnd;
#endif
	/* related arguments for mkfs.erofs */
	char *c_img_path;
	char *c_src_path;
	char *c_blobdev_path;
	char *c_compress_hints_file;
	char *c_compr_alg[EROFS_MAX_COMPR_CFGS];
	int c_compr_level[EROFS_MAX_COMPR_CFGS];
	char c_force_inodeversion;
	char c_force_chunkformat;
	/* < 0, xattr disabled and INT_MAX, always use inline xattrs */
	int c_inline_xattr_tolerance;

	u32 c_pclusterblks_max, c_pclusterblks_def, c_pclusterblks_packed;
	u32 c_max_decompressed_extent_bytes;
	u32 c_dict_size;
	u64 c_unix_timestamp;
	u32 c_uid, c_gid;
	const char *mount_point;
	long long c_uid_offset, c_gid_offset;
#ifdef WITH_ANDROID
	char *target_out_path;
	char *fs_config_file;
	char *block_list_file;
#endif

	/* offset when reading multi partition images */
	u64 c_offset;
};

extern struct erofs_configure cfg;

void erofs_init_configure(void);
void erofs_show_config(void);
void erofs_exit_configure(void);

void erofs_set_fs_root(const char *rootdir);
const char *erofs_fspath(const char *fullpath);

#ifdef HAVE_LIBSELINUX
int erofs_selabel_open(const char *file_contexts);
#else
static inline int erofs_selabel_open(const char *file_contexts)
{
	return -EINVAL;
}
#endif

void erofs_update_progressinfo(const char *fmt, ...);
char *erofs_trim_for_progressinfo(const char *str, int placeholder);

#ifdef __cplusplus
}
#endif

#endif
