--- a/drivers/net/wireless/rtl818x/rtl8180/dev.c
+++ b/drivers/net/wireless/rtl818x/rtl8180/dev.c
@@ -818,10 +818,19 @@
 	}
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 static u64 rtl8180_prepare_multicast(struct ieee80211_hw *dev,
 				     struct netdev_hw_addr_list *mc_list)
+#else
+static u64 rtl8180_prepare_multicast(struct ieee80211_hw *dev, int mc_count,
+				     struct dev_addr_list *mc_list)
+#endif
 {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	return netdev_hw_addr_list_count(mc_list);
+#else
+	return mc_count;
+#endif
 }
 
 static void rtl8180_configure_filter(struct ieee80211_hw *dev,
