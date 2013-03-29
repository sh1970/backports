--- a/drivers/net/ethernet/atheros/atlx/atl1.c
+++ b/drivers/net/ethernet/atheros/atlx/atl1.c
@@ -3060,7 +3060,9 @@
 	/* copy the MAC address out of the EEPROM */
 	if (atl1_read_mac_addr(&adapter->hw)) {
 		/* mark random mac */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 		netdev->addr_assign_type = NET_ADDR_RANDOM;
+#endif
 	}
 	memcpy(netdev->dev_addr, adapter->hw.mac_addr, netdev->addr_len);
 
