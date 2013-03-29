--- a/drivers/net/wireless/mwl8k.c
+++ b/drivers/net/wireless/mwl8k.c
@@ -2656,15 +2656,21 @@
 
 static struct mwl8k_cmd_pkt *
 __mwl8k_cmd_mac_multicast_adr(struct ieee80211_hw *hw, int allmulti,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 			      struct netdev_hw_addr_list *mc_list)
+#else
+			      int mc_count, struct dev_addr_list *ha)
+#endif
 {
 	struct mwl8k_priv *priv = hw->priv;
 	struct mwl8k_cmd_mac_multicast_adr *cmd;
 	int size;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	int mc_count = 0;
 
 	if (mc_list)
 		mc_count = netdev_hw_addr_list_count(mc_list);
+#endif
 
 	if (allmulti || mc_count > priv->num_mcaddrs) {
 		allmulti = 1;
@@ -2685,13 +2691,27 @@
 	if (allmulti) {
 		cmd->action |= cpu_to_le16(MWL8K_ENABLE_RX_ALL_MULTICAST);
 	} else if (mc_count) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		struct netdev_hw_addr *ha;
 		int i = 0;
+#else
+		int i;
+#endif
 
 		cmd->action |= cpu_to_le16(MWL8K_ENABLE_RX_MULTICAST);
 		cmd->numaddr = cpu_to_le16(mc_count);
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		netdev_hw_addr_list_for_each(ha, mc_list) {
 			memcpy(cmd->addr[i], ha->addr, ETH_ALEN);
+#else
+		for (i = 0; i < mc_count && ha; i++) {
+			if (ha->da_addrlen != ETH_ALEN) {
+				kfree(cmd);
+				return NULL;
+			}
+			memcpy(cmd->addr[i], ha->da_addr, ETH_ALEN);
+			ha = ha->next;
+#endif
 		}
 	}
 
@@ -5022,7 +5042,11 @@
 }
 
 static u64 mwl8k_prepare_multicast(struct ieee80211_hw *hw,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 				   struct netdev_hw_addr_list *mc_list)
+#else
+				   int mc_count, struct dev_addr_list *ha)
+#endif
 {
 	struct mwl8k_cmd_pkt *cmd;
 
@@ -5033,7 +5057,11 @@
 	 * we'll end up throwing this packet away and creating a new
 	 * one in mwl8k_configure_filter().
 	 */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	cmd = __mwl8k_cmd_mac_multicast_adr(hw, 0, mc_list);
+#else
+	cmd = __mwl8k_cmd_mac_multicast_adr(hw, 0, mc_count, ha);
+#endif
 
 	return (unsigned long)cmd;
 }
@@ -5155,7 +5183,11 @@
 	 */
 	if (*total_flags & FIF_ALLMULTI) {
 		kfree(cmd);
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		cmd = __mwl8k_cmd_mac_multicast_adr(hw, 1, NULL);
+#else
+		cmd = __mwl8k_cmd_mac_multicast_adr(hw, 1, 0, NULL);
+#endif
 	}
 
 	if (cmd != NULL) {
