--- a/drivers/net/wireless/ath/ath9k/hif_usb.c
+++ b/drivers/net/wireless/ath/ath9k/hif_usb.c
@@ -1370,7 +1370,9 @@
 	.reset_resume = ath9k_hif_usb_resume,
 #endif
 	.id_table = ath9k_hif_usb_ids,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27))
 	.soft_unbind = 1,
+#endif
 	.disable_hub_initiated_lpm = 1,
 };
 
