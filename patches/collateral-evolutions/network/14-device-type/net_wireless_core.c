--- a/net/wireless/core.c
+++ b/net/wireless/core.c
@@ -839,9 +839,11 @@
 }
 EXPORT_SYMBOL(cfg80211_unregister_wdev);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,32))
 static struct device_type wiphy_type = {
 	.name	= "wlan",
 };
+#endif
 
 void cfg80211_update_iface_num(struct cfg80211_registered_device *rdev,
 			       enum nl80211_iftype iftype, int num)
