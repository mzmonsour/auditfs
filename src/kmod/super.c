/*
 * Copyright (C) 2017 Matt Monsour
 * Licensed under GPLv3
 * Refer to LICENSE file for full GPL text
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

#include "auditfs.h"

static struct dentry *auditfs_mount(struct file_system_type *fs_type,
				    int flags, const char *dev_name,
				    void *data)
{
	return NULL; // TODO
}

static struct file_system_type auditfs_type = {
	.owner		= THIS_MODULE,
	.name		= AUDITFS_NAME,
	.mount		= auditfs_mount,
	.kill_sb	= kill_block_super,
	.fs_flags	= FS_REQUIRES_DEV
};

static int __init auditfs_init(void)
{
	return register_filesystem(&auditfs_type);
}

static void __exit auditfs_exit(void)
{
	unregister_filesystem(&auditfs_type);
}

module_init(auditfs_init);
module_exit(auditfs_exit);

MODULE_AUTHOR(KMOD_AUTHOR);
MODULE_DESCRIPTION(KMOD_DESC);
MODULE_LICENSE(KMOD_LICENSE);
