--- a/drivers/net/wireless/b43/pcmcia.c
+++ b/drivers/net/wireless/b43/pcmcia.c
@@ -63,6 +63,9 @@
 static int b43_pcmcia_probe(struct pcmcia_device *dev)
 {
 	struct ssb_bus *ssb;
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37))
+	win_req_t win;
+#endif
 	int err = -ENOMEM;
 	int res = 0;
 
@@ -72,6 +75,7 @@
 
 	err = -ENODEV;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	dev->config_flags |= CONF_ENABLE_IRQ;
 
 	dev->resource[2]->flags |=  WIN_ENABLE | WIN_DATA_WIDTH_16 |
@@ -79,21 +83,46 @@
 	dev->resource[2]->start = 0;
 	dev->resource[2]->end = SSB_CORE_SIZE;
 	res = pcmcia_request_window(dev, dev->resource[2], 250);
+#else
+	dev->conf.Attributes = CONF_ENABLE_IRQ;
+	dev->conf.IntType = INT_MEMORY_AND_IO;
+
+	win.Attributes =  WIN_ENABLE | WIN_DATA_WIDTH_16 |
+			 WIN_USE_WAIT;
+	win.Base = 0;
+	win.Size = SSB_CORE_SIZE;
+	win.AccessSpeed = 250;
+	res = pcmcia_request_window(dev, &win, &dev->win);
+#endif
 	if (res != 0)
 		goto err_kfree_ssb;
-
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	res = pcmcia_map_mem_page(dev, dev->resource[2], 0);
+#else
+	res = pcmcia_map_mem_page(dev, dev->win, 0);
+#endif
 	if (res != 0)
 		goto err_disable;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	if (!dev->irq)
+#else
+	dev->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
+	dev->irq.Handler = NULL; /* The handler is registered later. */
+	res = pcmcia_request_irq(dev, &dev->irq);
+	if (res != 0)
+#endif
 		goto err_disable;
 
 	res = pcmcia_enable_device(dev);
 	if (res != 0)
 		goto err_disable;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	err = ssb_bus_pcmciabus_register(ssb, dev, dev->resource[2]->start);
+#else
+	err = ssb_bus_pcmciabus_register(ssb, dev, win.Base);
+#endif
 	if (err)
 		goto err_disable;
 	dev->priv = ssb;
@@ -122,7 +151,13 @@
 
 static struct pcmcia_driver b43_pcmcia_driver = {
 	.owner		= THIS_MODULE,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	.name		= "b43-pcmcia",
+#else
+	.drv		= {
+		.name	= "b43-pcmcia",
+	},
+#endif
 	.id_table	= b43_pcmcia_tbl,
 	.probe		= b43_pcmcia_probe,
 	.remove		= b43_pcmcia_remove,
