--- a/drivers/bluetooth/bluecard_cs.c
+++ b/drivers/bluetooth/bluecard_cs.c
@@ -158,7 +158,12 @@
 static void bluecard_activity_led_timeout(u_long arg)
 {
 	bluecard_info_t *info = (bluecard_info_t *)arg;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+	unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
+
 
 	if (!test_bit(CARD_HAS_PCCARD_ID, &(info->hw_state)))
 		return;
@@ -175,7 +180,11 @@
 
 static void bluecard_enable_activity_led(bluecard_info_t *info)
 {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+	unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 
 	if (!test_bit(CARD_HAS_PCCARD_ID, &(info->hw_state)))
 		return;
@@ -231,7 +240,11 @@
 	}
 
 	do {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 		unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+		unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 		unsigned int offset;
 		unsigned char command;
 		unsigned long ready_bit;
@@ -378,7 +391,11 @@
 		return;
 	}
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	iobase = info->p_dev->resource[0]->start;
+#else
+	iobase = info->p_dev->io.BasePort1;
+#endif
 
 	if (test_bit(XMIT_SENDING_READY, &(info->tx_state)))
 		bluecard_enable_activity_led(info);
@@ -507,7 +524,11 @@
 	if (!test_bit(CARD_READY, &(info->hw_state)))
 		return IRQ_HANDLED;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	iobase = info->p_dev->resource[0]->start;
+#else
+	iobase = info->p_dev->io.BasePort1;
+#endif
 
 	spin_lock(&(info->lock));
 
@@ -629,7 +650,11 @@
 		return 0;
 
 	if (test_bit(CARD_HAS_PCCARD_ID, &(info->hw_state))) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 		unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+		unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 
 		/* Enable LED */
 		outb(0x08 | 0x20, iobase + 0x30);
@@ -649,7 +674,11 @@
 	bluecard_hci_flush(hdev);
 
 	if (test_bit(CARD_HAS_PCCARD_ID, &(info->hw_state))) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 		unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+		unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 
 		/* Disable LED */
 		outb(0x00, iobase + 0x30);
@@ -705,7 +734,11 @@
 
 static int bluecard_open(bluecard_info_t *info)
 {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+	unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 	struct hci_dev *hdev;
 	unsigned char id;
 
@@ -821,7 +854,11 @@
 
 static int bluecard_close(bluecard_info_t *info)
 {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+	unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 	struct hci_dev *hdev = info->hdev;
 
 	if (!hdev)
@@ -856,7 +893,18 @@
 	info->p_dev = link;
 	link->priv = info;
 
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
+	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
+
+	link->irq.Handler = bluecard_interrupt;
+#endif
+
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	link->config_flags |= CONF_ENABLE_IRQ;
+#else
+	link->conf.Attributes = CONF_ENABLE_IRQ;
+	link->conf.IntType = INT_MEMORY_AND_IO;
+#endif
 
 	return bluecard_config(link);
 }
@@ -873,15 +921,30 @@
 	bluecard_info_t *info = link->priv;
 	int i, n;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	link->config_index = 0x20;
+#else
+	link->conf.ConfigIndex = 0x20;
+#endif
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
 	link->resource[0]->end = 64;
 	link->io_lines = 6;
+#else
+	link->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
+	link->io.NumPorts1 = 64;
+	link->io.IOAddrLines = 6;
+#endif
 
 	for (n = 0; n < 0x400; n += 0x40) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 		link->resource[0]->start = n ^ 0x300;
 		i = pcmcia_request_io(link);
+#else
+		link->io.BasePort1 = n ^ 0x300;
+		i = pcmcia_request_io(link, &link->io);
+#endif
 		if (i == 0)
 			break;
 	}
@@ -889,9 +952,15 @@
 	if (i != 0)
 		goto failed;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	i = pcmcia_request_irq(link, bluecard_interrupt);
 	if (i != 0)
 		goto failed;
+#else
+	i = pcmcia_request_irq(link, &link->irq);
+	if (i != 0)
+		link->irq.AssignedIRQ = 0;
+#endif
 
 	i = pcmcia_enable_device(link);
 	if (i != 0)
@@ -929,7 +998,13 @@
 
 static struct pcmcia_driver bluecard_driver = {
 	.owner		= THIS_MODULE,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	.name		= "bluecard_cs",
+#else
+	.drv		= {
+		.name	= "bluecard_cs",
+	},
+#endif
 	.probe		= bluecard_probe,
 	.remove		= bluecard_detach,
 	.id_table	= bluecard_ids,
