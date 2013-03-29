--- a/drivers/net/wireless/ath/carl9170/main.c
+++ b/drivers/net/wireless/ath/carl9170/main.c
@@ -967,17 +967,35 @@
 	return err;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 static u64 carl9170_op_prepare_multicast(struct ieee80211_hw *hw,
 					 struct netdev_hw_addr_list *mc_list)
+#else
+static u64 carl9170_op_prepare_multicast(struct ieee80211_hw *hw, int mc_count,
+					 struct dev_addr_list *ha)
+#endif
 {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	struct netdev_hw_addr *ha;
+#else
+	int i;
+#endif
 	u64 mchash;
 
 	/* always get broadcast frames */
 	mchash = 1ULL << (0xff >> 2);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	netdev_hw_addr_list_for_each(ha, mc_list)
 		mchash |= 1ULL << (ha->addr[5] >> 2);
+#else
+	for (i = 0; i < mc_count; i++) {
+		if (WARN_ON(!ha))
+			break;
+		mchash |= 1ULL << (ha->dmi_addr[5] >> 2);
+		ha = ha->next;
+	}
+#endif
 
 	return mchash;
 }
