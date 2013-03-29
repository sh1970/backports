--- a/drivers/net/wireless/ath/ath6kl/usb.c
+++ b/drivers/net/wireless/ath/ath6kl/usb.c
@@ -1207,7 +1207,9 @@
 	.disconnect = ath6kl_usb_remove,
 	.id_table = ath6kl_usb_ids,
 	.supports_autosuspend = true,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 static int ath6kl_usb_init(void)
