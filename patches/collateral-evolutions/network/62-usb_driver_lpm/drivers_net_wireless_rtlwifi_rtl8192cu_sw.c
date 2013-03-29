--- a/drivers/net/wireless/rtlwifi/rtl8192cu/sw.c
+++ b/drivers/net/wireless/rtlwifi/rtl8192cu/sw.c
@@ -384,7 +384,9 @@
 #ifdef CONFIG_AUTOSUSPEND
 	.supports_autosuspend = 1,
 #endif
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(rtl8192cu_driver);
