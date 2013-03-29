--- a/drivers/net/wireless/rndis_wlan.c
+++ b/drivers/net/wireless/rndis_wlan.c
@@ -3757,7 +3757,9 @@
 	.disconnect =	usbnet_disconnect,
 	.suspend =	usbnet_suspend,
 	.resume =	usbnet_resume,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(rndis_wlan_driver);
