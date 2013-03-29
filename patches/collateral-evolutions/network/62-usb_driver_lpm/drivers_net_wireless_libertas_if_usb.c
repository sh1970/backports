--- a/drivers/net/wireless/libertas/if_usb.c
+++ b/drivers/net/wireless/libertas/if_usb.c
@@ -1015,7 +1015,9 @@
 	.suspend = if_usb_suspend,
 	.resume = if_usb_resume,
 	.reset_resume = if_usb_resume,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(if_usb_driver);
