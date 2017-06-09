#ifndef AUDITFS_H
#define AUDITFS_H

#include <linux/types.h>
#include <linux/fs.h>

#define KMOD_AUTHOR	"Matt Monsour <mzmonsour@gmail.com>"
#define KMOD_DESC	"Auditfs: A simple, auditing filesystem"
#define KMOD_LICENSE	"GPL"

#define AUDITFS_NAME	"auditfs"
#define AUDITFS_MAGIC	0x100200FF

/* No. of reserved blocks in the super section (before groups) */
#define AUDITFS_SUPER_RESERVED	16
/* No. of reserved blocks per group */
#define AUDITFS_BLKGRP_RESERVED	4
/* No. of reserved inodes */
#define AUDITFS_INODE_RESERVED	16
/* Inode size in bytes */
#define AUDITFS_INODE_SIZE	256
/* Inode of the root directory */
#define AUDITFS_ROOT_INODE	1
/* No. of direct inode pointers */
#define AUDITFS_IPTR_DIRECT	12

#define AUDITFS_LOG_OFF		0 /* Disable logging */
#define AUDITFS_LOG_NEVER	0xFFFF /* File may never be logged */
#define AUDITFS_LOG_ACCESS	0x0001 /* Log file accesses */
#define AUDITFS_LOG_MODIFY	0x0002 /* Log file modifications */
#define AUDITFS_LOG_META	0x0004 /* Log file metadata changes */

/*
 * In-memory auditfs superblock info
 */
struct auditfs_sb_info {
	unsigned long			s_blkgrp_size; /* Block group size in bytes */
	unsigned long			s_blkgrp_blocks; /* Block group size in blocks */
	unsigned long			s_blkgrp_inodes; /* No. of inodes per block group */
	unsigned long			s_blkgrp_ino_blocks; /* No. of inode blocks per group */
	unsigned long			s_blkgrp_data_blocks; /* No. of data blocks per group */
	unsigned long			s_inodes_per_block; /* No. of inodes per block */
	struct auditfs_super_block	*s_asb;
};

/*
 * Disk representation of auditfs superblock
 */
struct auditfs_super_block {
	__le32	s_magic; /* Magic bytes */
	__le32	s_block_size; /* FS block size */
	__le64	s_block_count; /* Total block count */
	__le32	s_total_inodes; /* Total inode count */
	__le32	s_total_data; /* Total data block count */
	__le32	s_free_inodes; /* Free inode count */
	__le32	s_free_data; /* Free data block count */
};

/*
 * Inode pointer structure
 */
struct auditfs_iptr {
	__le64	p_direct[AUDITFS_IPTR_DIRECT]; /* Direct inode pointers */
	__le64	p_single; /* Singly indirect inode pointer */
	__le64	p_double; /* Doubly indirect inode pointer */
	__le64	p_triple; /* Triply indirect inode pointer */
};

/*
 * Auditfs extended inode
 */
struct auditfs_inode_info {
	struct inode		vfs_inode; /* Base VFS inode data */
	struct auditfs_iptr	i_ptr; /* Inode ptr structure */
	unsigned int		i_log_mode; /* Logging mode settings */
	unsigned long		i_log_ino; /* Log file inode */
	unsigned long long	i_log_max; /* Log file max size in bytes */
	unsigned long long	i_log_start; /* Index of first log record */
	struct timespec		i_otime; /* Creation time */
};

/*
 * Disk representation of auditfs inode
 */
struct auditfs_inode {
	__le64			i_size; /* Files: size in bytes, Directories: number of entries */
	__le16			i_mode; /* File mode (rwx + file type) */
	__le16			i_uid; /* Owning unix uid */
	__le16			i_gid; /* Owning unix gid */
	__le16			i_links; /* Hard link counter */
	__le64			i_atime; /* Access time */
	__le64			i_mtime; /* Modification time */
	__le64			i_ctime; /* Change time */
	__le64			i_otime; /* Creation time */
	__le16			i_log_mode; /* Logging mode */
	__le16			i_reserved1;
	__le32			i_reserved2;
	__le64			i_log_ino; /* Log file inode */
	__le64			i_log_max; /* Maximum log file size (0 unlimited) */
	__le64			i_log_start; /* Index of first log record */
	struct auditfs_iptr	i_ptr; /* Inode pointer structure */
};

/*
 * Retrieve the auditfs superblock from the VFS superblock
 */
static inline struct auditfs_sb_info *AUDITFS_SB(struct super_block *sb)
{
	return (struct auditfs_sb_info *)sb->s_fs_info;
}

/*
 * Retrieve the auditfs inode from a VFS inode
 */
static inline struct auditfs_inode_info *AUDITFS_I(struct inode *inode) {
	return container_of(inode, struct auditfs_inode_info, vfs_inode);
}

#endif
