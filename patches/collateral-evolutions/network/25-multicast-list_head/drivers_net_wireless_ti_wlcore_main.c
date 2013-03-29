--- a/drivers/net/wireless/ti/wlcore/main.c
+++ b/drivers/net/wireless/ti/wlcore/main.c
@@ -2952,11 +2952,20 @@
 	u8 mc_list[ACX_MC_ADDRESS_GROUP_MAX][ETH_ALEN];
 };
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 static u64 wl1271_op_prepare_multicast(struct ieee80211_hw *hw,
 				       struct netdev_hw_addr_list *mc_list)
+#else
+static u64 wl1271_op_prepare_multicast(struct ieee80211_hw *hw, int mc_count,
+				       struct dev_addr_list *mc_list)
+#endif
 {
 	struct wl1271_filter_params *fp;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	struct netdev_hw_addr *ha;
+#else
+	int i;
+#endif
 
 	fp = kzalloc(sizeof(*fp), GFP_ATOMIC);
 	if (!fp) {
@@ -2965,16 +2974,40 @@
 	}
 
 	/* update multicast filtering parameters */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	fp->mc_list_length = 0;
 	if (netdev_hw_addr_list_count(mc_list) > ACX_MC_ADDRESS_GROUP_MAX) {
+#else
+	fp->enabled = true;
+	if (mc_count > ACX_MC_ADDRESS_GROUP_MAX) {
+		mc_count = 0;
+#endif
 		fp->enabled = false;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	} else {
 		fp->enabled = true;
 		netdev_hw_addr_list_for_each(ha, mc_list) {
+#else
+	}
+
+	fp->mc_list_length = 0;
+	for (i = 0; i < mc_count; i++) {
+		if (mc_list->da_addrlen == ETH_ALEN) {
+#endif
 			memcpy(fp->mc_list[fp->mc_list_length],
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 					ha->addr, ETH_ALEN);
+#else
+			       mc_list->da_addr, ETH_ALEN);
+#endif
 			fp->mc_list_length++;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		}
+#else
+		} else
+			wl1271_warning("Unknown mc address length.");
+		mc_list = mc_list->next;
+#endif
 	}
 
 	return (u64)(unsigned long)fp;
