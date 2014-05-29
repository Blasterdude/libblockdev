#include <dlfcn.h>
#include "blockdev.h"
#include "plugins.h"

#include "plugin_apis/lvm.c"
#include "plugin_apis/swap.c"

/**
 * SECTION: libblockdev
 * @short_description: a library for doing low-level operations with block devices
 * @title: libblockdev library
 * @include: blockdev.h
 *
 */

typedef struct BDPluginStatus {
    BDPluginSpec spec;
    gboolean loaded;
} BDPluginStatus;

/* KEEP THE ORDERING OF THESE ARRAYS MATCHING THE BDPluginName ENUM! */
static BDPluginStatus plugins[BD_PLUGIN_UNDEF] = {
    {{BD_PLUGIN_LVM, "libbd_lvm.so"}, FALSE},
    {{BD_PLUGIN_SWAP, "libbd_swap.so"}, FALSE},
};
static gchar* plugin_names[BD_PLUGIN_UNDEF] = {
    "lvm", "swap"
};

void set_plugin_so_name (BDPlugin name, gchar *so_name) {
    plugins[name].spec.so_name = so_name;
}

/**
 * bd_init:
 * @force_plugins: (allow-none): null-terminated list of plugins that should be loaded (even if
 *                 other plugins for the same technologies are found)
 *
 * Returns: whether the library was successfully initialized or not
 */
gboolean bd_init (BDPluginSpec *force_plugins) {
    guint8 i = 0;
    gboolean all_loaded = TRUE;

    if (force_plugins)
        for (i=0; force_plugins + i; i++)
            set_plugin_so_name(force_plugins[i].name, force_plugins[i].so_name);

    plugins[BD_PLUGIN_LVM].loaded = load_lvm_from_plugin(plugins[BD_PLUGIN_LVM].spec.so_name);
    plugins[BD_PLUGIN_SWAP].loaded = load_swap_from_plugin(plugins[BD_PLUGIN_SWAP].spec.so_name);

    for (i=0; (i < BD_PLUGIN_UNDEF) && all_loaded; i++)
        all_loaded = all_loaded && plugins[i].loaded;

    return all_loaded;
}

/**
 * bd_get_available_plugin_names:
 *
 * Returns: (transfer container) (array zero-terminated=1): an array of string
 * names of plugins that are available
 */
gchar** bd_get_available_plugin_names () {
    guint8 i = 0;
    guint8 num_loaded = 0;
    guint8 next = 0;

    for (i=0; i < BD_PLUGIN_UNDEF; i++)
        if (plugins[i].loaded)
            num_loaded++;

    gchar **ret_plugin_names = g_new (gchar*, num_loaded + 1);
    for (i=0; i < BD_PLUGIN_UNDEF; i++)
        if (plugins[i].loaded) {
            ret_plugin_names[next] = plugin_names[i];
            next++;
        }
    ret_plugin_names[next] = NULL;

    return ret_plugin_names;
}

/**
 * bd_is_plugin_available:
 * @plugin: the queried plugin
 *
 * Returns: whether the given plugin is available or not
 */
gboolean bd_is_plugin_available (BDPlugin plugin) {
    if (plugin < BD_PLUGIN_UNDEF)
        return plugins[plugin].loaded;
    else
        return FALSE;
}

#ifdef TESTING_LIB
#include "test_blockdev.c"
#endif