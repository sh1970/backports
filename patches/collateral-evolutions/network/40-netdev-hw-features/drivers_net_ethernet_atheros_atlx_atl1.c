--- a/drivers/net/ethernet/atheros/atlx/atl1.c
+++ b/drivers/net/ethernet/atheros/atlx/atl1.c
@@ -2917,8 +2917,10 @@
 	.ndo_validate_addr	= eth_validate_addr,
 	.ndo_set_mac_address	= atl1_set_mac,
 	.ndo_change_mtu		= atl1_change_mtu,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	.ndo_fix_features	= atlx_fix_features,
 	.ndo_set_features	= atlx_set_features,
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 	.ndo_do_ioctl		= atlx_ioctl,
 	.ndo_tx_timeout		= atlx_tx_timeout,
 #ifdef CONFIG_NET_POLL_CONTROLLER
@@ -3028,11 +3030,13 @@
 	netdev->features |= NETIF_F_SG;
 	netdev->features |= (NETIF_F_HW_VLAN_TX | NETIF_F_HW_VLAN_RX);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	netdev->hw_features = NETIF_F_HW_CSUM | NETIF_F_SG | NETIF_F_TSO |
 			      NETIF_F_HW_VLAN_RX;
 
 	/* is this valid? see atl1_setup_mac_ctrl() */
 	netdev->features |= NETIF_F_RXCSUM;
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 
 	/*
 	 * patch for some L1 of old version,
@@ -3645,6 +3649,14 @@
 	return 0;
 }
 
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39))
+/* FIXME: is this right? -- CHS */
+static u32 atl1_get_rx_csum(struct net_device *netdev)
+{
+	return 1;
+}
+#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)) */
+
 static void atl1_get_strings(struct net_device *netdev, u32 stringset,
 	u8 *data)
 {
@@ -3717,4 +3729,10 @@
 	.nway_reset		= atl1_nway_reset,
 	.get_ethtool_stats	= atl1_get_ethtool_stats,
 	.get_sset_count		= atl1_get_sset_count,
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39))
+	.get_rx_csum		= atl1_get_rx_csum,
+	.set_tx_csum		= ethtool_op_set_tx_hw_csum,
+	.set_sg			= ethtool_op_set_sg,
+	.set_tso		= ethtool_op_set_tso,
+#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)) */
 };
