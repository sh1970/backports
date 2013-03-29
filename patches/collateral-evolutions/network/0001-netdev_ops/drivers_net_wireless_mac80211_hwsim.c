--- a/drivers/net/wireless/mac80211_hwsim.c
+++ b/drivers/net/wireless/mac80211_hwsim.c
@@ -1695,7 +1695,7 @@
 
 static void hwsim_mon_setup(struct net_device *dev)
 {
-	dev->netdev_ops = &hwsim_netdev_ops;
+	netdev_attach_ops(dev, &hwsim_netdev_ops);
 	dev->destructor = free_netdev;
 	ether_setup(dev);
 	dev->tx_queue_len = 0;
