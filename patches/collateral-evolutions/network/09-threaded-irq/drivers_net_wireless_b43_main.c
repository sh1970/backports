--- a/drivers/net/wireless/b43/main.c
+++ b/drivers/net/wireless/b43/main.c
@@ -4243,8 +4243,13 @@
 	if (b43_bus_host_is_sdio(dev->dev)) {
 		b43_sdio_free_irq(dev);
 	} else {
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+		compat_synchronize_threaded_irq(&dev->irq_compat);
+		compat_free_threaded_irq(&dev->irq_compat);
+#else
 		synchronize_irq(dev->dev->irq);
 		free_irq(dev->dev->irq, dev);
+#endif
 	}
 	mutex_lock(&wl->mutex);
 	dev = wl->current_dev;
@@ -4290,9 +4295,17 @@
 			goto out;
 		}
 	} else {
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+		err = compat_request_threaded_irq(&dev->irq_compat,
+						  dev->dev->irq,
+						  b43_interrupt_handler,
+						  b43_interrupt_thread_handler,
+						  IRQF_SHARED, KBUILD_MODNAME, dev);
+#else
 		err = request_threaded_irq(dev->dev->irq, b43_interrupt_handler,
 					   b43_interrupt_thread_handler,
 					   IRQF_SHARED, KBUILD_MODNAME, dev);
+#endif
 		if (err) {
 			b43err(dev->wl, "Cannot request IRQ-%d\n",
 			       dev->dev->irq);
@@ -5115,6 +5128,10 @@
 
 static void b43_wireless_core_detach(struct b43_wldev *dev)
 {
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+	if (dev->dev->sdev->bus->bustype != SSB_BUSTYPE_SDIO)
+		compat_destroy_threaded_irq(&dev->irq_compat);
+#endif
 	/* We release firmware that late to not be required to re-request
 	 * is all the time when we reinit the core. */
 	b43_release_firmware(dev);
