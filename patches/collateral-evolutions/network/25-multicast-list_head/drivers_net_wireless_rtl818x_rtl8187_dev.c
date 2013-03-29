--- a/drivers/net/wireless/rtl818x/rtl8187/dev.c
+++ b/drivers/net/wireless/rtl818x/rtl8187/dev.c
@@ -1290,9 +1290,17 @@
 }
 
 static u64 rtl8187_prepare_multicast(struct ieee80211_hw *dev,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 				     struct netdev_hw_addr_list *mc_list)
+#else
+				     int mc_count, struct dev_addr_list *mc_list)
+#endif
 {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	return netdev_hw_addr_list_count(mc_list);
+#else
+	return mc_count;
+#endif
 }
 
 static void rtl8187_configure_filter(struct ieee80211_hw *dev,
