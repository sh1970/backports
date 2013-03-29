--- a/drivers/net/wireless/ath/carl9170/usb.c
+++ b/drivers/net/wireless/ath/carl9170/usb.c
@@ -1166,7 +1166,9 @@
 	.resume = carl9170_usb_resume,
 	.reset_resume = carl9170_usb_resume,
 #endif /* CONFIG_PM */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(carl9170_driver);
