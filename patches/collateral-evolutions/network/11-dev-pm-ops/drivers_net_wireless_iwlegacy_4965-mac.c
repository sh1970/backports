--- a/drivers/net/wireless/iwlegacy/4965-mac.c
+++ b/drivers/net/wireless/iwlegacy/4965-mac.c
@@ -6803,7 +6803,12 @@
 	.id_table = il4965_hw_card_ids,
 	.probe = il4965_pci_probe,
 	.remove = il4965_pci_remove,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 	.driver.pm = IL_LEGACY_PM_OPS,
+#elif defined(CONFIG_PM)
+	.suspend = il_pci_suspend_compat,
+	.resume = il_pci_resume_compat,
+#endif
 };
 
 static int __init
