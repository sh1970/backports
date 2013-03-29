--- a/net/mac80211/main.c
+++ b/net/mac80211/main.c
@@ -71,7 +71,11 @@
 	spin_lock_bh(&local->filter_lock);
 	changed_flags = local->filter_flags ^ new_flags;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	mc = drv_prepare_multicast(local, &local->mc_list);
+#else
+	mc = drv_prepare_multicast(local, local->mc_count, local->mc_list);
+#endif
 	spin_unlock_bh(&local->filter_lock);
 
 	/* be a bit nasty */
@@ -592,9 +596,11 @@
 	wiphy->vht_capa_mod_mask = &mac80211_vht_capa_mod_mask;
 
 	INIT_LIST_HEAD(&local->interfaces);
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 
 	__hw_addr_init(&local->mc_list);
 
+#endif
 	mutex_init(&local->iflist_mtx);
 	mutex_init(&local->mtx);
 
