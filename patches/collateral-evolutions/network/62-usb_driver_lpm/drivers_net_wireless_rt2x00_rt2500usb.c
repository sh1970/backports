--- a/drivers/net/wireless/rt2x00/rt2500usb.c
+++ b/drivers/net/wireless/rt2x00/rt2500usb.c
@@ -1989,7 +1989,9 @@
 	.suspend	= rt2x00usb_suspend,
 	.resume		= rt2x00usb_resume,
 	.reset_resume	= rt2x00usb_resume,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(rt2500usb_driver);
