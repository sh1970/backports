--- a/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
+++ b/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
@@ -2622,7 +2622,9 @@
 	}
 	if (atl1c_read_mac_addr(&adapter->hw)) {
 		/* got a random MAC address, set NET_ADDR_RANDOM to netdev */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 		netdev->addr_assign_type = NET_ADDR_RANDOM;
+#endif
 	}
 	memcpy(netdev->dev_addr, adapter->hw.mac_addr, netdev->addr_len);
 	if (netif_msg_probe(adapter))
