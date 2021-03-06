Features
=========

The libblockdev library will be state-less from the device perspective. There
may (and probably will) be some library-wide as well as technology-wide
configuration (e.g. default configuration for the LVM functions), but the
library won't keep state of the devices. So if for example the lvcreate()
function is called with a non-existing or full VG as a parameter, the function
will fail when trying to create the LV not in any pre-processing check.


partitions
-----------

:supported technologies:
   MBR, GPT, partition manipulation on partitionable devices

:functions:
   * mklabel [DONE]
   * create_part [DONE]
   * resize_part
   * remove_part [DONE]


filesystems
------------

:supported technologies:
   * DONE: ext4, xfs
   * IN PROGRESS: vfat
   * TODO?  ext2, ext3

:functions:
   * make_FSTYPE
   * resize_FSTYPE
   * check_FSTYPE
   * repair_FSTYPE
   * change_label_FSTYPE
   * snapshot_FSTYPE

   * wipefs [DONE]
   * generic_resize


LVM
----

:supported technologies:
   "plain LVM", LVM Thin Provisioning

:TODO:
   * read-only locking and default config

:functions:
   * get_global_config [DONE]
   * set_global_config [DONE]
   * get_possible_pe_sizes [DONE]
   * is_supported_pe_size [DONE]
   * get_max_lv_size [DONE]
   * round_size_to_pe [DONE]
   * get_lv_physical_size [DONE]
   * get_thpool_padding [DONE]
   * is_valid_thpool_metadata_size [DONE]
   * is_valid_thpool_chunk_size [DONE]

   * pvcreate [DONE]
   * pvresize [DONE]
   * pvremove [DONE]
   * pvmove [DONE]
   * pvscan [DONE]
   * pvinfo [DONE]
   * pvs [DONE]

   * vgcreate [DONE]
   * vgextend [DONE]
   * vgremove [DONE]
   * vgactivate [DONE]
   * vgdeactivate [DONE]
   * vgreduce [DONE]
   * vginfo [DONE]
   * vgs [DONE]

   * lvorigin [DONE]
   * lvcreate [DONE]
   * lvremove [DONE]
   * lvresize [DONE]
   * lvactivate [DONE]
   * lvdeactivate [DONE]
   * lvsnapshotcreate [DONE]
   * lvsnapshotmerge [DONE]
   * lvinfo [DONE]
   * lvs [DONE]

   * thpoolcreate [DONE]
   * thlvcreate [DONE]
   * thlvpoolname [DONE]
   * thsnapshotcreate [DONE]

   * lvm_cache_get_default_md_size [DONE]
   * lvm_cache_get_mode_str [DONE]
   * lvm_cache_get_mode_from_str [DONE]
   * lvm_cache_create_pool [DONE]
   * lvm_cache_attach [DONE]
   * lvm_cache_detach [DONE]
   * lvm_cache_create_cached_lv [DONE]
   * lvm_cache_pool_name [DONE]
   * lvm_cache_stats [DONE]

BTRFS
------

:supported technologies:
   btrfs as both filesystem and multi-device volume, subvolumes, snapshots

:functions:
   * create_volume [DONE]
   * add_device [DONE]
   * remove_device [DONE]
   * list_devices [DONE]
   * create_subvolume [DONE]
   * delete_subvolume [DONE]
   * list_subvolumes [DONE]
   * get_default_subvolume [DONE]
   * set_default_subvolume [DONE]
   * create_snapshot [DONE]
   * filesystem_info [DONE]
   * mkfs [DONE]
   * resize [DONE]
   * check [DONE]
   * repair [DONE]
   * change_label [DONE]


SWAP
-----

:supported technologies:
   swap partitions/LVs, swap files

:functions:
   * mkswap [DONE]
   * swapon [DONE]
   * swapoff [DONE]
   * swapstatus [DONE]


MDRAID
-------

:supported technologies:
   all RAID levels supported by the MD RAID

:functions:
   * get_superblock_size [DONE]
   * create [DONE]
   * destroy [DONE]
   * activate [DONE]
   * deactivate [DONE]
   * run [NEEDS_TEST]
   * nominate [DONE]
   * denominate [DONE]
   * add [DONE]
   * remove [DONE]
   * examine [DONE]
   * canonicalize_uuid [DONE]
   * get_md_uuid [DONE]
   * detail [DONE]
   * node_from_name [DONE]
   * name_from_node [DONE]


CRYPTO/LUKS
------------

:supported technologies:
   only LUKS encrypted devices

:functions:
   * generate_backup_passphrase [DONE]
   * device_is_luks [DONE]
   * luks_uuid [DONE]
   * luks_status [DONE]
   * luks_format [DONE]
   * luks_open [DONE]
   * luks_close [DONE]
   * luks_add_key [DONE]
   * luks_remove_key [DONE]
   * luks_change_key [DONE]
   * luks_resize [DONE]
   * escrow_device [DONE]


MULTIPATH
----------

:supported technologies:
   just very basic functionality

:functions:
   * flush_mpaths [DONE]
   * device_is_mpath_member [DONE]
   * set_friendly_names [DONE]


LOOP
-----

:supported technologies:
   basic operations with loop devices

:functions:
   * get_backing_file [DONE]
   * get_loop_name [DONE]
   * loop_setup [DONE]
   * loop_teardown [DONE]


DEVICE MAPPER
--------------

:supported technologies:
   basic operations with raw device mapper and DM RAID sets

:functions:
   * create_linear [DONE]
   * remove [DONE]
   * node_from_name [DONE]
   * name_from_node [DONE]
   * map_exists [DONE]
   * get_member_raid_sets [DONE]
   * activate_raid_set [DONE]
   * deactivate_raid_set [DONE]
   * get_raid_set_type [DONE]


s390
-----

:supported technologies:
   DASD, zFCP

:functions:
   * s390_dasd_format [DONE]
   * s390_dasd_needs_format [DONE]
   * s390_dasd_online [DONE]
   * s390_dasd_is_ldl [DONE]
   * s390_sanitize_dev_input [DONE]
   * s390_zfcp_sanitize_wwpn_input [DONE]
   * s390_zfcp_sanitize_lun_input [DONE]
   * s390_zfcp_online [DONE]
   * s390_zfcp_scsi_offline [DONE]
   * s390_zfcp_offline [DONE]


KBD (Kernel Block Devices)
---------------------------

:supported technologies:
   bcache, zram

:functions:
   * bcache_create [DONE]
   * bcache_destroy [DONE]
   * bcache_attach [DONE]
   * bcache_detach [DONE]
   * bcache_status [DONE]
   * bcache_set_mode [DONE]
   * bcache_get_mode [DONE]
   * bcache_get_backing_device [DONE]
   * bcache_get_cache_device [DONE]

   * zram_create_devices [DONE]
   * zram_destroy_devices [DONE]
   * zram_get_stats [DONE]


utils
------

Library (not a plugin) providing utility functions usable for multiple plugins
and any third-party code.

:functions:
   * exec_and_report_error [DONE]
   * exec_and_capture_output [DONE]
   * size_human_readable [DONE]
   * size_from_spec [DONE]
   * init_logging [DONE]
   * version_cmp [DONE]
   * check_util_version [DONE]
