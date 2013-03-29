--- a/drivers/net/wireless/libertas/if_sdio.c
+++ b/drivers/net/wireless/libertas/if_sdio.c
@@ -1345,6 +1345,7 @@
 	lbs_deb_leave(LBS_DEB_SDIO);
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 static int if_sdio_suspend(struct device *dev)
 {
 	struct sdio_func *func = dev_to_sdio_func(dev);
@@ -1403,15 +1404,18 @@
 	.suspend	= if_sdio_suspend,
 	.resume		= if_sdio_resume,
 };
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) */
 
 static struct sdio_driver if_sdio_driver = {
 	.name		= "libertas_sdio",
 	.id_table	= if_sdio_ids,
 	.probe		= if_sdio_probe,
 	.remove		= if_sdio_remove,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 	.drv = {
 		.pm = &if_sdio_pm_ops,
 	},
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) */
 };
 
 /*******************************************************************/
