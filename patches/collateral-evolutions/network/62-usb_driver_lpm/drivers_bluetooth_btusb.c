--- a/drivers/bluetooth/btusb.c
+++ b/drivers/bluetooth/btusb.c
@@ -1234,7 +1234,9 @@
 #endif
 	.id_table	= btusb_table,
 	.supports_autosuspend = 1,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(btusb_driver);
