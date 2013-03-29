--- a/drivers/net/wireless/ath/ath9k/hif_usb.c
+++ b/drivers/net/wireless/ath/ath9k/hif_usb.c
@@ -1373,7 +1373,9 @@
 #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27))
 	.soft_unbind = 1,
 #endif
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 int ath9k_hif_usb_init(void)
