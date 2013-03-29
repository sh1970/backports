--- a/drivers/net/ethernet/atheros/atlx/atl2.c
+++ b/drivers/net/ethernet/atheros/atlx/atl2.c
@@ -396,6 +396,7 @@
 	atl2_vlan_mode(adapter->netdev, adapter->netdev->features);
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 static netdev_features_t atl2_fix_features(struct net_device *netdev,
 	netdev_features_t features)
 {
@@ -421,6 +422,7 @@
 
 	return 0;
 }
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 
 static void atl2_intr_rx(struct atl2_adapter *adapter)
 {
@@ -1319,8 +1321,10 @@
 	.ndo_validate_addr	= eth_validate_addr,
 	.ndo_set_mac_address	= atl2_set_mac,
 	.ndo_change_mtu		= atl2_change_mtu,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	.ndo_fix_features	= atl2_fix_features,
 	.ndo_set_features	= atl2_set_features,
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 	.ndo_do_ioctl		= atl2_ioctl,
 	.ndo_tx_timeout		= atl2_tx_timeout,
 #ifdef CONFIG_NET_POLL_CONTROLLER
@@ -1417,8 +1421,12 @@
 
 	err = -EIO;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	netdev->hw_features = NETIF_F_SG | NETIF_F_HW_VLAN_RX;
+#endif
+#if defined(NETIF_F_HW_VLAN_TX) || (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	netdev->features |= (NETIF_F_HW_VLAN_TX | NETIF_F_HW_VLAN_RX);
+#endif
 
 	/* Init PHY as early as possible due to power saving issue  */
 	atl2_phy_init(&adapter->hw);
@@ -1838,6 +1846,13 @@
 	return 0;
 }
 
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39))
+static u32 atl2_get_tx_csum(struct net_device *netdev)
+{
+	return (netdev->features & NETIF_F_HW_CSUM) != 0;
+}
+#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)) */
+
 static u32 atl2_get_msglevel(struct net_device *netdev)
 {
 	return 0;
@@ -2107,6 +2122,14 @@
 	.get_eeprom_len		= atl2_get_eeprom_len,
 	.get_eeprom		= atl2_get_eeprom,
 	.set_eeprom		= atl2_set_eeprom,
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39))
+	.get_tx_csum		= atl2_get_tx_csum,
+	.get_sg			= ethtool_op_get_sg,
+	.set_sg			= ethtool_op_set_sg,
+#ifdef NETIF_F_TSO
+	.get_tso		= ethtool_op_get_tso,
+#endif
+#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)) */
 };
 
 static void atl2_set_ethtool_ops(struct net_device *netdev)
